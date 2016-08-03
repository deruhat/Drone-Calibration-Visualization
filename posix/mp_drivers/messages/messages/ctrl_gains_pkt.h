////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/ctrl_gains_pkt.h                                                            //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_CTRL_GAINS_PKT_H
#define MESSAGES_CTRL_GAINS_PKT_H

#include "messages/global_defs.h"
#include "messages/packet.h"
#include "messages/pid_gains_pkt.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  class ctrl_gains_pkt : public packet {
    public:
      enum SRC {
        UNDEFINED,
        CONTROL
      };
      
    public:
      float wn_ne;
      float zeta_ne;
      float wn_d;
      float zeta_d;
      float min_altitude;
      float max_altitude;
      float max_north_pos;
      float max_south_pos;
      float max_east_pos;
      float max_west_pos;
      float max_hvel;
      float max_vvel;
      
      float max_tilt_deg; // maximum allowed tilt angle [deg]
      float max_load_factor; // maximum allowed load factor
      float max_pwm_coll_rate; // maximum allowed PWM collective rate [us/s]
      float max_hdg_rate_dps; // maximum allowed heading rate [deg/s]
      float min_Ts_gs; // minimum allowed reference specific thrust [g's]
      float max_Ts_gs; // maximum allowed reference specific thrust [g's]
      float max_delta_Ts_gs; // maximum allowed reference specific thrust control increment [g's]
      float max_omega_xy_dps; // maximum allowed x- and y-axis body-rate [deg/s]
      float max_omega_z_dps; // maximum allowed z-axis body-rate [deg/s]
      float min_coll_pwm; // minimum allowed pulse-width collective control authority [us]
      float max_coll_pwm; // maximum allowed pulse-width collective control authority [us]
      float max_att_pwm; // maximum allowed pulse-width attitude control authority [us]
      float max_test_pwm; // maximum allowed pulse-width in MOTOR_CTRL_MODE [us]
      float zero_thrust_pwm; // zero-thrust pulse-width [us]
      float att_p_gain; // attitude control proportional gain
      pid_gains_pkt Ts_ne_pid; // specific thrust north-east PID gains
      pid_gains_pkt Ts_z_pid; // specific thrust z-body PID gains
      pid_gains_pkt omega_xy_pid; // xy body-rate PID gains
      pid_gains_pkt omega_z_pid; // z body-rate PID gains
      
      float max_tilt; // maximum allowed tilt angle [rad]
      float max_hdg_rate; // maximum allowed heading rate [rad/s]
      float min_Ts; // minimum allowed reference specific thrust [m/s^2]
      float max_Ts; // maximum allowed reference specific thrust [m/s^2]
      float max_delta_Ts; // maximum allowed reference specific thrust control increment [m/s^2]
      float max_omega_xy; // maximum allowed x- and y-axis body-rate [rad/s]
      float max_omega_z; // maximum allowed z-axis body-rate [rad/s]
      
    public:
        ctrl_gains_pkt(SRC src=UNDEFINED);
        ctrl_gains_pkt& operator=(const ctrl_gains_pkt& rhs);
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
