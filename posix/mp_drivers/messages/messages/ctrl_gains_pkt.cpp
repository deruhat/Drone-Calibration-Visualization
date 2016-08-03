////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/ctrl_gains_pkt.cpp                                                          //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/ctrl_gains_pkt.h"
using messages::ctrl_gains_pkt;
using std::ostream;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

ctrl_gains_pkt::ctrl_gains_pkt(SRC src) : packet(CTRL_GAINS_PKT) {
  wn_ne = 0.0f;
  zeta_ne = 0.0f;
  wn_d = 0.0f;
  zeta_d = 0.0f;
  min_altitude = 0.0f;
  max_altitude = 0.0f;
  max_north_pos = 0.0f;
  max_south_pos = 0.0f;
  max_east_pos = 0.0f;
  max_west_pos = 0.0f;
  max_hvel = 0.0f;
  max_vvel = 0.0f;
  
  max_tilt_deg = 0.0f;
  max_load_factor = 0.0f;
  max_pwm_coll_rate = 0.0f;
  max_hdg_rate_dps = 0.0f;
  min_Ts_gs = 0.0f;
  max_Ts_gs = 0.0f;
  max_delta_Ts_gs = 0.0f;
  max_omega_xy_dps = 0.0f;
  max_omega_z_dps = 0.0f;
  min_coll_pwm = 0.0f;
  max_coll_pwm = 0.0f;
  max_att_pwm = 0.0f;
  max_test_pwm = 0.0f;
  zero_thrust_pwm = 0.0f;
  att_p_gain = 0.0f;
  
  max_tilt = 0.0f;
  max_hdg_rate = 0.0f;
  min_Ts = 0.0f;
  max_Ts = 0.0f;
  max_delta_Ts = 0.0f;
  max_omega_xy = 0.0f;
  max_omega_z = 0.0f;
  
  packet::set_src(src);
}
ctrl_gains_pkt& ctrl_gains_pkt::operator=(const ctrl_gains_pkt& rhs) {
  packet::operator=(rhs);
  
  wn_ne = rhs.wn_ne;
  zeta_ne = rhs.zeta_ne;
  wn_d = rhs.wn_d;
  zeta_d = rhs.zeta_d;
  min_altitude = rhs.min_altitude;
  max_altitude = rhs.max_altitude;
  max_north_pos = rhs.max_north_pos;
  max_south_pos = rhs.max_south_pos;
  max_east_pos = rhs.max_east_pos;
  max_west_pos = rhs.max_west_pos;
  max_hvel = rhs.max_hvel;
  max_vvel = rhs.max_vvel;
  
  max_tilt_deg = rhs.max_tilt_deg;
  max_load_factor = rhs.max_load_factor;
  max_pwm_coll_rate = rhs.max_pwm_coll_rate;
  max_hdg_rate_dps = rhs.max_hdg_rate_dps;
  min_Ts_gs = rhs.min_Ts_gs;
  max_Ts_gs = rhs.max_Ts_gs;
  max_delta_Ts_gs = rhs.max_delta_Ts_gs;
  max_omega_xy_dps = rhs.max_omega_xy_dps;
  max_omega_z_dps = rhs.max_omega_z_dps;
  min_coll_pwm = rhs.min_coll_pwm;
  max_coll_pwm = rhs.max_coll_pwm;
  max_att_pwm = rhs.max_att_pwm;
  max_test_pwm = rhs.max_test_pwm;
  zero_thrust_pwm = rhs.zero_thrust_pwm;
  att_p_gain = rhs.att_p_gain;
  Ts_ne_pid = rhs.Ts_ne_pid;
  Ts_z_pid = rhs.Ts_z_pid;
  omega_xy_pid = rhs.omega_xy_pid;
  omega_z_pid = rhs.omega_z_pid;
  
  return *this;
}
void ctrl_gains_pkt::fill() {
  max_tilt = max_tilt_deg*utilities::constants::deg2rad;
  max_hdg_rate = max_hdg_rate_dps*utilities::constants::deg2rad;
  min_Ts = min_Ts_gs*utilities::constants::g0;
  max_Ts = max_Ts_gs*utilities::constants::g0;
  max_delta_Ts = max_delta_Ts_gs*utilities::constants::g0;
  max_omega_xy = max_omega_xy_dps*utilities::constants::deg2rad;
  max_omega_z = max_omega_z_dps*utilities::constants::deg2rad;
}
string ctrl_gains_pkt::src_label() const {
  static const char* src_labels[] = {
    "UNDEFINED",
    "CONTROL"
  };
  return string(src_labels[src()]);
}
string ctrl_gains_pkt::header() const {
  string str;
  
  str += "wn_ne"+DEFAULT_DELIM;
  str += "zeta_ne"+DEFAULT_DELIM;
  str += "wn_d"+DEFAULT_DELIM;
  str += "zeta_d"+DEFAULT_DELIM;
  str += "min_altitude"+DEFAULT_DELIM;
  str += "max_altitude"+DEFAULT_DELIM;
  str += "max_north_pos"+DEFAULT_DELIM;
  str += "max_south_pos"+DEFAULT_DELIM;
  str += "max_east_pos"+DEFAULT_DELIM;
  str += "max_west_pos"+DEFAULT_DELIM;
  str += "max_hvel"+DEFAULT_DELIM;
  str += "max_vvel"+DEFAULT_DELIM;
  
  str += "max_tilt_deg"+DEFAULT_DELIM;
  str += "max_load_factor"+DEFAULT_DELIM;
  str += "max_pwm_coll_rate"+DEFAULT_DELIM;
  str += "max_hdg_rate_dps"+DEFAULT_DELIM;
  str += "min_Ts_gs"+DEFAULT_DELIM;
  str += "max_Ts_gs"+DEFAULT_DELIM;
  str += "max_delta_Ts_gs"+DEFAULT_DELIM;
  str += "max_omega_xy_dps"+DEFAULT_DELIM;
  str += "max_omega_z_dps"+DEFAULT_DELIM;
  str += "min_coll_pwm"+DEFAULT_DELIM;
  str += "max_coll_pwm"+DEFAULT_DELIM;
  str += "max_att_pwm"+DEFAULT_DELIM;
  str += "max_test_pwm"+DEFAULT_DELIM;
  str += "zero_thrust_pwm"+DEFAULT_DELIM;
  str += "att_p_gain"+DEFAULT_DELIM;
  str += Ts_ne_pid.header()+DEFAULT_DELIM;
  str += Ts_z_pid.header()+DEFAULT_DELIM;
  str += omega_xy_pid.header()+DEFAULT_DELIM;
  str += omega_z_pid.header();
  
  return str;
}
uint32 ctrl_gains_pkt::derived_size() const {
  return sizeof(wn_ne)+
         sizeof(zeta_ne)+
         sizeof(wn_d)+
         sizeof(zeta_d)+
         sizeof(min_altitude)+
         sizeof(max_altitude)+
         sizeof(max_north_pos)+
         sizeof(max_south_pos)+
         sizeof(max_east_pos)+
         sizeof(max_west_pos)+
         sizeof(max_hvel)+
         sizeof(max_vvel)+
         sizeof(max_tilt_deg)+
         sizeof(max_load_factor)+
         sizeof(max_coll_pwm)+
         sizeof(max_hdg_rate_dps)+
         sizeof(min_Ts_gs)+
         sizeof(max_Ts_gs)+
         sizeof(max_delta_Ts_gs)+
         sizeof(max_omega_xy_dps)+
         sizeof(max_omega_z_dps)+
         sizeof(min_coll_pwm)+
         sizeof(max_coll_pwm)+
         sizeof(max_att_pwm)+
         sizeof(max_test_pwm)+
         sizeof(zero_thrust_pwm)+
         sizeof(att_p_gain)+
         Ts_ne_pid.size()+
         Ts_z_pid.size()+
         omega_xy_pid.size()+
         omega_z_pid.size();
}
uint8* ctrl_gains_pkt::derived_serialize(uint8* msg) const {
  msg = serialize_elem(msg,wn_ne);
  msg = serialize_elem(msg,zeta_ne);
  msg = serialize_elem(msg,wn_d);
  msg = serialize_elem(msg,zeta_d);
  msg = serialize_elem(msg,min_altitude);
  msg = serialize_elem(msg,max_altitude);
  msg = serialize_elem(msg,max_north_pos);
  msg = serialize_elem(msg,max_south_pos);
  msg = serialize_elem(msg,max_east_pos);
  msg = serialize_elem(msg,max_west_pos);
  msg = serialize_elem(msg,max_hvel);
  msg = serialize_elem(msg,max_vvel);
  msg = serialize_elem(msg,max_tilt_deg);
  msg = serialize_elem(msg,max_load_factor);
  msg = serialize_elem(msg,max_pwm_coll_rate);
  msg = serialize_elem(msg,max_hdg_rate_dps);
  msg = serialize_elem(msg,min_Ts_gs);
  msg = serialize_elem(msg,max_Ts_gs);
  msg = serialize_elem(msg,max_delta_Ts_gs);
  msg = serialize_elem(msg,max_omega_xy_dps);
  msg = serialize_elem(msg,max_omega_z_dps);
  msg = serialize_elem(msg,min_coll_pwm);
  msg = serialize_elem(msg,max_coll_pwm);
  msg = serialize_elem(msg,max_att_pwm);
  msg = serialize_elem(msg,max_test_pwm);
  msg = serialize_elem(msg,zero_thrust_pwm);
  msg = serialize_elem(msg,att_p_gain);
  msg = Ts_ne_pid.serialize(msg);
  msg = Ts_z_pid.serialize(msg);
  msg = omega_xy_pid.serialize(msg);
  msg = omega_z_pid.serialize(msg);
  return msg;
}
const uint8* ctrl_gains_pkt::derived_deserialize(const uint8* msg) {
  msg = deserialize_elem(msg,wn_ne);
  msg = deserialize_elem(msg,zeta_ne);
  msg = deserialize_elem(msg,wn_d);
  msg = deserialize_elem(msg,zeta_d);
  msg = deserialize_elem(msg,min_altitude);
  msg = deserialize_elem(msg,max_altitude);
  msg = deserialize_elem(msg,max_north_pos);
  msg = deserialize_elem(msg,max_south_pos);
  msg = deserialize_elem(msg,max_east_pos);
  msg = deserialize_elem(msg,max_west_pos);
  msg = deserialize_elem(msg,max_hvel);
  msg = deserialize_elem(msg,max_vvel);
  msg = deserialize_elem(msg,max_tilt_deg);
  msg = deserialize_elem(msg,max_load_factor);
  msg = deserialize_elem(msg,max_pwm_coll_rate);
  msg = deserialize_elem(msg,max_hdg_rate_dps);
  msg = deserialize_elem(msg,min_Ts_gs);
  msg = deserialize_elem(msg,max_Ts_gs);
  msg = deserialize_elem(msg,max_delta_Ts_gs);
  msg = deserialize_elem(msg,max_omega_xy_dps);
  msg = deserialize_elem(msg,max_omega_z_dps);
  msg = deserialize_elem(msg,min_coll_pwm);
  msg = deserialize_elem(msg,max_coll_pwm);
  msg = deserialize_elem(msg,max_att_pwm);
  msg = deserialize_elem(msg,max_test_pwm);
  msg = deserialize_elem(msg,zero_thrust_pwm);
  msg = deserialize_elem(msg,att_p_gain);
  msg = Ts_ne_pid.deserialize(msg);
  msg = Ts_z_pid.deserialize(msg);
  msg = omega_xy_pid.deserialize(msg);
  msg = omega_z_pid.deserialize(msg);
  return msg;
}
void ctrl_gains_pkt::derived_format(ostream& stream) const {
  stream << std::scientific
         << std::showpos
         << std::setprecision(DEFAULT_PRECISION)
         << std::setw(DEFAULT_WIDTH) << wn_ne << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << zeta_ne << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << wn_d << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << zeta_d << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << min_altitude << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_altitude << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_north_pos << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_south_pos << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_east_pos << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_west_pos << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_hvel << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_vvel << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_tilt_deg << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_load_factor << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_pwm_coll_rate << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_hdg_rate_dps << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << min_Ts_gs << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_Ts_gs << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_delta_Ts_gs << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_omega_xy_dps << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_omega_z_dps << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << min_coll_pwm << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_coll_pwm << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_att_pwm << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << max_test_pwm << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << zero_thrust_pwm << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << att_p_gain << DEFAULT_DELIM
         << Ts_ne_pid << DEFAULT_DELIM
         << Ts_z_pid << DEFAULT_DELIM
         << omega_xy_pid << DEFAULT_DELIM
         << omega_z_pid;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
