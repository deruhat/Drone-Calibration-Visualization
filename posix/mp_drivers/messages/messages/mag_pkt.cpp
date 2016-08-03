////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/mag_pkt.cpp                                                                 //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/mag_pkt.h"
using messages::mag_pkt;
using std::ostream;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

mag_pkt::mag_pkt(SRC src) : packet(MAG_PKT) {
  mag = v3x1::Zero();
  
  packet::set_src(src);
}
string mag_pkt::src_label() const {
  static const char* src_labels[] = {
    "UNDEFINED",
    "VICON"
  };
  return string(src_labels[src()]);
}
string mag_pkt::header() const {
  string str;
  str += "mag_x"+DEFAULT_DELIM;
  str += "mag_y"+DEFAULT_DELIM;
  str += "mag_z";
  return str;
}
uint32 mag_pkt::derived_size() const {
  return sizeof(mag(0))
        +sizeof(mag(1))
        +sizeof(mag(2));
}
uint8* mag_pkt::derived_serialize(uint8* msg) const {
  msg = serialize_elem(msg,mag(0));
  msg = serialize_elem(msg,mag(1));
  msg = serialize_elem(msg,mag(2));
  return msg;
}
const uint8* mag_pkt::derived_deserialize(const uint8* msg) {
  msg = deserialize_elem(msg,mag(0));
  msg = deserialize_elem(msg,mag(1));
  msg = deserialize_elem(msg,mag(2));
  return msg;
}
void mag_pkt::derived_format(ostream& stream) const {
  stream << std::scientific
         << std::showpos
         << std::setprecision(DEFAULT_PRECISION)
         << std::setw(DEFAULT_WIDTH) << mag(0) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << mag(1) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << mag(2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
