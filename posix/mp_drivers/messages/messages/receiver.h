////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/receiver.h                                                                  //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_RECEIVER_H
#define MESSAGES_RECEIVER_H

#include "messages/all_messages.h"
#include "messages/global_defs.h"
#include "utilities/consprod.h"
#include "utilities/socket_abstract.h"
#include "utilities/utl_module.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  class receiver : public utilities::utl_module {
    public:
      utilities::producer<ahrs_data_pkt> tx_ahrs_data_pkt;
      utilities::producer<ahrs_gains_pkt> tx_ahrs_gains_pkt;
      utilities::producer<ahrs_state_pkt> tx_ahrs_state_pkt;
      utilities::producer<ctrl_data_pkt> tx_ctrl_data_pkt;
      utilities::producer<ctrl_gains_pkt> tx_ctrl_gains_pkt;
      utilities::producer<ctrl_mode_pkt> tx_ctrl_mode_pkt;
      utilities::producer<ctrl_state_pkt> tx_ctrl_state_pkt;
      utilities::producer<dyn_cmd_pkt> tx_dyn_cmd_pkt;
      utilities::producer<health_state_pkt> tx_health_state_pkt;
      utilities::producer<imu_pkt> tx_imu_pkt;
      utilities::producer<imu_state_pkt> tx_imu_state_pkt;
      utilities::producer<mag_pkt> tx_mag_pkt;
      utilities::producer<mag_state_pkt> tx_mag_state_pkt;
      utilities::producer<pid_data_pkt> tx_pid_data_pkt;
      utilities::producer<pid_gains_pkt> tx_pid_gains_pkt;
      utilities::producer<pos_pkt> tx_pos_pkt;
      utilities::producer<pwm_pkt> tx_pwm_pkt;
      utilities::producer<pwm_state_pkt> tx_pwm_state_pkt;
      utilities::producer<quat_pkt> tx_quat_pkt;
      utilities::producer<sim_gains_pkt> tx_sim_gains_pkt;
      utilities::producer<sim_state_pkt> tx_sim_state_pkt;
      utilities::producer<ss_state_pkt> tx_ss_state_pkt;
      
    private:
      const std::string mc_local_address;
      utilities::socket_abstract* mp_socket;
      uint8 mp_buffer[2048];
      
    public:
      receiver(const std::string& local_address,
               utilities::socket_abstract::TYPE sock_type,
               uint32 exec_count=1);
    private:
      void exec(float ts);
      void initialize_variables();
      template <class T> inline void rx(utilities::producer<T>& P, const uint8*& ptr) {
        T pkt;
        ptr = pkt.deserialize(ptr);
        P.push(pkt);
      }
  };
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
