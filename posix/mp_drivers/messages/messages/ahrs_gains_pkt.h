////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/ahrs_gains_pkt.h                                                            //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_AHRS_GAINS_PKT_H
#define MESSAGES_AHRS_GAINS_PKT_H

#include "messages/global_defs.h"
#include "messages/packet.h"
#include "utilities/dcm.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  class ahrs_gains_pkt : public packet {
    public:
      enum SRC {
        UNDEFINED,
        AHRS
      };
      
    public:
      float std_P_qq_0; // initial EKF quaternion state error standard deviation
      float std_P_bb_0_dps; // initial EKF gyro bias state error standard deviation [deg/s]
      float std_gyro_dps; // gyroscope measurement standard deviation [deg/s]
      float std_b_gyro_dps2; // gyroscope bias process noise standard deviation [deg/s^2]
      float std_pseudo_q_norm; // quaternion norm pseudo-measurement standard deviation
      float std_grav_gs; // gravity correction measurement standard deviation [g's]
      float std_hdg_deg; // heading measurement standard deviation [deg]
      uint32 n_imu_samples; // Number of IMU samples required for initialization.
      uint32 n_mag_samples; // Number of magnetometer samples required for initialization.
      float tau; // gyro bias time correlation factor [s]
      float grav_update_threshold_gs; // gravity update threshold [g's]
      float max_hdg_innov_deg; // maximum allowed heading innovation [deg]
      float mag_dec_deg; // local magnetic declination angle [deg]
      
      float var_P_qq_0; // initial EKF quaternion state error variance
      float var_P_bb_0; // initial EKF gyro bias state error variance [rad^2/s^2]
      float var_gyro; // gyroscope measurement variance [rad^2/s^2]
      float var_b_gyro; // gyroscope bias process noise variance [rad^2/s^4]
      float var_pseudo_q_norm; // quaternion norm pseudo-measurement variance
      float var_grav_gs; // gravity correction measurement variance [g's^2]
      float var_hdg; // heading measurement variance [rad^2]
      float tau_inv; // inverse of gyro bias time correlation factor [1/s]
      float max_hdg_innov; // maximum allowed heading innovation [rad]
      float mag_dec; // local magnetic declination angle [rad]
      
    public:
      ahrs_gains_pkt(SRC src=UNDEFINED);
      ahrs_gains_pkt& operator=(const ahrs_gains_pkt& rhs);
      void fill();
      std::string src_label() const;
      std::string header() const;
    private:
      uint32 derived_size() const;
      uint8* derived_serialize(uint8* msg) const;
      const uint8* derived_deserialize(const uint8* msg);
      void derived_format(std::ostream& stream) const;
  };
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
