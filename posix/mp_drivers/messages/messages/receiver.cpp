////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/receiver.cpp                                                                //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/receiver.h"
#include "utilities/socket_ipc.h"
#include "utilities/socket_udp.h"
using messages::receiver;
using std::string;
using utilities::socket_abstract;
using utilities::socket_ipc;
using utilities::socket_udp;

////////////////////////////////////////////////////////////////////////////////////////////////////

receiver::receiver(const string& local_address,
                   socket_abstract::TYPE sock_type,
                   uint32 exec_count) :
  utl_module("messages","receiver",exec_count),
  mc_local_address(local_address) {
  // Name producers.
  tx_ahrs_data_pkt.set_name(class_name()+"::tx_ahrs_data_pkt");
  tx_ahrs_gains_pkt.set_name(class_name()+"::tx_ahrs_gains_pkt");
  tx_ahrs_state_pkt.set_name(class_name()+"::tx_ahrs_state_pkt");
  tx_ctrl_data_pkt.set_name(class_name()+"::tx_ctrl_data_pkt");
  tx_ctrl_gains_pkt.set_name(class_name()+"::tx_ctrl_gains_pkt");
  tx_ctrl_mode_pkt.set_name(class_name()+"::tx_ctrl_mode_pkt");
  tx_ctrl_state_pkt.set_name(class_name()+"::tx_ctrl_state_pkt");
  tx_dyn_cmd_pkt.set_name(class_name()+"::tx_dyn_cmd_pkt");
  tx_health_state_pkt.set_name(class_name()+"::tx_health_state_pkt");
  tx_imu_pkt.set_name(class_name()+"::tx_imu_pkt");
  tx_imu_state_pkt.set_name(class_name()+"::tx_imu_state_pkt");
  tx_mag_pkt.set_name(class_name()+"::tx_mag_pkt");
  tx_mag_state_pkt.set_name(class_name()+"::tx_mag_state_pkt");
  tx_pid_data_pkt.set_name(class_name()+"::tx_pid_data_pkt");
  tx_pid_gains_pkt.set_name(class_name()+"::tx_pid_gains_pkt");
  tx_pos_pkt.set_name(class_name()+"::tx_pos_pkt");
  tx_pwm_pkt.set_name(class_name()+"::tx_pwm_pkt");
  tx_pwm_state_pkt.set_name(class_name()+"::tx_pwm_state_pkt");
  tx_quat_pkt.set_name(class_name()+"::tx_quat_pkt");
  tx_sim_gains_pkt.set_name(class_name()+"::tx_sim_gains_pkt");
  tx_sim_state_pkt.set_name(class_name()+"::tx_sim_state_pkt");
  tx_ss_state_pkt.set_name(class_name()+"::tx_ss_state_pkt");
  
  // Instantiate socket.
  switch (sock_type) {
    case socket_abstract::IPC:
      mp_socket = new socket_ipc("receiver",mc_local_address);
      break;
    case socket_abstract::UDP:
      mp_socket = new socket_udp("receiver",mc_local_address);
      break;
  }
  
  // Set socket to non-blocking.
  mp_socket->set_flags(socket_abstract::NON_BLOCKING);
  
  // Initialize variables.
  initialize_variables();
}
void receiver::exec(float ts) {
  UNUSED(ts)
  int32 bytes_received = 1;
  
  // Read all datagrams in socket buffer.
  while (bytes_received > 0) {
    bytes_received = mp_socket->recv(mp_buffer,2048);
    const uint8* ptr = &mp_buffer[0];
    
    while (ptr < &mp_buffer[bytes_received]) {
      switch (static_cast<MSG_ID>(*ptr)) {
        case AHRS_DATA_PKT:    rx(tx_ahrs_data_pkt,ptr);    break;
        case AHRS_GAINS_PKT:   rx(tx_ahrs_gains_pkt,ptr);   break;
        case AHRS_STATE_PKT:   rx(tx_ahrs_state_pkt,ptr);   break;
        case CTRL_DATA_PKT:    rx(tx_ctrl_data_pkt,ptr);    break;
        case CTRL_GAINS_PKT:   rx(tx_ctrl_gains_pkt,ptr);   break;
        case CTRL_MODE_PKT:    rx(tx_ctrl_mode_pkt,ptr);    break;
        case CTRL_STATE_PKT:   rx(tx_ctrl_state_pkt,ptr);   break;
        case DYN_CMD_PKT:      rx(tx_dyn_cmd_pkt,ptr);      break;
        case HEALTH_STATE_PKT: rx(tx_health_state_pkt,ptr); break;
        case IMU_PKT:          rx(tx_imu_pkt,ptr);          break;
        case IMU_STATE_PKT:    rx(tx_imu_state_pkt,ptr);    break;
        case MAG_PKT:          rx(tx_mag_pkt,ptr);          break;
        case MAG_STATE_PKT:    rx(tx_mag_state_pkt,ptr);    break;
        case PID_DATA_PKT:     rx(tx_pid_data_pkt,ptr);     break;
        case PID_GAINS_PKT:    rx(tx_pid_gains_pkt,ptr);    break;
        case POS_PKT:          rx(tx_pos_pkt,ptr);          break;
        case PWM_PKT:          rx(tx_pwm_pkt,ptr);          break;
        case PWM_STATE_PKT:    rx(tx_pwm_state_pkt,ptr);    break;
        case QUAT_PKT:         rx(tx_quat_pkt,ptr);         break;
        case SIM_GAINS_PKT:    rx(tx_sim_gains_pkt,ptr);    break;
        case SIM_STATE_PKT:    rx(tx_sim_state_pkt,ptr);    break;
        case SS_STATE_PKT:     rx(tx_ss_state_pkt,ptr);     break;
      }
    }
  }
}
void receiver::initialize_variables() {
  memset(mp_buffer,0,2048*sizeof(uint8));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
