////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/pid_gains_pkt.cpp                                                           //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/pid_gains_pkt.h"
using messages::pid_gains_pkt;
using std::ostream;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

pid_gains_pkt::pid_gains_pkt() : packet(PID_GAINS_PKT) {
  k_p = 0.0f;
  k_i = 0.0f;
  k_d = 0.0f;
  int_min = 0.0f;
  int_max = 0.0f;
}
void pid_gains_pkt::set_src(SRC src) {
  packet::set_src(src);
}
string pid_gains_pkt::src_label() const {
  static const char* src_labels[] = {
    "UNDEFINED"
  };
  return string(src_labels[src()]);
}
string pid_gains_pkt::header() const {
  string str;
  str += "k_p"+DEFAULT_DELIM;
  str += "k_i"+DEFAULT_DELIM;
  str += "k_d"+DEFAULT_DELIM;
  str += "int_min"+DEFAULT_DELIM;
  str += "int_max";
  return str;
}
uint32 pid_gains_pkt::derived_size() const {
  return sizeof(k_p)+
         sizeof(k_i)+
         sizeof(k_d)+
         sizeof(int_min)+
         sizeof(int_max);
}
uint8* pid_gains_pkt::derived_serialize(uint8* msg) const {
  msg = serialize_elem(msg,k_p);
  msg = serialize_elem(msg,k_i);
  msg = serialize_elem(msg,k_d);
  msg = serialize_elem(msg,int_min);
  msg = serialize_elem(msg,int_max);
  return msg;
}
const uint8* pid_gains_pkt::derived_deserialize(const uint8* msg) {
  msg = deserialize_elem(msg,k_p);
  msg = deserialize_elem(msg,k_i);
  msg = deserialize_elem(msg,k_d);
  msg = deserialize_elem(msg,int_min);
  msg = deserialize_elem(msg,int_max);
  return msg;
}
void pid_gains_pkt::derived_format(ostream& stream) const {
  stream << std::scientific
         << std::showpos
         << std::setprecision(DEFAULT_PRECISION)
         << std::setw(DEFAULT_WIDTH) << k_p << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << k_i << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << k_d << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << int_min << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << int_max;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
