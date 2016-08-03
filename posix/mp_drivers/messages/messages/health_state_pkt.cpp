////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/health_state_pkt.cpp                                                        //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/health_state_pkt.h"
using messages::health_state_pkt;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

health_state_pkt::health_state_pkt() : state<HEALTH_STATE_PKT>() {
  // Do nothing.
}
health_state_pkt::health_state_pkt(STATE s) : state<HEALTH_STATE_PKT>(s) {
  // Do nothing.
}
void health_state_pkt::set_src(SRC src) {
  state<HEALTH_STATE_PKT>::set_src(src);
}
string health_state_pkt::src_label() const {
  static const char* src_labels[] = {
    "UNDEFINED"
  };
  return string(src_labels[src()]);
}
const string health_state_pkt::state_label() const {
  static const char* state_names[] = {
    "GREEN",
    "YELLOW",
    "RED"
  };
  return string(state_names[index()]);
}
bool health_state_pkt::is_terminal() const {
  static const bool term_mask[] = {
    false,
    false,
    false
  };
  return term_mask[index()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
