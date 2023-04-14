
/**********************************************************
 * TimeUtil.h                                             *
 *                                                        *
 * Author: Manuel Schoch <info@manuel-schoch.net>         *
 *                                                        *
 **********************************************************/

#ifndef TIMEUTIL_H
#define TIMEUTIL_H

#include <Arduino.h>

class TimeUtil {
public:
  /**
   * Calculates the delta between the 2 time stamps in microseconds. If delta_time_stamp is before
   * time_stamp the result will be negative. The function tries to detect and consider overflows.
   * If delta_time_stamp is more than (2^32-1)/2 (2147.48s) larger time_stamp, an overflow is assumed.
   * @return The delta in microseconds.
   */
  static int32_t deltaMicroseconds(uint32_t time_stamp, uint32_t delta_time_stamp);
  
  /**
   * Calculates the delta between the 2 time stamps in milliseconds. If delta_time_stamp is before
   * time_stamp the result will be negative. The function tries to detect and consider overflows.
   * If delta_time_stamp is more than (2^32-1)/2 (596.52h) larger time_stamp, an overflow is assumed.
   * @return The delta in milliseconds.
   */
  static int32_t delta(uint32_t time_stamp, uint32_t delta_time_stamp);
};

#endif // WIREUTIL
 
