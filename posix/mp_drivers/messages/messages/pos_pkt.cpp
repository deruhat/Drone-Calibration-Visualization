////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/pos_pkt.cpp                                                                 //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/pos_pkt.h"
using messages::pos_pkt;
using std::ostream;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

pos_pkt::pos_pkt(SRC src) : packet(POS_PKT) {
  pos_ned = v3x1::Zero();
  
  packet::set_src(src);
}
string pos_pkt::src_label() const {
  static const char* src_labels[] = {
    "UNDEFINED",
    "VICON"
  };
  return string(src_labels[src()]);
}
string pos_pkt::header() const {
  string str;
  str += "pos_ned_n"+DEFAULT_DELIM;
  str += "pos_ned_e"+DEFAULT_DELIM;
  str += "pos_ned_d";
  return str;
}
uint32 pos_pkt::derived_size() const {
  return sizeof(pos_ned(0))+
         sizeof(pos_ned(1))+
         sizeof(pos_ned(2));
}
uint8* pos_pkt::derived_serialize(uint8* msg) const {
  msg = serialize_elem(msg,pos_ned(0));
  msg = serialize_elem(msg,pos_ned(1));
  msg = serialize_elem(msg,pos_ned(2));
  return msg;
}
const uint8* pos_pkt::derived_deserialize(const uint8* msg) {
  msg = deserialize_elem(msg,pos_ned(0));
  msg = deserialize_elem(msg,pos_ned(1));
  msg = deserialize_elem(msg,pos_ned(2));
  return msg;
}
void pos_pkt::derived_format(ostream& stream) const {
  stream << std::scientific
         << std::showpos
         << std::setprecision(DEFAULT_PRECISION)
         << std::setw(DEFAULT_WIDTH) << pos_ned(0) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << pos_ned(1) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << pos_ned(2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
