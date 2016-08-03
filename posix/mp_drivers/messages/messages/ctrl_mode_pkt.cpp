////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/ctrl_mode_pkt.cpp                                                           //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/ctrl_mode_pkt.h"
using messages::ctrl_mode_pkt;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

ctrl_mode_pkt::ctrl_mode_pkt(SRC src) : state<CTRL_MODE_PKT>() {
  state<CTRL_MODE_PKT>::set_src(src);
}
ctrl_mode_pkt::ctrl_mode_pkt(STATE s, SRC src) : state<CTRL_MODE_PKT>(s) {
  state<CTRL_MODE_PKT>::set_src(src);
}
string ctrl_mode_pkt::src_label() const {
  static const char* src_labels[] = {
    "UNDEFINED"
  };
  return string(src_labels[src()]);
}
const string ctrl_mode_pkt::state_label() const {
  static const char* state_names[] = {
    "STANDBY_MODE",
    "MOTOR_CTRL_MODE",
    "INERTIAL_CTRL_MODE_1",
    "INERTIAL_CTRL_MODE_2",
    "INERTIAL_CTRL_MODE_3",
    "TILT_COMPENSATED_MODE",
    "ALTITUDE_HOLD_MODE",
    "POSITION_HOLD_MODE",
    "PVA_MODE"
  };
  return string(state_names[index()]);
}
bool ctrl_mode_pkt::is_terminal() const {
  static const bool term_mask[] = {
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false
  };
  return term_mask[index()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
