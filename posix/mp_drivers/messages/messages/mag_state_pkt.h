////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/mag_state_pkt.h                                                             //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_MAG_STATE_PKT_H
#define MESSAGES_MAG_STATE_PKT_H

#include "messages/global_defs.h"
#include "messages/state.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  class mag_state_pkt : public state<MAG_STATE_PKT> {
    public:
      enum SRC {
        UNDEFINED
      };
      enum STATE {
        TERM,
        IDLE,
        NORMAL,
        MOCAP,
        SIM,
        CALIBRATE
      };
      
    public:
      mag_state_pkt();
      mag_state_pkt(STATE s);
      void set_src(SRC src);
      std::string src_label() const;
      const std::string state_label() const;
      bool is_terminal() const;
  };
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
