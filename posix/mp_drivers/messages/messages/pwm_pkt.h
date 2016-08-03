////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/pwm_pkt.h                                                                   //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_PWM_PKT_H
#define MESSAGES_PWM_PKT_H

#include "messages/global_defs.h"
#include "messages/packet.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  class pwm_pkt : public packet {
    public:
      enum SRC {
        UNDEFINED,
        CONTROL
      };
      
    public:
      float ch1; // channel 1 pulse width [900,2100] [usec]
      float ch2; // channel 2 pulse width [900,2100] [usec]
      float ch3; // channel 3 pulse width [900,2100] [usec]
      float ch4; // channel 4 pulse width [900,2100] [usec]
      float ch5; // channel 5 pulse width [900,2100] [usec]
      float ch6; // channel 6 pulse width [900,2100] [usec]
      
    public:
      pwm_pkt(SRC src=UNDEFINED);
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
