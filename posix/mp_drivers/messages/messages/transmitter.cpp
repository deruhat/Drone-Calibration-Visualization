////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/transmitter.cpp                                                             //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/transmitter.h"
#include "utilities/socket_ipc.h"
#include "utilities/socket_udp.h"
using messages::transmitter;
using std::string;
using utilities::socket_abstract;
using utilities::socket_ipc;
using utilities::socket_udp;

////////////////////////////////////////////////////////////////////////////////////////////////////

transmitter::transmitter(const string& local_address,
                         const string& dest_address,
                         socket_abstract::TYPE sock_type,
                         uint32 exec_count) :
  utl_module("messages","transmitter",exec_count),
  mc_local_address(local_address),
  mc_dest_address(dest_address) {
  // Name consumers.
  rx_ahrs_data_pkt.set_name(class_name()+"::rx_ahrs_data_pkt");
  rx_ahrs_gains_pkt.set_name(class_name()+"::rx_ahrs_gains_pkt");
  rx_ahrs_state_pkt.set_name(class_name()+"::rx_ahrs_state_pkt");
  rx_ctrl_data_pkt.set_name(class_name()+"::rx_ctrl_data_pkt");
  rx_ctrl_gains_pkt.set_name(class_name()+"::rx_ctrl_gains_pkt");
  rx_ctrl_mode_pkt.set_name(class_name()+"::rx_ctrl_mode_pkt");
  rx_ctrl_state_pkt.set_name(class_name()+"::rx_ctrl_state_pkt");
  rx_dyn_cmd_pkt.set_name(class_name()+"::rx_dyn_cmd_pkt");
  rx_health_state_pkt.set_name(class_name()+"::rx_health_state_pkt");
  rx_imu_pkt.set_name(class_name()+"::rx_imu_pkt");
  rx_imu_state_pkt.set_name(class_name()+"::rx_imu_state_pkt");
  rx_mag_pkt.set_name(class_name()+"::rx_mag_pkt");
  rx_mag_state_pkt.set_name(class_name()+"::rx_mag_state_pkt");
  rx_pid_data_pkt.set_name(class_name()+"::rx_pid_data_pkt");
  rx_pid_gains_pkt.set_name(class_name()+"::rx_pid_gains_pkt");
  rx_pos_pkt.set_name(class_name()+"::rx_pos_pkt");
  rx_pwm_pkt.set_name(class_name()+"::rx_pwm_pkt");
  rx_pwm_state_pkt.set_name(class_name()+"::rx_pwm_state_pkt");
  rx_quat_pkt.set_name(class_name()+"::rx_quat_pkt");
  rx_sim_gains_pkt.set_name(class_name()+"::rx_sim_gains_pkt");
  rx_sim_state_pkt.set_name(class_name()+"::rx_sim_state_pkt");
  rx_ss_state_pkt.set_name(class_name()+"::rx_ss_state_pkt");
  
  // Set consumer maximum queue sizes.
  rx_ahrs_data_pkt.set_max_queue_size(0);
  rx_ahrs_gains_pkt.set_max_queue_size(0);
  rx_ahrs_state_pkt.set_max_queue_size(0);
  rx_ctrl_data_pkt.set_max_queue_size(0);
  rx_ctrl_gains_pkt.set_max_queue_size(0);
  rx_ctrl_mode_pkt.set_max_queue_size(0);
  rx_ctrl_state_pkt.set_max_queue_size(0);
  rx_dyn_cmd_pkt.set_max_queue_size(0);
  rx_health_state_pkt.set_max_queue_size(0);
  rx_imu_pkt.set_max_queue_size(0);
  rx_imu_state_pkt.set_max_queue_size(0);
  rx_mag_pkt.set_max_queue_size(0);
  rx_mag_state_pkt.set_max_queue_size(0);
  rx_pid_data_pkt.set_max_queue_size(0);
  rx_pid_gains_pkt.set_max_queue_size(0);
  rx_pos_pkt.set_max_queue_size(0);
  rx_pwm_pkt.set_max_queue_size(0);
  rx_pwm_state_pkt.set_max_queue_size(0);
  rx_quat_pkt.set_max_queue_size(0);
  rx_sim_gains_pkt.set_max_queue_size(0);
  rx_sim_state_pkt.set_max_queue_size(0);
  rx_ss_state_pkt.set_max_queue_size(0);
  
  // Instantiate socket.
  switch (sock_type) {
    case socket_abstract::IPC:
      mp_socket = new socket_ipc("transmitter",mc_local_address);
      break;
    case socket_abstract::UDP:
      mp_socket = new socket_udp("transmitter",mc_local_address);
      break;
  }
  
  // Set socket to non-blocking.
  mp_socket->set_flags(socket_abstract::NON_BLOCKING);
  
  // Initialize variables.
  initialize_variables();
}
void transmitter::flush_all() {
  rx_ahrs_data_pkt.flush();
  rx_ahrs_gains_pkt.flush();
  rx_ahrs_state_pkt.flush();
  rx_ctrl_data_pkt.flush();
  rx_ctrl_gains_pkt.flush();
  rx_ctrl_mode_pkt.flush();
  rx_ctrl_state_pkt.flush();
  rx_dyn_cmd_pkt.flush();
  rx_health_state_pkt.flush();
  rx_imu_pkt.flush();
  rx_imu_state_pkt.flush();
  rx_mag_pkt.flush();
  rx_mag_state_pkt.flush();
  rx_pid_data_pkt.flush();
  rx_pid_gains_pkt.flush();
  rx_pos_pkt.flush();
  rx_pwm_pkt.flush();
  rx_pwm_state_pkt.flush();
  rx_quat_pkt.flush();
  rx_sim_gains_pkt.flush();
  rx_sim_state_pkt.flush();
  rx_ss_state_pkt.flush();
}
void transmitter::exec(float ts) {
  UNUSED(ts)
  uint8* ptr = &mp_buffer[0];
  uint32 bytes_written = 0;
  
  tx(rx_ahrs_data_pkt,ptr,bytes_written);
  tx(rx_ahrs_gains_pkt,ptr,bytes_written);
  tx(rx_ahrs_state_pkt,ptr,bytes_written);
  tx(rx_ctrl_data_pkt,ptr,bytes_written);
  tx(rx_ctrl_gains_pkt,ptr,bytes_written);
  tx(rx_ctrl_mode_pkt,ptr,bytes_written);
  tx(rx_ctrl_state_pkt,ptr,bytes_written);
  tx(rx_dyn_cmd_pkt,ptr,bytes_written);
  tx(rx_health_state_pkt,ptr,bytes_written);
  tx(rx_imu_pkt,ptr,bytes_written);
  tx(rx_imu_state_pkt,ptr,bytes_written);
  tx(rx_mag_pkt,ptr,bytes_written);
  tx(rx_mag_state_pkt,ptr,bytes_written);
  tx(rx_pid_data_pkt,ptr,bytes_written);
  tx(rx_pid_gains_pkt,ptr,bytes_written);
  tx(rx_pos_pkt,ptr,bytes_written);
  tx(rx_pwm_pkt,ptr,bytes_written);
  tx(rx_pwm_state_pkt,ptr,bytes_written);
  tx(rx_quat_pkt,ptr,bytes_written);
  tx(rx_sim_gains_pkt,ptr,bytes_written);
  tx(rx_sim_state_pkt,ptr,bytes_written);
  tx(rx_ss_state_pkt,ptr,bytes_written);
  
  mp_socket->send(mp_buffer,bytes_written,mc_dest_address);
}
void transmitter::initialize_variables() {
  memset(mp_buffer,0,2048*sizeof(uint8));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
