////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/sim_gains_pkt.cpp                                                           //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/sim_gains_pkt.h"
using messages::sim_gains_pkt;
using std::ostream;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

sim_gains_pkt::sim_gains_pkt(SRC src) : packet(SIM_GAINS_PKT) {
  r_i_ned = v3x1::Zero();
  v_i_ned = v3x1::Zero();
  roll_i = 0.0f;
  pitch_i = 0.0f;
  yaw_i = 0.0f;
  omega_i = v3x1::Zero();
  m = 0.0f;
  L = 0.0f;
  cT = 0.0f;
  cM2cT = 0.0f;
  S = 0.0f;
  cD = 0.0f;
  cM = 0.0f;
  rho = 0.0f;
  tau_up = 0.0f;
  tau_down = 0.0f;
  J = m3x3::Zero();
  
  packet::set_src(src);
}
sim_gains_pkt& sim_gains_pkt::operator=(const sim_gains_pkt& rhs) {
  packet::operator=(rhs);
  
  r_i_ned = rhs.r_i_ned;
  v_i_ned = rhs.v_i_ned;
  roll_i = rhs.roll_i;
  pitch_i = rhs.pitch_i;
  yaw_i = rhs.yaw_i;
  omega_i = rhs.omega_i;
  m = rhs.m;
  L = rhs.L;
  cT = rhs.cT;
  cM2cT = rhs.cM2cT;
  S = rhs.S;
  cD = rhs.cD;
  cM = rhs.cM;
  rho = rhs.rho;
  tau_up = rhs.tau_up;
  tau_down = rhs.tau_down;
  J = rhs.J;
  
  return *this;
}
void sim_gains_pkt::fill() {
  /*DEBUG*/
}
string sim_gains_pkt::src_label() const {
  static const char* src_labels[] = {
    "UNDEFINED",
    "SIM"
  };
  return string(src_labels[src()]);
}
string sim_gains_pkt::header() const {
  string str;
  
  str += "r_i_ned_x"+DEFAULT_DELIM;
  str += "r_i_ned_y"+DEFAULT_DELIM;
  str += "r_i_ned_z"+DEFAULT_DELIM;
  str += "v_i_ned_x"+DEFAULT_DELIM;
  str += "v_i_ned_y"+DEFAULT_DELIM;
  str += "v_i_ned_z"+DEFAULT_DELIM;
  str += "roll_i"+DEFAULT_DELIM;
  str += "pitch_i"+DEFAULT_DELIM;
  str += "yaw_i"+DEFAULT_DELIM;
  str += "omega_i_x"+DEFAULT_DELIM;
  str += "omega_i_y"+DEFAULT_DELIM;
  str += "omega_i_z"+DEFAULT_DELIM;
  str += "m"+DEFAULT_DELIM;
  str += "L"+DEFAULT_DELIM;
  str += "cM2cT"+DEFAULT_DELIM;
  str += "S"+DEFAULT_DELIM;
  str += "cD"+DEFAULT_DELIM;
  str += "cM"+DEFAULT_DELIM;
  str += "rho"+DEFAULT_DELIM;
  str += "tau_up"+DEFAULT_DELIM;
  str += "tau_down"+DEFAULT_DELIM;
  str += "J";
  
  return str;
}
uint32 sim_gains_pkt::derived_size() const {
  return sizeof(r_i_ned(0))+
         sizeof(r_i_ned(1))+
         sizeof(r_i_ned(2))+
         sizeof(v_i_ned(0))+
         sizeof(v_i_ned(1))+
         sizeof(v_i_ned(2))+
         sizeof(roll_i)+
         sizeof(pitch_i)+
         sizeof(yaw_i)+
         sizeof(omega_i(0))+
         sizeof(omega_i(1))+
         sizeof(omega_i(2))+
         sizeof(m)+
         sizeof(L)+
         sizeof(cT)+
         sizeof(cM2cT)+
         sizeof(S)+
         sizeof(cD)+
         sizeof(cM)+
         sizeof(rho)+
         sizeof(tau_up)+
         sizeof(tau_down)+
         sizeof(J(0,0))+
         sizeof(J(0,1))+
         sizeof(J(0,2))+
         sizeof(J(1,0))+
         sizeof(J(1,1))+
         sizeof(J(1,2))+
         sizeof(J(2,0))+
         sizeof(J(2,1))+
         sizeof(J(2,2));
}
uint8* sim_gains_pkt::derived_serialize(uint8* msg) const {
  msg = serialize_elem(msg,m);
  msg = serialize_elem(msg,L);
  msg = serialize_elem(msg,cT);
  msg = serialize_elem(msg,cM2cT);
  msg = serialize_elem(msg,S);
  msg = serialize_elem(msg,cD);
  msg = serialize_elem(msg,cM);
  msg = serialize_elem(msg,rho);
  msg = serialize_elem(msg,tau_up);
  msg = serialize_elem(msg,tau_down);
  msg = serialize_elem(msg,J(0,0));
  msg = serialize_elem(msg,J(0,1));
  msg = serialize_elem(msg,J(0,2));
  msg = serialize_elem(msg,J(1,0));
  msg = serialize_elem(msg,J(1,1));
  msg = serialize_elem(msg,J(1,2));
  msg = serialize_elem(msg,J(2,0));
  msg = serialize_elem(msg,J(2,1));
  msg = serialize_elem(msg,J(2,2));
  return msg;
}
const uint8* sim_gains_pkt::derived_deserialize(const uint8* msg) {
  msg = deserialize_elem(msg,m);
  msg = deserialize_elem(msg,L);
  msg = deserialize_elem(msg,cT);
  msg = deserialize_elem(msg,cM2cT);
  msg = deserialize_elem(msg,S);
  msg = deserialize_elem(msg,cD);
  msg = deserialize_elem(msg,cM);
  msg = deserialize_elem(msg,rho);
  msg = deserialize_elem(msg,tau_up);
  msg = deserialize_elem(msg,tau_down);
  msg = deserialize_elem(msg,J(0,0));
  msg = deserialize_elem(msg,J(0,1));
  msg = deserialize_elem(msg,J(0,2));
  msg = deserialize_elem(msg,J(1,0));
  msg = deserialize_elem(msg,J(1,1));
  msg = deserialize_elem(msg,J(1,2));
  msg = deserialize_elem(msg,J(2,0));
  msg = deserialize_elem(msg,J(2,1));
  msg = deserialize_elem(msg,J(2,2));
  return msg;
}
void sim_gains_pkt::derived_format(ostream& stream) const {
  stream << std::scientific
         << std::showpos
         << std::setprecision(DEFAULT_PRECISION)
         << std::setw(DEFAULT_WIDTH) << r_i_ned(0) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << r_i_ned(1) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << r_i_ned(2) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << v_i_ned(0) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << v_i_ned(1) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << v_i_ned(2) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << roll_i << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << pitch_i << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << yaw_i << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << omega_i(0) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << omega_i(1) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << omega_i(2) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << m << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << L << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << cT << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << cM2cT << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << S << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << cD << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << cM << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << rho << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << tau_up << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << tau_down << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << J(0,0) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << J(0,1) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << J(0,2) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << J(1,0) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << J(1,1) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << J(1,2) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << J(2,0) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << J(2,1) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << J(2,2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
