////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/dyn_cmd_pkt.cpp                                                             //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/dyn_cmd_pkt.h"
using messages::dyn_cmd_pkt;
using std::ostream;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

dyn_cmd_pkt::dyn_cmd_pkt(SRC src) : packet(DYN_CMD_PKT) {
  mode = ctrl_mode_pkt(ctrl_mode_pkt::STANDBY_MODE);
  ch1 = 0.0f;
  ch2 = 0.0f;
  ch3 = 0.0f;
  ch4 = 0.0f;
  
  packet::set_src(src);
}
dyn_cmd_pkt::dyn_cmd_pkt(const dyn_cmd_pkt& data, SRC src) : packet(DYN_CMD_PKT) {
  this->operator=(data);
  packet::set_src(src);
}
void dyn_cmd_pkt::bound() {
  ch1 = utilities::bound(-1.0f,ch1,1.0f);
  ch2 = utilities::bound(-1.0f,ch2,1.0f);
  ch3 = utilities::bound(-1.0f,ch3,1.0f);
  ch4 = utilities::bound(-1.0f,ch4,1.0f);
}
string dyn_cmd_pkt::src_label() const {
  static const char* src_labels[] = {
    "UNDEFINED",
    "GCS",
    "API"
  };
  return string(src_labels[src()]);
}
string dyn_cmd_pkt::header() const {
  string str;
  str += mode.header()+DEFAULT_DELIM;
  str += "ch1"+DEFAULT_DELIM;
  str += "ch2"+DEFAULT_DELIM;
  str += "ch3"+DEFAULT_DELIM;
  str += "ch4";
  return str;
}
uint32 dyn_cmd_pkt::derived_size() const {
  return mode.size()+
         sizeof(ch1)+
         sizeof(ch2)+
         sizeof(ch3)+
         sizeof(ch4);
}
uint8* dyn_cmd_pkt::derived_serialize(uint8* msg) const {
  msg = mode.serialize(msg);
  msg = serialize_elem(msg,ch1);
  msg = serialize_elem(msg,ch2);
  msg = serialize_elem(msg,ch3);
  msg = serialize_elem(msg,ch4);
  return msg;
}
const uint8* dyn_cmd_pkt::derived_deserialize(const uint8* msg) {
  msg = mode.deserialize(msg);
  msg = deserialize_elem(msg,ch1);
  msg = deserialize_elem(msg,ch2);
  msg = deserialize_elem(msg,ch3);
  msg = deserialize_elem(msg,ch4);
  return msg;
}
void dyn_cmd_pkt::derived_format(ostream& stream) const {
  stream << mode << DEFAULT_DELIM
         << std::scientific
         << std::showpos
         << std::setprecision(DEFAULT_PRECISION)
         << std::setw(DEFAULT_WIDTH) << ch1 << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << ch2 << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << ch3 << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << ch4;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
