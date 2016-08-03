////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/ahrs_gains_pkt.cpp                                                          //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/ahrs_gains_pkt.h"
using messages::ahrs_gains_pkt;
using std::ostream;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

ahrs_gains_pkt::ahrs_gains_pkt(SRC src) : packet(AHRS_GAINS_PKT) {
  std_P_qq_0 = 0.0f;
  std_P_bb_0_dps = 0.0f;
  std_gyro_dps = 0.0f;
  std_b_gyro_dps2 = 0.0f;
  std_pseudo_q_norm = 0.0f;
  std_grav_gs = 0.0f;
  std_hdg_deg = 0.0f;
  n_imu_samples = 0;
  n_mag_samples = 0;
  tau = 0.0f;
  grav_update_threshold_gs = 0.0f;
  max_hdg_innov_deg = 0.0f;
  mag_dec_deg = 0.0f;
  
  var_P_qq_0 = 0.0f;
  var_P_bb_0 = 0.0f;
  var_gyro = 0.0f;
  var_b_gyro = 0.0f;
  var_pseudo_q_norm = 0.0f;
  var_grav_gs = 0.0f;
  var_hdg = 0.0f;
  tau_inv = 0.0f;
  max_hdg_innov = 0.0f;
  mag_dec = 0.0f;
  
  packet::set_src(src);
}
ahrs_gains_pkt& ahrs_gains_pkt::operator=(const ahrs_gains_pkt& rhs) {
  packet::operator=(rhs);
  std_P_qq_0 = rhs.std_P_qq_0;
  std_P_bb_0_dps = rhs.std_P_bb_0_dps;
  std_gyro_dps = rhs.std_gyro_dps;
  std_b_gyro_dps2 = rhs.std_b_gyro_dps2;
  std_pseudo_q_norm = rhs.std_pseudo_q_norm;
  std_grav_gs = rhs.std_grav_gs;
  std_hdg_deg = rhs.std_hdg_deg;
  n_imu_samples = rhs.n_imu_samples;
  n_mag_samples = rhs.n_mag_samples;
  tau = rhs.tau;
  grav_update_threshold_gs = rhs.grav_update_threshold_gs;
  max_hdg_innov_deg = rhs.max_hdg_innov_deg;
  mag_dec_deg = rhs.mag_dec_deg;
  return *this;
}
void ahrs_gains_pkt::fill() {
  var_P_qq_0 = powf(std_P_qq_0,2.0f);
  var_P_bb_0 = powf(std_P_bb_0_dps*utilities::constants::deg2rad,2.0f);
  var_gyro = powf(std_gyro_dps*utilities::constants::deg2rad,2.0f);
  var_b_gyro = powf(std_b_gyro_dps2*utilities::constants::deg2rad,2.0f);
  var_pseudo_q_norm = powf(std_pseudo_q_norm,2.0f);
  var_grav_gs = powf(std_grav_gs,2.0f);
  var_hdg = powf(std_hdg_deg*utilities::constants::deg2rad,2.0f);
  tau_inv = 1.0f/tau;
  max_hdg_innov = max_hdg_innov_deg*utilities::constants::deg2rad;
  mag_dec = mag_dec_deg*utilities::constants::deg2rad;
}
string ahrs_gains_pkt::src_label() const {
  static const char* src_labels[] = {
      "UNDEFINED",
      "AHRS"
  };
  return string(src_labels[src()]);
}
string ahrs_gains_pkt::header() const {
  string str;
  str += "std_P_qq_0"+DEFAULT_DELIM;
  str += "std_P_bb_0_dps"+DEFAULT_DELIM;
  str += "std_gyro_dps"+DEFAULT_DELIM;
  str += "std_b_gyro_dps2"+DEFAULT_DELIM;
  str += "std_pseudo_q_norm"+DEFAULT_DELIM;
  str += "std_grav_gs"+DEFAULT_DELIM;
  str += "std_hdg_deg"+DEFAULT_DELIM;
  str += "n_imu_samples"+DEFAULT_DELIM;
  str += "n_mag_samples"+DEFAULT_DELIM;
  str += "tau"+DEFAULT_DELIM;
  str += "grav_update_threshold_gs"+DEFAULT_DELIM;
  str += "max_hdg_innov_deg"+DEFAULT_DELIM;
  str += "mag_dec_deg";
  return str;
}
uint32 ahrs_gains_pkt::derived_size() const {
  return sizeof(std_P_qq_0)+
         sizeof(std_P_bb_0_dps)+
         sizeof(std_gyro_dps)+
         sizeof(std_b_gyro_dps2)+
         sizeof(std_pseudo_q_norm)+
         sizeof(std_grav_gs)+
         sizeof(std_hdg_deg)+
         sizeof(n_imu_samples)+
         sizeof(n_mag_samples)+
         sizeof(tau)+
         sizeof(grav_update_threshold_gs)+
         sizeof(max_hdg_innov_deg)+
         sizeof(mag_dec_deg);
}
uint8* ahrs_gains_pkt::derived_serialize(uint8* msg) const {
  msg = serialize_elem(msg,std_P_qq_0);
  msg = serialize_elem(msg,std_P_bb_0_dps);
  msg = serialize_elem(msg,std_gyro_dps);
  msg = serialize_elem(msg,std_b_gyro_dps2);
  msg = serialize_elem(msg,std_pseudo_q_norm);
  msg = serialize_elem(msg,std_grav_gs);
  msg = serialize_elem(msg,std_hdg_deg);
  msg = serialize_elem(msg,n_imu_samples);
  msg = serialize_elem(msg,n_mag_samples);
  msg = serialize_elem(msg,tau);
  msg = serialize_elem(msg,grav_update_threshold_gs);
  msg = serialize_elem(msg,max_hdg_innov_deg);
  msg = serialize_elem(msg,mag_dec_deg);
  return msg;
}
const uint8* ahrs_gains_pkt::derived_deserialize(const uint8* msg) {
  msg = deserialize_elem(msg,std_P_qq_0);
  msg = deserialize_elem(msg,std_P_bb_0_dps);
  msg = deserialize_elem(msg,std_gyro_dps);
  msg = deserialize_elem(msg,std_b_gyro_dps2);
  msg = deserialize_elem(msg,std_pseudo_q_norm);
  msg = deserialize_elem(msg,std_grav_gs);
  msg = deserialize_elem(msg,std_hdg_deg);
  msg = deserialize_elem(msg,n_imu_samples);
  msg = deserialize_elem(msg,n_mag_samples);
  msg = deserialize_elem(msg,tau);
  msg = deserialize_elem(msg,grav_update_threshold_gs);
  msg = deserialize_elem(msg,max_hdg_innov_deg);
  msg = deserialize_elem(msg,mag_dec_deg);
  return msg;
}
void ahrs_gains_pkt::derived_format(ostream& stream) const {
  stream << std::scientific
         << std::showpos
         << std::setprecision(DEFAULT_PRECISION)
         << std::setw(DEFAULT_WIDTH) << std_P_qq_0 << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << std_P_bb_0_dps << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << std_gyro_dps << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << std_b_gyro_dps2 << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << std_pseudo_q_norm << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << std_grav_gs << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << std_hdg_deg << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << n_imu_samples << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << n_mag_samples << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << tau << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << grav_update_threshold_gs << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_hdg_innov_deg << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << mag_dec_deg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
