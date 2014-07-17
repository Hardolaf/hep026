/* Project definitions */
#include "defines.h"

/* Standard libraries */
#include <avr/io.h>
#include <util/delay.h>

/* Project libraries */
#include "mux.h"
#include "adc.h"

/****************************************************************************
 *                               Notes                                      *
 ***************************************************************************/
/*
 * Setting a pin to output:
 *    DDRX |= (1<<PXN);
 *      Where X is the pin set, N is the pin number
 * Setting a pin high:
 *    PORTX |= (1<<PXN);
 *      Where X is the pin set, N is the pin number
 * Setting a pin low:
 *    PORTX ~= (1<<PXN);
 */

int main(void) {
	// Set output pins (does not define I2C)
	DDRB |= 0b11110000;
	DDRC |= 0b11000000;
	DDRD |= 0b11011100;

	adc_init();

	while(1){
		mux_on();
		_delay_ms(100);
		for (uint8_t i; i < 50; i++) {
			mux_cycle();
			_delay_ms(100);
		}
	}

	return 0;
}
