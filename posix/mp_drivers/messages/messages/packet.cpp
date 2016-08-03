////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/packet.cpp                                                                  //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/packet.h"
using messages::packet;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

packet::packet(MSG_ID msg_id) : utilities::packet<MSG_ID>(msg_id) {
  // Do nothing.
}
packet::~packet() {
  // Do nothing.
}
string packet::id_label() const {
  return msg_id_label(id());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
