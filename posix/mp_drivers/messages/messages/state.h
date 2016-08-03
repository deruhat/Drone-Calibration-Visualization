////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/state.h                                                                     //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_STATE_H
#define MESSAGES_STATE_H

#include "messages/global_defs.h"
#include "utilities/state.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  template <MSG_ID PKT_ID> class state : public utilities::state<MSG_ID,PKT_ID> {
    public:
      state() : utilities::state<MSG_ID,PKT_ID>() {
        // Do nothing.
      }
      state(uint8 s) : utilities::state<MSG_ID,PKT_ID>(s) {
        // Do nothing.
      }
      virtual ~state() {
        // Do nothing.
      }
      std::string id_label() const {
        return msg_id_label(utilities::state<MSG_ID,PKT_ID>::id());
      }
  };
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
