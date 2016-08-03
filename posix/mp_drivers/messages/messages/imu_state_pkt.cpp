////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/imu_state_pkt.cpp                                                           //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/imu_state_pkt.h"
using messages::imu_state_pkt;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

imu_state_pkt::imu_state_pkt() : state<IMU_STATE_PKT>() {
  // Do nothing.
}
imu_state_pkt::imu_state_pkt(STATE s) : state<IMU_STATE_PKT>(s) {
  // Do nothing.
}
void imu_state_pkt::set_src(SRC src) {
  state<IMU_STATE_PKT>::set_src(src);
}
string imu_state_pkt::src_label() const {
  static const char* src_labels[] = {
    "UNDEFINED"
  };
  return string(src_labels[src()]);
}
const string imu_state_pkt::state_label() const {
  static const char* state_names[] = {
    "TERM",
    "IDLE",
    "NORMAL",
    "SIM",
    "CALIBRATE"
  };
  return string(state_names[index()]);
}
bool imu_state_pkt::is_terminal() const {
  static const bool term_mask[] = {
    true,
    false,
    false,
    false,
    false
  };
  return term_mask[index()];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
