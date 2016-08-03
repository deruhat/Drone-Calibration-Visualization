////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    api/fsw.h                                                                            //
// DATE:     Fri Jan 22 01:07:17 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef API_FSW_H
#define API_FSW_H

#include "messages/receiver.h"
#include "messages/transmitter.h"
#include "utilities/thread.h"
#include "messages/all_messages.h"
#include "utilities/consprod.h"
using messages::dyn_cmd_pkt;
using messages::pos_pkt;
using messages::mag_pkt;
using messages::quat_pkt;
using messages::imu_pkt;
using messages::pwm_pkt;
using messages::ahrs_data_pkt;
using utilities::producer;
using utilities::consumer;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace api {
  class fsw : public utilities::thread {
    private:
      const uint32 mc_period_msec;

      dyn_cmd_pkt m_dyn_cmd_pkt;
      producer<dyn_cmd_pkt> tx_dyn_cmd_pkt;

      pos_pkt m_pos_pkt;
      producer<pos_pkt> tx_pos_pkt;

      mag_pkt m_mag_pkt;
      producer<mag_pkt> tx_mag_pkt;

      quat_pkt quat_data;
      consumer<ahrs_data_pkt> rx_ahrs_data_pkt;

      imu_pkt imu_data;
      consumer<imu_pkt> rx_imu_pkt;

      pwm_pkt pwm_data;
      consumer<pwm_pkt> rx_pwm_pkt;
      
    public:
      fsw();
      ~fsw();
      void hold_velocity(float v_f, float v_r, float v_d, float psi_rate);
      void hold_attitude(float roll, float pitch, float yaw, float a_z);
      void hold_motor(float m1, float m2, float m3, float m4);
      void update_position(float p_n, float p_e, float p_d);
      void update_magnetometer(float f, float r, float d);
      bool get_orientation(float (&q_n2b)[4]);
      bool get_gyro(float (&gyro)[3]);
      bool get_pwm(float (&pwm)[6]);

    private:
      bool launch();
      bool terminate();
      void execute();
  };
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
