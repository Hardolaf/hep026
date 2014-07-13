
// CPU Frequency
#define F_CPU 16000000UL

/*****************************************************************************
*             Define the pin mappings for various functions                  *
*****************************************************************************/
/* Serial Interface */
#define PIN_SERIAL_RX PD2 // D0
#define PIN_SERIAL_TX PD3 // D1
/* I2C Interface */
#define PIN_I2C_SDA PD1 // D2
#define PIN_I2C_SCL PD0 // D3
/* ADC Control */
#define PIN_ADC_ALERT_RDY PD4 // D4
#define PIN_ADC_ADDR PC6 // D5
/* MUX 1 Selection */
#define PIN_MUX1_SEL1_A PD7 // D6
#define PIN_MUX1_SEL1_B PE6 // D7
#define PIN_MUX1_SEL1_C PB4 // D8
/* MUX 2 Selection */
#define PIN_MUX2_SEL2_A PB5 // D9
#define PIN_MUX2_SEL2_B PB6 // D10
#define PIN_MUX2_SEL2_C PB7 // D11
/* Integrator */
#define PIN_INT_RES PD6 // D12
#define PIN_INT_HOLD PC7 // D13
/* External Inputs */
#define PIN_EXT_TRIGGER PF7 //A0
#define PIN_EXT_CPS PF6 // A1
