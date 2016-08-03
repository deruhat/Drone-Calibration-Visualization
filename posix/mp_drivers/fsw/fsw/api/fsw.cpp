////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    api/fsw.cpp                                                                          //
// DATE:     Fri Jan 22 01:07:17 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "fsw.h"
#include "messages/receiver.h"
#include "messages/transmitter.h"
#include "utilities/timer.h"
using api::fsw;
using messages::ctrl_mode_pkt;
using messages::port_ext_xlrx;
using messages::port_ext_xltx;
using messages::port_fsw_xlrx;
using messages::port_gcs_ul;
using messages::port_gcs_log;
using messages::port_fsw_ul;
using messages::receiver;
using messages::transmitter;
using std::string;
using utilities::socket_abstract;
using utilities::timer;

////////////////////////////////////////////////////////////////////////////////////////////////////

fsw::fsw() : 
thread("fsw_api_thread",thread::PR1),
mc_period_msec(20),
m_dyn_cmd_pkt(dyn_cmd_pkt::API),
m_pos_pkt(pos_pkt::VICON),
m_mag_pkt(mag_pkt::VICON) {
  launch();
}
fsw::~fsw() {
  terminate();
}
void fsw::hold_velocity(float v_f, float v_r, float v_d, float psi_rate) {
  m_dyn_cmd_pkt.mode = ctrl_mode_pkt::POSITION_HOLD_MODE;
  m_dyn_cmd_pkt.ch1 = -v_d;
  m_dyn_cmd_pkt.ch2 = v_r;
  m_dyn_cmd_pkt.ch3 = -v_f;
  m_dyn_cmd_pkt.ch4 = psi_rate;

  m_dyn_cmd_pkt.bound();

  tx_dyn_cmd_pkt.push(m_dyn_cmd_pkt);
}
void fsw::hold_attitude(float roll, float pitch, float yaw, float acc_d){
  m_dyn_cmd_pkt.mode = ctrl_mode_pkt::TILT_COMPENSATED_MODE;
  m_dyn_cmd_pkt.ch1 = -acc_d;
  m_dyn_cmd_pkt.ch2 = roll;
  m_dyn_cmd_pkt.ch3 = pitch;
  m_dyn_cmd_pkt.ch4 = yaw;

  m_dyn_cmd_pkt.bound();

  tx_dyn_cmd_pkt.push(m_dyn_cmd_pkt);
}
void fsw::hold_motor(float m1, float m2, float m3, float m4){
  m_dyn_cmd_pkt.mode = ctrl_mode_pkt::MOTOR_CTRL_MODE;
  m_dyn_cmd_pkt.ch1 = m1;
  m_dyn_cmd_pkt.ch2 = m2;
  m_dyn_cmd_pkt.ch3 = m3;
  m_dyn_cmd_pkt.ch4 = m4;

  m_dyn_cmd_pkt.bound();

  tx_dyn_cmd_pkt.push(m_dyn_cmd_pkt);
}

