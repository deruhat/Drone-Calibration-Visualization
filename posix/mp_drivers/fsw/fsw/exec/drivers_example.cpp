////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    fsw/exec/mikipilot_fsw.cpp                                                           //
// DATE:     Tue Nov 24 03:26:36 2015                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////
// MODIFIED BY:	Abdulellah Abualshour    //
// PI: 		Mohammed Alshiekh        //
// LAB:   	Autonomous GN&C Lab      //
///////////////////////////////////////////

// Libraries:
#include "fsw/globals/globals.h"
#include "fsw/hardware/mp_ap_board.h"
#include "fsw/hardware/overo.h"
#include "fsw/control/MatricesAndVectors.h"
#include "fsw/control/QuatRotEuler.h"
#include "fsw/control/MathFuncs.h"
#include "fsw/control/AttitudeControl.h"
#include "fsw/control/pevents.h"
/* */
#include "packets/all.h"
#include "utilities/consumer.h"
#include "utilities/globals.h"
#include "utilities/producer.h"
#include "utilities/timer.h"
#include "comm/comm/globals.h"
/* */
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
/* */
#include <time.h>
#include "pthread.h"
#include "ros.h"
#include "sensor_msgs/Joy.h"
#include <chrono>
/* */
#define USE_USBCON
#define PI 3.14159265

// namespaces:
using namespace std::chrono;
using namespace neosmart;
using std::string;

// Workstation IP Address:
char *rosSrvrIp = "192.168.1.51";

// pevent.h stuff:
neosmart_event_t e_Key1, e_Key2, e_KeyESC;
neosmart_event_t e_Timeout; //Always false event for forcing timeout of WaitForEvent

// Global variables:
int threadCount = 0;
//
float max_hvel = 2.0;
float max_vvel = 0.5;
//
float v_f = 0.0f;
float v_r = 0.0f;
float v_d = 0.0f;
float psi_rate = 0.0f;
//
float dv_n = 0.0f;
float dv_w = 0.0f;
float dv_u = 0.0f;
float dpsi_rate = 0.0f;
//
float dp_n = 0.0f;
float dp_w = 0.0f;
float dp_u = 1.0f;
//
float cp_n = 0.0f;
float cp_w = 0.0f;
float cp_u = 0.0f;
float attitude[4] = {0,0,0,0};
//
float pe_n_prev = 0.0f;
float pe_w_prev = 0.0f;
float pe_u_prev = 0.0f;
//
float t = 0;
float t_prev = 0;
float dt = 0;
//
float m1 = 0.0f;
float m2 = 0.0f;
float m3 = 0.0f;
float m4 = 0.0f;
//
float kyaw = 0.5f;
float kz = 0.1f;
//
int firstLoop = 1;
//
//Desired thrust, roll, pitch and yaw
float u1 = 0;
double roll_ref = 0;
double pitch_ref = 0;
double yaw_ref = 0; 

//Create quaternion, gyro and pwm variables
float q_n2b[4];  // = {0.12314235f,0.12314235f,0.12314235f,0.12314235f};
float gyro[3];  // = {0.12314235f,0.12314235f,0.12314235f};
float pwm[6];  // = {0.12314235f,0.12314235f,0.12314235f,0.12314235f, 0.12314235f, 0.12314235f};

void cb_joy(const sensor_msgs::Joy& msg){
	u1 = msg.axes[1]*20;
	roll_ref = -msg.axes[3]*PI/6;
	pitch_ref = msg.axes[4]*PI/6;
	//printf("msg: %f %f\n",roll_ref, pitch_ref);
}

struct filter{
	double y;
	double y_prev;
	double y_prev2;
	double x;
	double x_prev;
	double x_prev2;
	double num[3];
	double den[3]; 
};

void initializeFilter(filter *F,double x){
	F->num[0] = 1;
	F->num[1] = -1.95558;
	F->num[2] = 0.956544;
	F->den[0] = 0.000241359;
	F->den[1] = 0.000482718;
	F->den[2] = 0.000241359;
	F->y_prev = x; //Set as first measurement
	F->y_prev2 = x;
	F->x_prev = x;
	F->x_prev2 = x;
}

void runFilter(filter *F, double measurement){
	F->x = measurement;
	F->y = F->den[0]*F->x + F->den[1]*F->x_prev + F->den[2]*F->x_prev2 - F->num[1]*F->y_prev - F->num[2]*F->y_prev2;
	F->y_prev2 = F->y_prev;
	F->y_prev = F->y;
	F->x_prev2 = F->x_prev;
	F->x_prev = F->x;
}

