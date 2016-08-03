////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/ctrl_state_pkt.cpp                                                          //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/ctrl_state_pkt.h"
using messages::ctrl_state_pkt;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

ctrl_state_pkt::ctrl_state_pkt() : state<CTRL_STATE_PKT>() {
  // Do nothing.
}
ctrl_state_pkt::ctrl_state_pkt(STATE s) : state<CTRL_STATE_PKT>(s) {
  // Do nothing.
}
void ctrl_state_pkt::set_src(SRC src) {
  state<CTRL_STATE_PKT>::set_src(src);
}
string ctrl_state_pkt::src_label() const {
  static const char* src_labels[] = {
    "UNDEFINED",
    "CONTROL"
  };
  return string(src_labels[src()]);
}
const string ctrl_state_pkt::state_label() const {
  static const char* state_names[] = {
    "TERM",
    "IDLE",
    "NORMAL"
  };
  return string(state_names[index()]);
}
bool ctrl_state_pkt::is_terminal() const {
  static const bool term_mask[] = {
    true,
    false,
    false
  };
  return term_mask[index()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
