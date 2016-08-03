////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/packet.h                                                                    //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_PACKET_H
#define MESSAGES_PACKET_H

#include "messages/global_defs.h"
#include "utilities/packet.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  class packet : public utilities::packet<MSG_ID> {
    public:
      packet(MSG_ID msg_id);
      virtual ~packet();
      std::string id_label() const;
  };
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
