////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/ctrl_data_pkt.h                                                             //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_CTRL_DATA_PKT_H
#define MESSAGES_CTRL_DATA_PKT_H

#include "messages/global_defs.h"
#include "messages/packet.h"
#include "messages/pid_data_pkt.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  class ctrl_data_pkt : public packet {
    public:
      enum SRC {
        UNDEFINED,
        CONTROL
      };
      
    public:
      pid_data_pkt accl_z; // accl_z PID data packet
      pid_data_pkt omega_x; // omega_x PID data packet
      pid_data_pkt omega_y; // omega_y PID data packet
      pid_data_pkt omega_z; // omega_z PID data packet
      
    public:
      ctrl_data_pkt(SRC src=UNDEFINED);
      std::string src_label() const;
      std::string header() const;
    private:
      uint32 derived_size() const;
      uint8* derived_serialize(uint8* msg) const;
      const uint8* derived_deserialize(const uint8* msg);
      void derived_format(std::ostream& stream) const;
      void timestamp();
      void timestamp(float ts);
  };
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
