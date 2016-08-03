////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/ahrs_data_pkt.cpp                                                           //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/ahrs_data_pkt.h"
using messages::ahrs_data_pkt;
using std::ostream;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

ahrs_data_pkt::ahrs_data_pkt(FORMAT_MODE format_mode) : packet(AHRS_DATA_PKT) {
  // Quaternion element self initializes to q = [1 0 0 0]'.
  b_gyro = v3x1::Zero();
  m_format_mode = format_mode;
}
void ahrs_data_pkt::set_format_mode(FORMAT_MODE format_mode) {
  m_format_mode = format_mode;
}
ahrs_data_pkt& ahrs_data_pkt::operator=(const ahrs_data_pkt& rhs) {
  packet::operator=(rhs);
  q_n2b = rhs.q_n2b;
  b_gyro = rhs.b_gyro;
  return *this;
}
void ahrs_data_pkt::set_src(SRC src) {
  packet::set_src(src);
}
string ahrs_data_pkt::src_label() const {
  static const char* src_labels[] = {
      "UNDEFINED",
      "AHRS"
  };
  return string(src_labels[src()]);
}
string ahrs_data_pkt::header() const {
  string str;
  switch (m_format_mode) {
    case RAW:
      str += "q_n2b_0"+DEFAULT_DELIM;
      str += "q_n2b_1"+DEFAULT_DELIM;
      str += "q_n2b_2"+DEFAULT_DELIM;
      str += "q_n2b_3"+DEFAULT_DELIM;
      str += "b_gx_dps"+DEFAULT_DELIM;
      str += "b_gy_dps"+DEFAULT_DELIM;
      str += "b_gz_dps";
      break;
    case EULER:
      str += "roll_deg"+DEFAULT_DELIM;
      str += "pitch_deg"+DEFAULT_DELIM;
      str += "yaw_deg"+DEFAULT_DELIM;
      str += "b_gx_dps"+DEFAULT_DELIM;
      str += "b_gy_dps"+DEFAULT_DELIM;
      str += "b_gz_dps";
      break;
  }
  return str;
}
uint32 ahrs_data_pkt::derived_size() const {
  return sizeof(q_n2b.w())+
         sizeof(q_n2b.x())+
         sizeof(q_n2b.y())+
         sizeof(q_n2b.z())+
         sizeof(b_gyro(0))+
         sizeof(b_gyro(1))+
         sizeof(b_gyro(2));
}
uint8* ahrs_data_pkt::derived_serialize(uint8* msg) const {
  msg = serialize_elem(msg,q_n2b.w());
  msg = serialize_elem(msg,q_n2b.x());
  msg = serialize_elem(msg,q_n2b.y());
  msg = serialize_elem(msg,q_n2b.z());
  msg = serialize_elem(msg,b_gyro(0));
  msg = serialize_elem(msg,b_gyro(1));
  msg = serialize_elem(msg,b_gyro(2));
  return msg;
}
const uint8* ahrs_data_pkt::derived_deserialize(const uint8* msg) {
  msg = deserialize_elem(msg,q_n2b.w());
  msg = deserialize_elem(msg,q_n2b.x());
  msg = deserialize_elem(msg,q_n2b.y());
  msg = deserialize_elem(msg,q_n2b.z());
  msg = deserialize_elem(msg,b_gyro(0));
  msg = deserialize_elem(msg,b_gyro(1));
  msg = deserialize_elem(msg,b_gyro(2));
  return msg;
}
void ahrs_data_pkt::derived_format(ostream& stream) const {
  const float&  rad2deg = utilities::constants::rad2deg;
  switch (m_format_mode) {
    case RAW:
      stream << std::scientific
             << std::showpos
             << std::setprecision(DEFAULT_PRECISION)
             << std::setw(DEFAULT_WIDTH) << q_n2b.w() << DEFAULT_DELIM
             << std::setw(DEFAULT_WIDTH) << q_n2b.x() << DEFAULT_DELIM
             << std::setw(DEFAULT_WIDTH) << q_n2b.y() << DEFAULT_DELIM
             << std::setw(DEFAULT_WIDTH) << q_n2b.z() << DEFAULT_DELIM
             << std::setw(DEFAULT_WIDTH) << b_gyro(0)*rad2deg << DEFAULT_DELIM
             << std::setw(DEFAULT_WIDTH) << b_gyro(1)*rad2deg << DEFAULT_DELIM
             << std::setw(DEFAULT_WIDTH) << b_gyro(2)*rad2deg;
      break;
    case EULER:
      stream << std::scientific
             << std::showpos
             << std::setprecision(DEFAULT_PRECISION)
             << std::setw(DEFAULT_WIDTH) << q_n2b.roll_deg() << DEFAULT_DELIM
             << std::setw(DEFAULT_WIDTH) << q_n2b.pitch_deg() << DEFAULT_DELIM
             << std::setw(DEFAULT_WIDTH) << q_n2b.yaw_deg() << DEFAULT_DELIM
             << std::setw(DEFAULT_WIDTH) << b_gyro(0)*rad2deg << DEFAULT_DELIM
             << std::setw(DEFAULT_WIDTH) << b_gyro(1)*rad2deg << DEFAULT_DELIM
             << std::setw(DEFAULT_WIDTH) << b_gyro(2)*rad2deg;
      break;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
