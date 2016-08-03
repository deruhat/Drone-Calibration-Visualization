////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/global_defs.cpp                                                             //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/global_defs.h"
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

string messages::msg_id_label(MSG_ID msg_id) {
  static const char* packet_labels[] = {
    "AHRS_DATA_PKT",
    "AHRS_GAINS_PKT",
    "AHRS_STATE_PKT",
    "CTRL_DATA_PKT",
    "CTRL_GAINS_PKT",
    "CTRL_MODE_PKT",
    "CTRL_STATE_PKT",
    "DYN_CMD_PKT",
    "HEALTH_STATE_PKT",
    "IMU_PKT",
    "IMU_STATE_PKT",
    "MAG_PKT",
    "MAG_STATE_PKT",
    "PID_DATA_PKT",
    "PID_GAINS_PKT",
    "POS_PKT",
    "PWM_PKT",
    "PWM_STATE_PKT",
    "QUAT_PKT",
    "SIM_GAINS_PKT",
    "SIM_STATE_PKT",
    "SS_STATE_PKT"
  };
  return string(packet_labels[msg_id]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
