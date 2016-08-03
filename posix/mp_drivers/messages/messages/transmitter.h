////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/transmitter.h                                                               //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_TRANSMITTER_H
#define MESSAGES_TRANSMITTER_H

#include "messages/all_messages.h"
#include "messages/global_defs.h"
#include "utilities/consprod.h"
#include "utilities/socket_abstract.h"
#include "utilities/utl_module.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  class transmitter : public utilities::utl_module {
    public:
      utilities::consumer<ahrs_data_pkt> rx_ahrs_data_pkt;
      utilities::consumer<ahrs_gains_pkt> rx_ahrs_gains_pkt;
      utilities::consumer<ahrs_state_pkt> rx_ahrs_state_pkt;
      utilities::consumer<ctrl_data_pkt> rx_ctrl_data_pkt;
      utilities::consumer<ctrl_gains_pkt> rx_ctrl_gains_pkt;
      utilities::consumer<ctrl_mode_pkt> rx_ctrl_mode_pkt;
      utilities::consumer<ctrl_state_pkt> rx_ctrl_state_pkt;
      utilities::consumer<dyn_cmd_pkt> rx_dyn_cmd_pkt;
      utilities::consumer<health_state_pkt> rx_health_state_pkt;
      utilities::consumer<imu_pkt> rx_imu_pkt;
      utilities::consumer<imu_state_pkt> rx_imu_state_pkt;
      utilities::consumer<mag_pkt> rx_mag_pkt;
      utilities::consumer<mag_state_pkt> rx_mag_state_pkt;
      utilities::consumer<pid_data_pkt> rx_pid_data_pkt;
      utilities::consumer<pid_gains_pkt> rx_pid_gains_pkt;
      utilities::consumer<pos_pkt> rx_pos_pkt;
      utilities::consumer<pwm_pkt> rx_pwm_pkt;
      utilities::consumer<pwm_state_pkt> rx_pwm_state_pkt;
      utilities::consumer<quat_pkt> rx_quat_pkt;
      utilities::consumer<sim_gains_pkt> rx_sim_gains_pkt;
      utilities::consumer<sim_state_pkt> rx_sim_state_pkt;
      utilities::consumer<ss_state_pkt> rx_ss_state_pkt;
      
    private:
      const std::string mc_local_address;
      const std::string mc_dest_address;
      utilities::socket_abstract* mp_socket;
      uint8 mp_buffer[2048];
      
    public:
      transmitter(const std::string& local_address,
                  const std::string& dest_address,
                  utilities::socket_abstract::TYPE sock_type,
                  uint32 exec_count=1);
      void flush_all();
    private:
      void exec(float ts);
      void initialize_variables();
      template <class T> inline void tx(utilities::consumer<T>& C, uint8*& ptr, uint32& w_bytes) {
        T pkt;
        while (C.pull(pkt)) {
          ptr = pkt.serialize(ptr);
          w_bytes += pkt.size();
        }
      }
  };
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
