////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/quat_pkt.cpp                                                                //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/quat_pkt.h"
using messages::quat_pkt;
using std::ostream;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

quat_pkt::quat_pkt(SRC src) : packet(QUAT_PKT) {
  // Quaternion element self initializes to q = [1 0 0 0]'.
  m_format_mode = EULER;
  
  packet::set_src(src);
}
void quat_pkt::set_format_mode(FORMAT_MODE format_mode) {
  m_format_mode = format_mode;
}
quat_pkt& quat_pkt::operator=(const quat_pkt& rhs) {
  packet::operator=(rhs);
  q = rhs.q;
  return *this;
}
string quat_pkt::src_label() const {
  static const char* src_labels[] = {
    "UNDEFINED",
    "AHRS"
  };
  return string(src_labels[src()]);
}
string quat_pkt::header() const {
  string str;
  switch (m_format_mode) {
    case RAW:
      str += "q0"+DEFAULT_DELIM;
      str += "q1"+DEFAULT_DELIM;
      str += "q2"+DEFAULT_DELIM;
      str += "q3";
      break;
    case EULER:
      str += "roll_deg"+DEFAULT_DELIM;
      str += "pitch_deg"+DEFAULT_DELIM;
      str += "yaw_deg";
      break;
  }
  return str;
}
uint32 quat_pkt::derived_size() const {
  return sizeof(q.w())+
         sizeof(q.x())+
         sizeof(q.y())+
         sizeof(q.z());
}
uint8* quat_pkt::derived_serialize(uint8* msg) const {
  msg = serialize_elem(msg,q.w());
  msg = serialize_elem(msg,q.x());
  msg = serialize_elem(msg,q.y());
  msg = serialize_elem(msg,q.z());
  return msg;
}
const uint8* quat_pkt::derived_deserialize(const uint8* msg) {
  msg = deserialize_elem(msg,q.w());
  msg = deserialize_elem(msg,q.x());
  msg = deserialize_elem(msg,q.y());
  msg = deserialize_elem(msg,q.z());
  return msg;
}
void quat_pkt::derived_format(ostream& stream) const {
  switch (m_format_mode) {
    case RAW:
      stream << std::scientific
             << std::showpos
             << std::setprecision(DEFAULT_PRECISION)
             << std::setw(DEFAULT_WIDTH) << q.w() << DEFAULT_DELIM
             << std::setw(DEFAULT_WIDTH) << q.x() << DEFAULT_DELIM
             << std::setw(DEFAULT_WIDTH) << q.y() << DEFAULT_DELIM
             << std::setw(DEFAULT_WIDTH) << q.z();
      break;
    case EULER:
      stream << std::scientific
             << std::showpos
             << std::setprecision(DEFAULT_PRECISION)
             << std::setw(DEFAULT_WIDTH) << q.roll_deg() << DEFAULT_DELIM
             << std::setw(DEFAULT_WIDTH) << q.pitch_deg() << DEFAULT_DELIM
             << std::setw(DEFAULT_WIDTH) << q.yaw_deg();
      break;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
