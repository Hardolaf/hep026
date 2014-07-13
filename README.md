# BPM Data Acquisition System

**Project**: hep026

**Author**: Joseph D Warner <<warner.512@osu.edu>>

**Organization**: The Ohio State University

**Version**: 0.1

**Date**: 2014/07/11

## Purpose

This software aims to control the BPM Data Acquisition System that is being
built for CERN for use on Proton Sychrotron particle accelerator to collect
data from beam profile monitors (BPM) located at
[IRRAD-1](https://irradiation.web.cern.ch/irradiation/irrad1.htm).

## Hardware Requirements

This software is designed to work with the hep026 rev. 1 board designed by
Joseph Warner of The Ohio State University ATLAS Group. If this software is
not being used with that board but instead with some equivalent board, certain
constants may need to be updated in *defines.h*. The microcontroller daughter
board used in this project is the Arduino Yun which has basic information
detailed below.

### Arduino Yun Details

The [Arduino Yun](http://arduino.cc/en/Main/ArduinoBoardYun?from=Products.ArduinoYUN)
is an open source prototyping board that is designed with two processors:
ATmega32u4 and the Atheros AR9331.

#### ATmega32u4

The [ATmega32u4](http://www.atmel.com/devices/ATMEGA32U4.aspx) controls all of
the input and output pins on the Arduino Yun. It provides a
[pinout digaram](http://arduino.cc/en/Hacking/PinMapping32u4) on Arduino's
official website showing the mapping between the pins on the mcu and their
function on the Arduino Yun. A summary of its functionality is provided below
taken from the official product page of the Arduino Yun.

Microcontroller | ATmega32u4
--------------- | ----------
Operating Voltage | 5V
Input Voltage | 5V
Digital I/O Pins | 20
PWM Channels | 7
Analog Input Channels | 12
DC Current per I/O Pin | 40 mA
DC Current for 3.3V Pin | 50 mA
Flash Memory | 32 KB (of which 4 KB used by bootloader)
SRAM | 2.5 KB
EEPROM | 1 KB
Clock Speed | 16 MHz

#### Atheros AR9331

The [Atheros AR9331](http://www.openhacks.com/uploadsproductos/ar9331_datasheet.pdf)
provides a linux based operating system for the Arduino Yun. It is connected
to an ethernet port and WiFi radio that allow communication via the Internet.
A short summary of its capabilities is provided below from the official
product page of the Arduino Yun.

Processor | Atheros AR9331
--------- | --------------
Architecture | MIPS @400MHz
Operating Voltage | 3.3V
Ethernet | IEEE 802.3 10/100Mbit/s
WiFi | IEEE 802.11b/g/n
USB Type-A | 2.0 Host
Card Reader | Micro-SD only
RAM | 64 MB DDR2
Flash Memory | 16 MB

### Constants and Signals

The hardware constants defined in *defines.h* are mapped to physical pins on
the hep026 board and on the Arduino Yun itself.

#### Serial

The serial interface of the Arduin Yun are a fixed set of pins, Digital 0 (RX)
and Digital 1 (TX). These pins on the ATmega32u4 are connected directly to
corresponding serial pins on the Atheros AR9331. Thus, it is not reccommended
to modify what pins are used for serial communication as it will prevent any
communication between the two processors on the Arduino Yun.

    /* Serial Interface */
    #define PIN_SERIAL_RX PD2 // D0
    #define PIN_SERIAL_TX PD3 // D1

#### I2C and ADC control

The 16 bit analog-to-digital converter on the Arduino Yun is operates with
four pins: Digital 2 (SDA), Digital 3 (SCL), Digital 4 (ALERT_RDY), and
Digital 5 (ADDR). These pins are all directly mapped to the corresponding pins
on the ads1115 chip on the hep026 board.  It is not reccomended to move SDA
and SCL from pins 2 and 3 because these pins on the Arduino Yun have hardware
interrupt capabilities provided by the ATmega32u4.

    /* I2C Interface */
    #define PIN_I2C_SDA PD1 // D2
    #define PIN_I2C_SCL PD0 // D3
    /* ADC Control */
    #define PIN_ADC_ALERT_RDY PD4 // D4
    #define PIN_ADC_ADDR PC6 // D5

#### MUX Selection

On the hep026 board, there are 8 multiplexers that determine which integrator
is currently sending data towards the ADC. These multiplexers are 3-to-8
converters. They are separated into two sets: MUX1 and MUX2. MUX1 is a
single multiplexer that controls which multiplexer in MUX2 will output to the
integrators. MUX2 is a set of 7 integrators which determine which integrator
channel will output.

The precise placemenet of this pins on any board seeking to have a similar
control mechanism is not necessary, however care should be taken to change all
outputs rapidly on the microcontroller when changing which integrator channel
is active.

    /* MUX 1 Selection */
    #define PIN_MUX1_SEL1_A PD7 // D6
    #define PIN_MUX1_SEL1_B PE6 // D7
    #define PIN_MUX1_SEL1_C PB4 // D8
    /* MUX 2 Selection */
    #define PIN_MUX2_SEL2_A PB5 // D9
    #define PIN_MUX2_SEL2_B PB6 // D10
    #define PIN_MUX2_SEL2_C PB7 // D11

#### Integrator Control

The functionality of these pins is to the HOLD and RES gates on the acf2101
integrators on the hep026 board.

The HOLD pin is used to disconnect the input current and hold the output
voltage at a fixed level. When reading data from the integrator into the ADC,
HOLD should held high (1). When collecting data from inputs, HOLD should be
held low (0).

The RES pin is used to discharge the capacitors in the acf2101 integrators.
When discharging the capacitors, RESET should be held low (0), otherwise it
should be held high (1) at all times. The state of HOLD does not matter when
discharging the capacitors.

If making a similar board, care should be taken to ensure that thee is
sufficient output current from these pins to drive the acf2101 integrators.

    #define PIN_INT_RES PD6 // D12
    #define PIN_INT_HOLD PC7 // D13

#### External Inputs

The hep026 board has two external triggers that provide it information about
when data collection should occur. There are the Trigger and CPS signals.
When they change state, it is expected that board begin or stop collecting
data.

These pins do not need to be connected to interrupts as polling is fast enough
to detect the signals.

    /* External Inputs */
    #define PIN_EXT_TRIGGER PF7 //A0
    #define PIN_EXT_CPS PF6 // A1

## Software Requirements

## Using This Software

To use this software you will need to compile it and then load it onto the
microcontroller.

To compile this software you must run

    make

To then subsequentely load the compiled program onto the microcontroller run

    make program

To clean the build directory of the project run

    make clean
