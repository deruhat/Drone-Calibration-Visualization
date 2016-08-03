////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/sim_gains_pkt.h                                                             //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_SIM_GAINS_PKT_H
#define MESSAGES_SIM_GAINS_PKT_H

#include "messages/global_defs.h"
#include "messages/packet.h"
#include "messages/pid_gains_pkt.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  class sim_gains_pkt : public packet {
    public:
      enum SRC {
        UNDEFINED,
        SIM
      };
      
    public:
      v3x1 r_i_ned; // Initial position in NED frame [m]
      v3x1 v_i_ned; // Initial velocity in NED frame [m/s]
      float roll_i; // Initial roll angle [rad]
      float pitch_i; // Initial pitch angle [rad]
      float yaw_i; // Initial yaw angle [rad]
      v3x1 omega_i; // Initial body rate [rad/s]
      float m; // vehicle mass [kg]
      float L; // boom moment arm [m]
      float cT;
      float cM2cT; // ratio of propeller moment to propeller thrust coefficient [m]
      float S; // drag reference area [m^2]
      float cD; // vehicle drag force coefficient
      float cM; // vehicle drag torque coefficient
      float rho; // air density [kg/m^3]
      float tau_up; // motor throttle-up time constant [s]
      float tau_down; // motor throttle-down time constant [s]
      m3x3 J; // vehicle inertia tensor [kg*m^2]
      
    public:
        sim_gains_pkt(SRC src=UNDEFINED);
        sim_gains_pkt& operator=(const sim_gains_pkt& rhs);
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
