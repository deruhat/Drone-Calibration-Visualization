////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/pid_gains_pkt.h                                                             //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_PID_GAINS_PKT_H
#define MESSAGES_PID_GAINS_PKT_H

#include "messages/global_defs.h"
#include "messages/packet.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  class pid_gains_pkt : public packet {
    public:
      enum SRC {
        UNDEFINED
      };
      
    public:
      float k_p; // proportional gain
      float k_i; // integral gain
      float k_d; // derivative gain
      float int_min; // lower bound on integral
      float int_max; // upper bound on integral
      
    public:
      pid_gains_pkt();
      void set_src(SRC src);
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
