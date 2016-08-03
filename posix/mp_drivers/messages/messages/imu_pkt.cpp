////////////////////////////////////////////////////////////////////////////////////////////////////
// TITLE:    messages/imu_pkt.cpp                                                                 //
// DATE:     Thu Jan 21 15:00:44 2016                                                             //
// AUTHORS:  Michael (Miki) Szmuk, Tim Lowery                                                     //
// PI:       Dr. Behcet Acikmese                                                                  //
// LAB:      Autonomous GN&C Lab                                                                  //
// LICENSE:  Copyright 2015, Copyright 2016                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "messages/imu_pkt.h"
using messages::imu_pkt;
using std::ostream;
using std::string;

////////////////////////////////////////////////////////////////////////////////////////////////////

imu_pkt::imu_pkt(SRC src) : packet(IMU_PKT) {
  accl = v3x1::Zero();
  gyro = v3x1::Zero();
  
  packet::set_src(src);
}
string imu_pkt::src_label() const {
  static const char* src_labels[] = {
    "UNDEFINED",
    "IMU",
    "AHRS" 
  };
  return string(src_labels[src()]);
}
string imu_pkt::header() const {
  string str;
  str += "accl_x"+DEFAULT_DELIM;
  str += "accl_y"+DEFAULT_DELIM;
  str += "accl_z"+DEFAULT_DELIM;
  str += "gyro_x"+DEFAULT_DELIM;
  str += "gyro_y"+DEFAULT_DELIM;
  str += "gyro_z";
  return str;
}
uint32 imu_pkt::derived_size() const {
  return sizeof(accl(0))
        +sizeof(accl(1))
        +sizeof(accl(2))
        +sizeof(gyro(0))
        +sizeof(gyro(1))
        +sizeof(gyro(2));
}
uint8* imu_pkt::derived_serialize(uint8* msg) const {
  msg = serialize_elem(msg,accl(0));
  msg = serialize_elem(msg,accl(1));
  msg = serialize_elem(msg,accl(2));
  msg = serialize_elem(msg,gyro(0));
  msg = serialize_elem(msg,gyro(1));
  msg = serialize_elem(msg,gyro(2));
  return msg;
}
const uint8* imu_pkt::derived_deserialize(const uint8* msg) {
  msg = deserialize_elem(msg,accl(0));
  msg = deserialize_elem(msg,accl(1));
  msg = deserialize_elem(msg,accl(2));
  msg = deserialize_elem(msg,gyro(0));
  msg = deserialize_elem(msg,gyro(1));
  msg = deserialize_elem(msg,gyro(2));
  return msg;
}
void imu_pkt::derived_format(ostream& stream) const {
  stream << std::scientific
         << std::showpos
         << std::setprecision(DEFAULT_PRECISION)
         << std::setw(DEFAULT_WIDTH) << accl(0) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << accl(1) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << accl(2) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << gyro(0) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << gyro(1) << DEFAULT_DELIM
         << std::setw(DEFAULT_WIDTH) << gyro(2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