void fsw::update_position(float p_n, float p_e, float p_d){
  m_pos_pkt.pos_ned(0) = p_n;
  m_pos_pkt.pos_ned(1) = p_e;
  m_pos_pkt.pos_ned(2) = p_d;

  tx_pos_pkt.push(m_pos_pkt);
}
void fsw::update_magnetometer(float f, float r, float d){
  m_mag_pkt.mag(0) = f;
  m_mag_pkt.mag(1) = r;
  m_mag_pkt.mag(2) = d;

  tx_mag_pkt.push(m_mag_pkt);
}
bool fsw::get_orientation(float (&q_n2b)[4]){
  ahrs_data_pkt quat_data;
  if(rx_ahrs_data_pkt.pull(quat_data)){
    q_n2b[0] = quat_data.q_n2b.w();
    q_n2b[1] = quat_data.q_n2b.x();
    q_n2b[2] = quat_data.q_n2b.y();
    q_n2b[3] = quat_data.q_n2b.z();

    return true;
  }
  else{
    return false;
  }
}
bool fsw::get_gyro(float (&gyro)[3]){
  imu_pkt gyro_data;
  if(rx_imu_pkt.pull(gyro_data)){
    gyro[0] = gyro_data.gyro(0);
    gyro[1] = gyro_data.gyro(1);
    gyro[2] = gyro_data.gyro(2);

    return true;
  }
  else{
    return false;
  }
}
bool fsw::get_pwm(float (&pwm)[6]){
  pwm_pkt pwm_data;
  if(rx_pwm_pkt.pull(pwm_data)){
    pwm[0] = pwm_data.ch1;
    pwm[1] = pwm_data.ch2;
    pwm[2] = pwm_data.ch3; 
    pwm[3] = pwm_data.ch4;
    pwm[4] = pwm_data.ch5;
    pwm[5] = pwm_data.ch6;

    return true;
  }
  else{
    return false;
  }
}
bool fsw::launch() {
  if (!is_running()) {
    m_dyn_cmd_pkt.mode = ctrl_mode_pkt::STANDBY_MODE;
    m_dyn_cmd_pkt.ch1 = 0.0f;
    m_dyn_cmd_pkt.ch2 = 0.0f;
    m_dyn_cmd_pkt.ch3 = 0.0f;
    m_dyn_cmd_pkt.ch4 = 0.0f;

    m_pos_pkt.pos_ned(0) = 0.0f;
    m_pos_pkt.pos_ned(1) = 0.0f;
    m_pos_pkt.pos_ned(2) = 0.0f;

    m_mag_pkt.mag(0) = 0.0f;
    m_mag_pkt.mag(1) = 0.0f;
    m_mag_pkt.mag(2) = 0.0f;
  }
  return thread::launch();
}
bool fsw::terminate() {
  return thread::terminate();
}
void fsw::execute() {
  // Init comms
  receiver crosslink_rx("127.0.0.1:"+port_ext_xlrx,socket_abstract::UDP);
  crosslink_rx.set_exec_count(1);

  transmitter crosslink_tx("127.0.0.1:"+port_ext_xltx,
                           "127.0.0.1:"+port_fsw_xlrx,socket_abstract::UDP);
  crosslink_tx.set_exec_count(1);

  transmitter uplink("127.0.0.1:"+port_gcs_ul,
                           "192.168.1.207:"+port_fsw_ul,socket_abstract::UDP);
  uplink.set_exec_count(1);

  receiver downlink("127.0.0.1:"+port_gcs_log,socket_abstract::UDP);

  downlink.set_exec_count(1);



  // Init command packets
  tx_dyn_cmd_pkt.set_name(name()+"::tx_dyn_cmd_pkt");
  crosslink_tx.rx_dyn_cmd_pkt.set_max_queue_size(1);
  tx_dyn_cmd_pkt >> crosslink_tx.rx_dyn_cmd_pkt;

  // Init position packets
  tx_pos_pkt.set_name(name()+"::tx_pos_pkt");
  uplink.rx_pos_pkt.set_max_queue_size(1);
  tx_pos_pkt >> uplink.rx_pos_pkt;

  // Init mag packets
  tx_mag_pkt.set_name(name()+"::tx_mag_pkt");
  uplink.rx_mag_pkt.set_max_queue_size(1);
  tx_mag_pkt >> uplink.rx_mag_pkt;

  // Init quat packets
  rx_ahrs_data_pkt.set_name(name()+"::rx_ahrs_data_pkt");
  rx_ahrs_data_pkt.set_max_queue_size(1);
  rx_ahrs_data_pkt << downlink.tx_ahrs_data_pkt;

  // Init gyro packets
  rx_imu_pkt.set_name(name()+"::rx_imu_pkt");
  rx_imu_pkt.set_max_queue_size(1);
  rx_imu_pkt << downlink.tx_imu_pkt;

  // Init pwm packets
  rx_pwm_pkt.set_name(name()+"::rx_pwm_pkt");
  rx_pwm_pkt.set_max_queue_size(1);
  rx_pwm_pkt << downlink.tx_pwm_pkt;

  // Instantiate local timer.
  timer clock(name()+"_exec",mc_period_msec);
  
  // Run timed loop.
  for (clock.reset(); keep_running(); ++clock.await_target()) {
    // Get timestamp for current loop.
    float ts = timer::get_timestamp().to_sec();
    
    // Execute module.
    crosslink_rx.execute(ts);
    crosslink_tx.execute(ts);
    uplink.execute(ts);
    downlink.execute(ts);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
