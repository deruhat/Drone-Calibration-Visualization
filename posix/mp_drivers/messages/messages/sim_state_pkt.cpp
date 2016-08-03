////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/sim_state_pkt.cpp                                                           //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/sim_state_pkt.h"
using messages::sim_state_pkt;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

sim_state_pkt::sim_state_pkt() : state<SIM_STATE_PKT>() {
  // Do nothing.
}
sim_state_pkt::sim_state_pkt(STATE s) : state<SIM_STATE_PKT>(s) {
  // Do nothing.
}
void sim_state_pkt::set_src(SRC src) {
  state<SIM_STATE_PKT>::set_src(src);
}
string sim_state_pkt::src_label() const {
  static const char* src_labels[] = {
    "UNDEFINED",
    "SIM"
  };
  return string(src_labels[src()]);
}
const string sim_state_pkt::state_label() const {
  static const char* state_names[] = {
    "TERM",
    "IDLE",
    "RESET",
    "NORMAL"
  };
  return string(state_names[index()]);
}
bool sim_state_pkt::is_terminal() const {
  static const bool term_mask[] = {
    true,
    false,
    false,
    false
  };
  return term_mask[index()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
