#include "WireUtil.h"
#include <Wire.h>
#include <TimeUtil.h>

int WireUtil::writeRegister(uint8_t dev_addr, uint8_t reg_addr, uint8_t data) {
  return WireUtil::writeRegister(dev_addr, reg_addr, &data, 1);
}

int WireUtil::writeRegister(uint8_t dev_addr, uint8_t reg_addr, const uint8_t* data, uint8_t n_bytes) {
  Wire.beginTransmission(dev_addr);
  Wire.write(reg_addr);
  for(int i=0; i<n_bytes; ++i) {
    Wire.write(data[i]);
  }
  Wire.endTransmission();
  return 0;
}

int WireUtil::readRegister(uint8_t dev_addr, uint8_t reg_addr, uint8_t& res, uint32_t retry_us, uint32_t retry_interval_us) {
  return readRegister(dev_addr, reg_addr, uint8_t(1), &res, retry_us, retry_interval_us);
} 

int WireUtil::readRegister(uint8_t dev_addr, uint8_t reg_addr, uint8_t n_bytes, uint32_t& res, bool lsb_first, uint32_t retry_us, uint32_t retry_interval_us) {
  if(n_bytes > 4) {
    return -1;
  }
  uint8_t buf[n_bytes];
  if(readRegister(dev_addr, reg_addr, n_bytes, buf, retry_us, retry_interval_us) != 0) {
    return -1;
  }
  res = 0;
  if(lsb_first) {
    for(int i=0; i<n_bytes; ++i) {
      res |= (uint32_t(buf[i]) << (i << 3));
    }
  } else {
    for(int i=0; i<n_bytes; ++i) {
      res <<= 8;
      res |= uint32_t(buf[i]);
    }
  }
  return 0;
}

int WireUtil::readRegister(uint8_t dev_addr, uint8_t reg_addr, uint8_t n_bytes, uint8_t* buf, uint32_t retry_us, uint32_t retry_interval_us) {
  Wire.beginTransmission(dev_addr);
  Wire.write(reg_addr);
  Wire.endTransmission();
  uint32_t start_time = micros();  
  while(Wire.requestFrom(dev_addr, uint8_t(n_bytes)) < n_bytes) {
    if(retry_us <= 0 || TimeUtil::deltaMicroseconds(start_time, micros() + retry_interval_us) >= retry_us) {
       return -1;
    }
    delayMicroseconds(retry_interval_us);
  }
  for(int i=0; i<n_bytes; ++i) {
    buf[i] = Wire.read();
  }
  return 0;
}