// Multithreading POSIX stuff:
char getch() { //This function allows to capture char without needing to press 'ENTER'
	char buf = 0;
	struct termios old = {0};
	if (tcgetattr(0, &old) < 0)
		    perror("tcsetattr()");
	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 1;
	old.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &old) < 0)
		    perror("tcsetattr ICANON");
	if (read(0, &buf, 1) < 0)
		    perror ("read()");
	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if (tcsetattr(0, TCSADRAIN, &old) < 0)
		    perror ("tcsetattr ~ICANON");
	return (buf);
}

void *keyboardTask(void *threadID)
{
	char ch;	//Char for storing keystroke
	printf("KeyboardTask has started!\n");
	int Key1 = 0, Key2 = 0, KeyESC = 0;		//Values for key states (0 or 1)
	
	while(1){
		ch = getch();
		if (ch == '1'){
			Key1 = (Key1 + 1) % 2;
			if (Key1 == 1)
				SetEvent(e_Key1);
			else
				ResetEvent(e_Key1);
			printf("Key1 State: %d\n",Key1);
		}
		else if (ch == '2'){
			SetEvent(e_Key2);
			Key2 = (Key2 + 1) % 2;
			printf("Key2 State: %d\n",Key2);
		}
		else if (ch == 27){	//ESC character
			SetEvent(e_KeyESC);
			KeyESC = (KeyESC + 1) % 2;
			printf("\nESC has been activated!\n\n");
			break;
		}
	}
	
	printf("keyboardTask stopping...\n");
	threadCount -= 1;
	pthread_exit(NULL);
}

void* rosJoyTask(void* threadID){
	printf("rosJoyTask has started!\n");
	ros::NodeHandle  nh;  
	nh.initNode(rosSrvrIp);
  	ros::Subscriber<sensor_msgs::Joy> sub_joy("/joy", cb_joy);
  	while(1){
  		nh.subscribe(sub_joy);
		nh.spinOnce();
		if(WaitForEvent(e_KeyESC,0) == 0) //Check if ESC was pressed
			break;
	}
	printf("rosJoyTask stopping...\n");
	threadCount -= 1;
	pthread_exit(NULL);
}

