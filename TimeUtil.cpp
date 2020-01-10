
#include "TimeUtil.h"

int32_t TimeUtil::deltaMicroseconds(uint32_t time_stamp, uint32_t delta_time_stamp) {
  // This is the same math as wit milliseconds, just with a different unit
  return delta(time_stamp, delta_time_stamp);
}
    
int32_t TimeUtil::delta(uint32_t time_stamp, uint32_t delta_time_stamp) {
  // normally: delta = delta_time_stamp - time_stamp
  if(delta_time_stamp > time_stamp && (delta_time_stamp - time_stamp) > 0x7FFFFFFFu) {
    // overflow
    // since the time stamps differ by more than ((2^32-1)/2), delta_time_stamp must be bigger than
    // ((2^32-1)/2) and time_stamp smaller, that means our int32_t conversions are safe
    return -int32_t(time_stamp) - int32_t(0xFFFFFFFFu - delta_time_stamp);
  } else if(delta_time_stamp < time_stamp && (time_stamp - delta_time_stamp) > 0x7FFFFFFFu) {
    // overflow
    return int32_t(0xFFFFFFFFu - time_stamp) + delta_time_stamp;
  } else {
    // delta_time_stamp - time_stamp differ by <= 0x7FFFFFFF which can be represented at signed int32
    return int32_t(delta_time_stamp - time_stamp);
  }
}
