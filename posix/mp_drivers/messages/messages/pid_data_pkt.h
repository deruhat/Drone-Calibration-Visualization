////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/pid_data_pkt.h                                                              //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_PID_DATA_PKT_H
#define MESSAGES_PID_DATA_PKT_H

#include "messages/global_defs.h"
#include "messages/packet.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  class pid_data_pkt : public packet {
    public:
      enum SRC {
        UNDEFINED,
        TS_N_PID,
        TS_E_PID,
        TS_Z_PID,
        OMEGA_X_PID,
        OMEGA_Y_PID,
        OMEGA_Z_PID
      };
      
    public:
      float reset; // reset coefficient (0.0 = reset, 1.0 = no reset)
      float u_p; // proportional control effort
      float u_i; // integral control effort
      float u_d; // derivative control effort
      float u; // total control effort
      float e; // error used in time step
      
    public:
      pid_data_pkt(SRC src=UNDEFINED);
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
