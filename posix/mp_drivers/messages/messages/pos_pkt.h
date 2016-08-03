////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/pos_pkt.h                                                                   //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_POS_PKT_H
#define MESSAGES_POS_PKT_H

#include "messages/global_defs.h"
#include "messages/packet.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  class pos_pkt : public packet {
    public:
      enum SRC {
        UNDEFINED,
        VICON
      };
      
    public:
      v3x1 pos_ned; // position in local NED coordinate frame [m]
      
    public:
      pos_pkt(SRC src=UNDEFINED);
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
