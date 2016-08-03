////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/pwm_pkt.cpp                                                                 //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/pwm_pkt.h"
using messages::pwm_pkt;
using std::ostream;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

pwm_pkt::pwm_pkt(SRC src) : packet(PWM_PKT) {
  ch1 = 0.0f;
  ch2 = 0.0f;
  ch3 = 0.0f;
  ch4 = 0.0f;
  ch5 = 0.0f;
  ch6 = 0.0f;
  
  packet::set_src(src);
}
string pwm_pkt::src_label() const {
  static const char* src_labels[] = {
    "UNDEFINED",
    "CONTROL"
  };
  return string(src_labels[src()]);
}
string pwm_pkt::header() const {
  string str;
  str += "ch1"+DEFAULT_DELIM;
  str += "ch2"+DEFAULT_DELIM;
  str += "ch3"+DEFAULT_DELIM;
  str += "ch4"+DEFAULT_DELIM;
  str += "ch5"+DEFAULT_DELIM;
  str += "ch6";
  return str;
}
uint32 pwm_pkt::derived_size() const {
  return sizeof(ch1)+
         sizeof(ch2)+
         sizeof(ch3)+
         sizeof(ch4)+
         sizeof(ch5)+
         sizeof(ch6);
}
uint8* pwm_pkt::derived_serialize(uint8* msg) const {
  msg = serialize_elem(msg,ch1);
  msg = serialize_elem(msg,ch2);
  msg = serialize_elem(msg,ch3);
  msg = serialize_elem(msg,ch4);
  msg = serialize_elem(msg,ch5);
  msg = serialize_elem(msg,ch6);
  return msg;
}
const uint8* pwm_pkt::derived_deserialize(const uint8* msg) {
  msg = deserialize_elem(msg,ch1);
  msg = deserialize_elem(msg,ch2);
  msg = deserialize_elem(msg,ch3);
  msg = deserialize_elem(msg,ch4);
  msg = deserialize_elem(msg,ch5);
  msg = deserialize_elem(msg,ch6);
  return msg;
}
void pwm_pkt::derived_format(ostream& stream) const {
  stream << std::fixed
         << std::noshowpos
         << std::setprecision(0)
         << std::setw(4) << ch1 << DEFAULT_DELIM
         << std::setw(4) << ch2 << DEFAULT_DELIM
         << std::setw(4) << ch3 << DEFAULT_DELIM
         << std::setw(4) << ch4 << DEFAULT_DELIM
         << std::setw(4) << ch5 << DEFAULT_DELIM
         << std::setw(4) << ch6;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