void* controlTask(void* threadID){
	printf("controlTask has started!\n");
	
	//Filter for magnetometer values
	filter MagFiltX;
	filter MagFiltY;
	filter MagFiltZ;

	// Initialize hardware and GNC objects.
	comm::meta::set_local_node_id(comm::meta::NODE_001);
	fsw::hardware::overo overo;
	fsw::hardware::mp_ap_board mp_ap_board(overo,1,1,1);

	// Can call this if the MP AP board powers up with the red (D2) LED lit (that means that 
	// the board is in manual inputs mode, and that it will ignore what the autopilot is commanding
	// on the PWM channels). This happens occasionally, but is only an issue during power up. 
	// Calling the function below will put the board in autopilot command mode, and you'll see 
	// D2 turn off, and D1 (the green LED) turn on.
	mp_ap_board.set_pwm_mux_to_ap();

	// Declare local consumers/producers.
	utilities::consumer< packets::imu_data<TOPIC_DEVICE> > imu_consumer("imu_consumer",1);
	utilities::consumer< packets::mag_data<TOPIC_DEVICE> > mag_consumer("mag_consumer",1);
	utilities::producer< packets::pwm_cmd<TOPIC_DEVICE> > pwm_producer("pwm_producer");

	// Make connections.
	mp_ap_board.imu().tx_device_data >> imu_consumer;
	mp_ap_board.mag().tx_device_data >> mag_consumer;
	mp_ap_board.pwm().rx_device_data << pwm_producer;

	// Set devices to "DEVICE" mode.
	mp_ap_board.imu().m_module_sm.rx_transition_request.push(states::imu_state::DEVICE);
	mp_ap_board.mag().m_module_sm.rx_transition_request.push(states::mag_state::DEVICE);
	mp_ap_board.pwm().m_module_sm.rx_transition_request.push(states::pwm_state::DEVICE);

	// Set devices to "SIM" mode.
	//mp_ap_board.imu().m_module_sm.rx_transition_request.push(states::imu_state::SIM);
	//mp_ap_board.mag().m_module_sm.rx_transition_request.push(states::mag_state::SIM);
	//mp_ap_board.pwm().m_module_sm.rx_transition_request.push(states::pwm_state::SIM);

	// Can call these individually if you want to calibrate any of the devices.
	//mp_ap_board.imu().m_module_sm.rx_transition_request.push(states::imu_state::CALIBRATE);
	//mp_ap_board.mag().m_module_sm.rx_transition_request.push(states::mag_state::CALIBRATE);
	//mp_ap_board.pwm().m_module_sm.rx_transition_request.push(states::pwm_state::CALIBRATE);

	// Declare local variables.
	utilities::timer local_clock("test_timer",1);
	packets::imu_data<TOPIC_DEVICE> temp_imu_data;
	packets::mag_data<TOPIC_DEVICE> temp_mag_data;
	packets::pwm_cmd<TOPIC_DEVICE> temp_pwm_data;

	float ts = utilities::timer::get_timestamp().to_sec();

	mp_ap_board.imu().execute(ts);
	imu_consumer.pull(temp_imu_data);
	mp_ap_board.mag().execute(ts);
	mag_consumer.pull(temp_mag_data);

	while(temp_imu_data.p_accl[0] == 0){
		printf("Waiting for IMU data... ");
		sleep(0.25);
		mp_ap_board.imu().execute(ts);
		imu_consumer.pull(temp_imu_data);
	}

	while(temp_mag_data.p_mag_vec[0] == 0){
		printf("Waiting for Magnetometer data... ");
		sleep(0.25);
		mp_ap_board.mag().execute(ts);
		mag_consumer.pull(temp_mag_data);
	}

	initializeFilter(&MagFiltX,temp_imu_data.p_accl[0]);
	initializeFilter(&MagFiltY,temp_imu_data.p_accl[1]);
	initializeFilter(&MagFiltZ,temp_imu_data.p_accl[2]);

	float SumMagX = 0;
	float SumMagY = 0;
	float SumMagZ = 0;
	int nData = 250;
	for (int index = 0; index < nData; index++){
		mp_ap_board.mag().execute(ts);
		mag_consumer.pull(temp_mag_data);
		SumMagX += temp_mag_data.p_mag_vec[0];
		SumMagY += temp_mag_data.p_mag_vec[1];
		SumMagZ += temp_mag_data.p_mag_vec[2];
		//printf("test  ");
		usleep(5000);
	}
	Vec3 north_inert;
	north_inert.v[0] = SumMagX/nData;
	north_inert.v[1] = SumMagY/nData;
	north_inert.v[2] = SumMagZ/nData;
	north_inert = ScaleVec3(north_inert, 1.0 / p_normVec3(north_inert, 2));
	printf("\nNorth = %f %f %f \n",north_inert.v[0], north_inert.v[1], north_inert.v[2]);

	FILE* output_file = fopen("output.txt", "w"); 
	// Enter waiting loop.
	for (local_clock.reset(); true; ++local_clock.await_target()) {
		ts = utilities::timer::get_timestamp().to_sec();

		t = local_clock.time_elapsed().to_sec();
		dt = t - t_prev;
		// printf("dt = %f\n",dt);

		mp_ap_board.imu().execute(ts);
		mp_ap_board.mag().execute(ts);

		imu_consumer.pull(temp_imu_data);
		mag_consumer.pull(temp_mag_data);

		runFilter(&MagFiltX, temp_imu_data.p_accl[0]);
		runFilter(&MagFiltY, temp_imu_data.p_accl[1]);
		runFilter(&MagFiltZ, temp_imu_data.p_accl[2]);

		//inertial gravity vector [0,0,1]
		Vec3 gravity_inert;
		gravity_inert.v[0] = 0; 
		gravity_inert.v[1] = 0; 
		gravity_inert.v[2] = 1;
		//PrintVec3 (gravity_inert,"gravity inertial");
		//fprintf(output_file,"%f %f %f\n",gravity_inert.v[0],gravity_inert.v[1],gravity_inert.v[2]);

		//inertial north vector [1,0,0]
		//Vec3 north_inert; 
		//north_inert.v[0] = -0.377646794; 
		//north_inert.v[1] = -0.189410678; 
		//north_inert.v[2] = 0.906345558;
		//PrintVec3 (north_inert,"north inertial");
		//fprintf(output_file,"%f %f %f\n",north_inert.v[0],north_inert.v[1],north_inert.v[2]); 

		//gravity vector from body frame = -accelerometer readings
		Vec3 gravity;
		gravity.v[0] = -MagFiltX.y; 
		gravity.v[1] = -MagFiltY.y; 
		gravity.v[2] = -MagFiltZ.y;
		//PrintVec3 (gravity,"gravity");

		//north vector from body frame = magnetometer readings
		Vec3 north;
		north.v[0] = temp_mag_data.p_mag_vec[0]; 
		north.v[1] = temp_mag_data.p_mag_vec[1]; 
		north.v[2] = temp_mag_data.p_mag_vec[2]; 
		//PrintVec3 (north,"north");
		//fprintf(output_file,"%f %f %f\n",north.v[0],north.v[1],north.v[2]);

		//Rotation for Triad algorithm
		Mat3x3 Rot = Triad(gravity,north,gravity_inert,north_inert);
		//PrintMat3x3 (Rot);
		Vec4 quat = Rot2quat(Rot);
		//PrintVec4(quat,"Quaternion");
		Vec3 RPY;
		RPY = Quat2RPY(quat);
		PrintVec3 (ScaleVec3(RPY,180/PI),"RPY  "); 
		//fprintf(output_file,"%f %f %f %f\n",t, RPY.v[0],RPY.v[1],RPY.v[2]);
		//printf("thrust: %f\n",u1);

		// Angular velocity
		Vec3 w_bw;
		w_bw.v[0] = -temp_imu_data.p_gyro[0];
		w_bw.v[1] = -temp_imu_data.p_gyro[1]; 
		w_bw.v[2] = -temp_imu_data.p_gyro[2];
		//PrintVec3(w_bw, "angVel");

		//Desired angular velocity
		Vec3 wDes;
		wDes.v[0] = 0; wDes.v[1] = 0; wDes.v[2] = 0;


		//Desired rotation matrix
		Mat3x3 Rdes = RPY2Rot(roll_ref, pitch_ref, yaw_ref);

		//Call the attitude control function
		Vec4 u = attitudeControl(quat, Rdes, Rot, w_bw, wDes, u1);
		//PrintVec4(u,"Thrust");
		Vec4 pwmVec = u2pwmXshape(u);
		//PrintVec4(pwmVec,"pwm");

		//Allocate motor speeds
		temp_pwm_data.ch(0) = pwmVec.v[1]*1000+1000;
		temp_pwm_data.ch(1) = pwmVec.v[2]*1000+1000;
		temp_pwm_data.ch(2) = pwmVec.v[3]*1000+1000;
		temp_pwm_data.ch(3) = pwmVec.v[0]*1000+1000;

		//printf("Motors: %f %f %f %f\n",temp_pwm_data.ch(0),temp_pwm_data.ch(1),temp_pwm_data.ch(2),temp_pwm_data.ch(3));

		pwm_producer.push(temp_pwm_data);
		mp_ap_board.pwm().execute(ts);

		//printf("Motors: %f %f %f %f\n",m1*1000+1000,m2*1000+1000,m3*1000+1000,m4*1000+1000);
		//interface.hold_motor(m1, m2, m3, m4);

		//Print outputs
		//PrintVec4(u, "Inputs");
		//printf("\n");

		//fprintf(output_file,"%f %f %f %f %f %f %f %f %f %f %f %f %f\n",t, MagFiltX.y,MagFiltY.y,MagFiltZ.y,north.v[0],north.v[1],north.v[2], RPY.v[0],RPY.v[1],RPY.v[2], 
		//w_bw.v[0], w_bw.v[1], w_bw.v[2]);

		// Wait till end of period. In this example, local_clock is set to a period of 500 ms, and 
		// has its target time incremented with ++local_clock. await_target() internally calls a 
		// wait to reach the internal target time for the current period. You can see what the 
		// target time is at any point by using utilities::timer::target() which returns a 
		// utilities::tob object (see source code provided in utilities).
		t_prev = t;
		if(WaitForEvent(e_KeyESC,0) == 0) //Check if ESC was pressed
		break;
	}


	// Set devices to "IDLE" mode.
	mp_ap_board.imu().m_module_sm.rx_transition_request.push(states::imu_state::IDLE);
	mp_ap_board.mag().m_module_sm.rx_transition_request.push(states::mag_state::IDLE);
	mp_ap_board.pwm().m_module_sm.rx_transition_request.push(states::pwm_state::IDLE);

	// Set devices to "TERM" mode.
	mp_ap_board.imu().m_module_sm.rx_transition_request.push(states::imu_state::TERM);
	mp_ap_board.mag().m_module_sm.rx_transition_request.push(states::mag_state::TERM);
	mp_ap_board.pwm().m_module_sm.rx_transition_request.push(states::pwm_state::TERM);

	fclose(output_file);
	printf("controlTask stopping...\n");
	threadCount -= 1;
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {

	// Start events:
	e_Key1 = CreateEvent(true,false); 			//manual-reset event
	e_Key2 = CreateEvent(false,false); 			//auto-reset event
	e_KeyESC = CreateEvent(true,false); 	
	e_Timeout = CreateEvent(false,false);	

	// Declare threads:
	pthread_t rosJoyThread;
	pthread_t controlThread;
	pthread_t keyboardThread;

	// Create threads:
	pthread_create(&rosJoyThread, NULL, rosJoyTask, NULL);
	threadCount += 1;
	pthread_create(&controlThread, NULL, controlTask, NULL);
	threadCount += 1;
	pthread_create(&keyboardThread, NULL, keyboardTask, NULL);
	threadCount += 1;
	
	// Loop for ESC detection:
	while(1){
		WaitForEvent(e_Timeout,500);
		if(threadCount == 0)
			break;
	}
	printf("Closing program... \n");
	
	// Free memory:
	DestroyEvent(e_Key1);
	DestroyEvent(e_Key2);
	DestroyEvent(e_KeyESC);
	DestroyEvent(e_Timeout);
	
	// Exit:
	pthread_exit(NULL);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
