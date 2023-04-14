
/**********************************************************
 * WireUtil.h                                             *
 *                                                        *
 * Author: Manuel Schoch <info@manuel-schoch.net>         *                                                       *
 *                                                        *
 **********************************************************/

#ifndef WIREUTIL_H
#define WIREUTIL_H

#include <Arduino.h>

class WireUtil {
public:
  /**
   * Write an I2C register.
   * @param dev_addr The I2C slave address
   * @param reg_addr The address of the register to read
   * @param data The data write
   * @return 0 on success, < 0 otherwise
   */
  static int writeRegister(uint8_t dev_addr, uint8_t reg_addr, uint8_t data);
  
  /**
   * Write multiple succeeding I2C registers in burst mode.
   * @param dev_addr The I2C slave address
   * @param reg_addr The address of the register to read
   * @param data The data write
   * @param n_bytes The number of bytes to write
   * @return 0 on success, < 0 otherwise
   */
  static int writeRegister(uint8_t dev_addr, uint8_t reg_addr, const uint8_t* data, uint8_t n_bytes);
  
  /**
   * Read an I2C register. For the case that a register can't be read (i. e. the slave responds with an NACK), the function
   * supports auto-repeat by specifying for how long it should try to read the data. Additionally a the re-try interval can be specified.
   * @param dev_addr The I2C slave address
   * @param reg_addr The address of the register to read
   * @param res The data read
   * @param retry_us The duration in microseconds how long to re-try, in case the slave sends a NACK (default: 0 -> don't re-try)
   * @param retry_interval_us The interval how frequent to re-try reading the data (default: 800us)
   * @return 0 on success, < 0 otherwise
   */
  static int readRegister(uint8_t dev_addr, uint8_t reg_addr, uint8_t& res, uint32_t retry_us=0, uint32_t retry_interval_us=1000);
  
  /**
   * Read multiple succeeding I2C registers in burst mode.
   * @param dev_addr The I2C slave address
   * @param reg_addr The address of the register to read
   * @param n_bytes The number of bytes to read (max 4)
   * @param res The data read
   * @param lsb_first Specifies if the least significant byte is returned first (default: false -> msb first)
   * @param retry_us The duration in microseconds how long to re-try, in case the slave sends a NACK (default: 0 -> don't re-try)
   * @param retry_interval_us The interval how frequent to re-try reading the data (default: 800us)
   * @return 0 on success, < 0 otherwise
   */
  static int readRegister(uint8_t dev_addr, uint8_t reg_addr, uint8_t n_bytes, uint32_t& res, bool lsb_first=false, uint32_t retry_us=0, uint32_t retry_interval_us=1000);
  
  /**
   * Read multiple succeeding I2C registers in burst mode.
   * @param dev_addr The I2C slave address
   * @param reg_addr The address of the register to read
   * @param n_bytes The number of bytes to read
   * @param buf The data read
   * @param retry_us The duration in microseconds how long to re-try, in case the slave sends a NACK (default: 0 -> don't re-try)
   * @param retry_interval_us The interval how frequent to re-try reading the data (default: 800us)
   * @return 0 on success, < 0 otherwise
   */
  static int readRegister(uint8_t dev_addr, uint8_t reg_addr, uint8_t n_bytes, uint8_t* buf, uint32_t retry_us=0, uint32_t retry_interval_us=1000);
};

#endif // WIREUTIL
