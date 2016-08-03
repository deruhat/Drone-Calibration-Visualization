////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/quat_pkt.h                                                                  //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_QUAT_PKT_H
#define MESSAGES_QUAT_PKT_H

#include "messages/global_defs.h"
#include "messages/packet.h"
#include "utilities/quat.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  class quat_pkt : public packet {
    public:
      enum SRC {
        UNDEFINED,
        AHRS
      };
      enum FORMAT_MODE {
        RAW,
        EULER
      };
      
    public:
      utilities::quat<float> q; // unit attitude quaternion
    private:
      FORMAT_MODE m_format_mode;
      
    public:
      quat_pkt(SRC src=UNDEFINED);
      void set_format_mode(FORMAT_MODE format_mode);
      quat_pkt& operator=(const quat_pkt& rhs);
      std::string src_label() const;
      std::string header() const;
    private:
      uint32 derived_size() const;
      uint8* derived_serialize(uint8* msg) const;
      uint8 const* derived_deserialize(uint8 const* msg);
      void derived_format(std::ostream& stream) const;
  };
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
