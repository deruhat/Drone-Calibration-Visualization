////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/ctrl_mode_pkt.h                                                             //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_CTRL_MODE_PKT_H
#define MESSAGES_CTRL_MODE_PKT_H

#include "messages/global_defs.h"
#include "messages/state.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  class ctrl_mode_pkt : public state<CTRL_MODE_PKT> {
    public:
      enum SRC {
        UNDEFINED
      };
      enum STATE {
        STANDBY_MODE,
        MOTOR_CTRL_MODE,
        INERTIAL_CTRL_MODE_1,
        INERTIAL_CTRL_MODE_2,
        INERTIAL_CTRL_MODE_3,
        TILT_COMPENSATED_MODE,
        ALTITUDE_HOLD_MODE,
        POSITION_HOLD_MODE,
        PVA_MODE
      };
      
    public:
      ctrl_mode_pkt(SRC src=UNDEFINED);
      ctrl_mode_pkt(STATE s, SRC src=UNDEFINED);
      std::string src_label() const;
      const std::string state_label() const;
      bool is_terminal() const;
  };
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
