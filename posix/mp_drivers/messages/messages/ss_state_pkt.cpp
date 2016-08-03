////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/ss_state_pkt.cpp                                                            //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/ss_state_pkt.h"
using messages::ss_state_pkt;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

ss_state_pkt::ss_state_pkt() : state<SS_STATE_PKT>() {
	// Do nothing.
}
ss_state_pkt::ss_state_pkt(STATE s) : state<SS_STATE_PKT>(s) {
	// Do nothing.
}
void ss_state_pkt::set_src(SRC src) {
  state<SS_STATE_PKT>::set_src(src);
}
string ss_state_pkt::src_label() const {
  static const char* src_labels[] = {
    "UNDEFINED",
    "GCS"
  };
  return string(src_labels[src()]);
}
const string ss_state_pkt::state_label() const {
  static const char* state_names[] = {
    "GCS_CTRL",
    "API_CTRL"
  };
  return string(state_names[index()]);
}
bool ss_state_pkt::is_terminal() const {
  static const bool term_mask[] = {
    false,
    false
  };
  return term_mask[index()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
