////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/mag_state_pkt.cpp                                                           //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/mag_state_pkt.h"
using messages::mag_state_pkt;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

mag_state_pkt::mag_state_pkt() : state<MAG_STATE_PKT>() {
  // Do nothing.
}
mag_state_pkt::mag_state_pkt(STATE s) : state<MAG_STATE_PKT>(s) {
  // Do nothing.
}
void mag_state_pkt::set_src(SRC src) {
  state<MAG_STATE_PKT>::set_src(src);
}
string mag_state_pkt::src_label() const {
  static const char* src_labels[] = {
    "UNDEFINED"
  };
  return string(src_labels[src()]);
}
const string mag_state_pkt::state_label() const {
  static const char* state_names[] = {
    "TERM",
    "IDLE",
    "NORMAL",
    "MOCAP",
    "SIM",
    "CALIBRATE"
  };
  return string(state_names[index()]);
}
bool mag_state_pkt::is_terminal() const {
  static const bool term_mask[] = {
    true,
    false,
    false,
    false,
    false,
    false
  };
  return term_mask[index()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
