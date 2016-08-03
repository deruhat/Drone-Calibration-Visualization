////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/global_defs.h                                                               //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_GLOBAL_DEFS_H
#define MESSAGES_GLOBAL_DEFS_H

#include "utilities/global_defs.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace messages {
  const std::string port_fsw_ul = "6000";
  const std::string port_gcs_ul = "6050";
  const std::string port_fsw_dl = "6100";
  const std::string port_gcs_dl = "6150";
  const std::string port_fsw_log = "6200";
  const std::string port_gcs_log = "6250";
  const std::string port_fsw_xlrx = "8000";
  const std::string port_fsw_xltx = "8050";
  const std::string port_ext_xlrx = "8100";
  const std::string port_ext_xltx = "8150";
  
  enum MSG_ID {
    AHRS_DATA_PKT,
    AHRS_GAINS_PKT,
    AHRS_STATE_PKT,
    CTRL_DATA_PKT,
    CTRL_GAINS_PKT,
    CTRL_MODE_PKT,
    CTRL_STATE_PKT,
    DYN_CMD_PKT,
    HEALTH_STATE_PKT,
    IMU_PKT,
    IMU_STATE_PKT,
    MAG_PKT,
    MAG_STATE_PKT,
    PID_DATA_PKT,
    PID_GAINS_PKT,
    POS_PKT,
    PWM_PKT,
    PWM_STATE_PKT,
    QUAT_PKT,
    SIM_GAINS_PKT,
    SIM_STATE_PKT,
    SS_STATE_PKT
  };
  
  std::string msg_id_label(MSG_ID msg_id);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
