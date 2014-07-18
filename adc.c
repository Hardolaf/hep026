#include "defines.h"

#include "lib/I2C-master-lib/I2C_master.h"

/*****************************************************************************
 * ADC Addresses
 *      There are four possible addresses that the ADC can have. However, due
 *      to the layout of the hep026 board, only two are possible without
 *      serious performance degradation. They are Ground and VDD. They are
 *      configurable by accessing PIN_ADC_ADDR. For completeness however, all
 *      four possible addresses will be documented here.
 *
 *      ADDR PIN | Slave Address
 *      ---------+--------------
 *      Ground   | 0b1001000
 *      VDD      | 0b1001001
 *      SDA      | 0b1001010
 *      SCL      | 0b1001011
 ****************************************************************************/
#define ADC_ADDR 0b10010000

/*****************************************************************************
 * ADC Registers
 *      Register           | Short Name | Value | R/W
 *      -------------------+------------+-------+----
 *      Conversion         | CONV       | 00    | R
 *      Config             | CONFIG     | 01    | R/W
 *      Lo_thresh_register | LO_THRESH  | 10    | R/W
 *      Hi_thresh_register | HI_THRESH  | 11    | R/w
 ****************************************************************************/
#define ADC_CONV_REGISTER      0b00000000
#define ADC_CONFIG_REGISTER    0b00000001
#define ADC_LO_THRESH_REGISTER 0b00000010
#define ADC_HI_THRESH_REGISTER 0b00000011

/*****************************************************************************
 * ADC Configuration Values
 *      Bit         |Field      |Value |Description
 *      ------------+-----------+------+--------------------------------------
 *      Bits[15]    |OS         |0     |No effect
 *      Bits[14:12] |MUX[2:0]   |000   |AIN_p = AIN0, AIN_n = AIN1
 *      Bits[11:9]  |PGA[2:0]   |001   |FS = ±4.096 V
 *      Bits[8]     |MODE       |0     |Continuous conversion mode
 *      Bits[7:5]   |DR[2:0]    |100   |128 SPS (samples per second)
 *      Bits[4]     |COMP_MODE  |0     |Traditional comparator with hysteresis
 *      Bits[3]     |COMP_POL   |0     |Active low
 *      Bits[2]     |COMP_LAT   |0     |Non-latching comparator
 *      Bits[1:0]   |COMP_QUE   |11    |Disable comparator
 ****************************************************************************/
#define ADC_CONFIG_MSB 0b00000010
#define ADC_CONFIG_LSB 0b10000011

/*****************************************************************************
 * Threshold registers
 *      These registers hold information on the upper and lower threshold of
 *      the ADC. Lo_thresh holds information on the minimum value possible
 *      (default 0x8000) and Hi_thresh holds information on the maximum
 *      possible value (default 0x7FFF). These are two's complement.
 *
 *      It is not normally necessary to change these.
 ****************************************************************************/
#define ADC_LO_THRESH_DEFAULT_MSB 0b10000000
#define ADC_LO_THRESH_DEFAULT_LSB 0b00000000
#define ADC_HI_THRESH_DEFAULT_MSB 0b01111111
#define ADC_HI_THRESH_DEFAULT_LSB 0b11111111

/*
 * Initializes the ADC to prepare for it to be ready to use
 */
void adc_init(void) {
	i2c_init();

	i2c_start_wait(ADC_ADDR+I2C_WRITE);
	i2c_write(ADC_CONFIG_REGISTER);
	i2c_write(ADC_CONFIG_MSB);
	i2c_write(ADC_CONFIG_LSB);

	i2c_stop();
}
