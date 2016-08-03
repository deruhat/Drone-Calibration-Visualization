////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/health_state_pkt.h                                                          //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_HEALTH_STATE_PKT_H
#define MESSAGES_HEALTH_STATE_PKT_H

#include "messages/global_defs.h"
#include "messages/state.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  class health_state_pkt : public state<HEALTH_STATE_PKT> {
    public:
      enum SRC {
        UNDEFINED
      };
      enum STATE {
        GREEN,
        YELLOW,
        RED
      };
      
    public:
      health_state_pkt();
      health_state_pkt(STATE s);
      void set_src(SRC src);
      std::string src_label() const;
      const std::string state_label() const;
      bool is_terminal() const;
  };
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
