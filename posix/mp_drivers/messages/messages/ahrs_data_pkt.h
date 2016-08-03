////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/ahrs_data_pkt.h                                                             //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_AHRS_DATA_PKT_H
#define MESSAGES_AHRS_DATA_PKT_H

#include "messages/global_defs.h"
#include "messages/packet.h"
#include "utilities/quat.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  class ahrs_data_pkt : public packet {
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
      utilities::quat<float> q_n2b; // unit attitude quaternion
      v3x1 b_gyro; // gyro biases [rad/s]
    private:
      FORMAT_MODE m_format_mode;
      
    public:
      ahrs_data_pkt(FORMAT_MODE format_mode=RAW);
      void set_format_mode(FORMAT_MODE format_mode);
      ahrs_data_pkt& operator=(const ahrs_data_pkt& rhs);
      void set_src(SRC src);
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
