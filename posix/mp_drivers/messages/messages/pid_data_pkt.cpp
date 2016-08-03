////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/pid_data_pkt.cpp                                                            //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/pid_data_pkt.h"
using messages::pid_data_pkt;
using std::ostream;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

pid_data_pkt::pid_data_pkt(SRC src) : packet(PID_DATA_PKT) {
  reset = 0.0f;
  u_p = 0.0f;
  u_i = 0.0f;
  u_d = 0.0f;
  u = 0.0f;
  e = 0.0f;
  
  packet::set_src(src);
}
string pid_data_pkt::src_label() const {
  static const char* src_labels[] = {
    "UNDEFINED",
    "TS_N_PID",
    "TS_E_PID",
    "TS_Z_PID",
    "OMEGA_X_PID",
    "OMEGA_Y_PID",
    "OMEGA_Z_PID"
  };
  return string(src_labels[src()]);
}
string pid_data_pkt::header() const {
  string str;
  str += "reset"+DEFAULT_DELIM;
  str += "u_p"+DEFAULT_DELIM;
  str += "u_i"+DEFAULT_DELIM;
  str += "u_d"+DEFAULT_DELIM;
  str += "u"+DEFAULT_DELIM;
  str += "e";
  return str;
}
uint32 pid_data_pkt::derived_size() const {
  return sizeof(reset)+
         sizeof(u_p)+
         sizeof(u_i)+
         sizeof(u_d)+
         sizeof(u)+
         sizeof(e);
}
uint8* pid_data_pkt::derived_serialize(uint8* msg) const {
  msg = serialize_elem(msg,reset);
  msg = serialize_elem(msg,u_p);
  msg = serialize_elem(msg,u_i);
  msg = serialize_elem(msg,u_d);
  msg = serialize_elem(msg,u);
  msg = serialize_elem(msg,e);
  return msg;
}
const uint8* pid_data_pkt::derived_deserialize(const uint8* msg) {
  msg = deserialize_elem(msg,reset);
  msg = deserialize_elem(msg,u_p);
  msg = deserialize_elem(msg,u_i);
  msg = deserialize_elem(msg,u_d);
  msg = deserialize_elem(msg,u);
  msg = deserialize_elem(msg,e);
  return msg;
}
void pid_data_pkt::derived_format(ostream& stream) const {
  stream << std::scientific
         << std::showpos
         << std::setprecision(DEFAULT_PRECISION)
         << std::setw(DEFAULT_WIDTH) << reset << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << u_p << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << u_i << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << u_d << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << u << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << e;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
