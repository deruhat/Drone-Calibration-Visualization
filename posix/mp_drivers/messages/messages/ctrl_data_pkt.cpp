////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/ctrl_data_pkt.cpp                                                           //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/ctrl_data_pkt.h"
using messages::ctrl_data_pkt;
using std::ostream;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

ctrl_data_pkt::ctrl_data_pkt(SRC src) : packet(CTRL_DATA_PKT) {
  packet::set_src(src);
}
string ctrl_data_pkt::src_label() const {
  static const char* src_labels[] = {
      "UNDEFINED",
      "CONTROL"
  };
  return string(src_labels[src()]);
}
string ctrl_data_pkt::header() const {
  string str;
  str += accl_z.header()+DEFAULT_DELIM;
  str += omega_x.header()+DEFAULT_DELIM;
  str += omega_y.header()+DEFAULT_DELIM;
  str += omega_z.header();
  return str;
}
uint32 ctrl_data_pkt::derived_size() const {
  return accl_z.size()+
         omega_x.size()+
         omega_y.size()+
         omega_z.size();
}
uint8* ctrl_data_pkt::derived_serialize(uint8* msg) const {
  msg = accl_z.serialize(msg);
  msg = omega_x.serialize(msg);
  msg = omega_y.serialize(msg);
  msg = omega_z.serialize(msg);
  return msg;
}
const uint8* ctrl_data_pkt::derived_deserialize(const uint8* msg) {
  msg = accl_z.deserialize(msg);
  msg = omega_x.deserialize(msg);
  msg = omega_y.deserialize(msg);
  msg = omega_z.deserialize(msg);
  return msg;
}
void ctrl_data_pkt::derived_format(ostream& stream) const {
  stream << accl_z << DEFAULT_DELIM
         << omega_x << DEFAULT_DELIM
         << omega_y << DEFAULT_DELIM
         << omega_z;
}
void ctrl_data_pkt::timestamp() {
    packet::timestamp();
    accl_z.timestamp(ts());
    omega_x.timestamp(ts());
    omega_y.timestamp(ts());
    omega_z.timestamp(ts());
}
void ctrl_data_pkt::timestamp(float ts) {
  packet::timestamp(ts);
  accl_z.timestamp(ts);
  omega_x.timestamp(ts);
  omega_y.timestamp(ts);
  omega_z.timestamp(ts);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
