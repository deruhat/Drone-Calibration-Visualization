////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/dyn_cmd_pkt.h                                                               //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_DYN_CMD_PKT_H
#define MESSAGES_DYN_CMD_PKT_H

#include "messages/ctrl_mode_pkt.h"
#include "messages/global_defs.h"
#include "messages/packet.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  class dyn_cmd_pkt : public packet {
    public:
      enum SRC {
        UNDEFINED,
        GCS,
        API
      };
      
    public:
      ctrl_mode_pkt mode; // control mode
      float ch1; // channel 1 [-1.0,1.0]
      float ch2; // channel 2 [-1.0,1.0]
      float ch3; // channel 3 [-1.0,1.0]
      float ch4; // channel 4 [-1.0,1.0]
      
    public:
      dyn_cmd_pkt(SRC src=UNDEFINED);
      dyn_cmd_pkt(const dyn_cmd_pkt& data, SRC src=UNDEFINED);
      void bound();
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
