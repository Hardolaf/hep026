/* Project definitions */
#include "defines.h"

/* Standard libraries */
#include <avr/io.h>
#include <util/delay.h>

/* Project libraries */
#include "mux.h"

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
 *    PORTX |= (1<<PXN);
 */

int main(void) {
	// Set pin 13 for output
	DDRC |= (1<<PC7);

	PORTC |= (1<<PC7);
	_delay_ms(5000);
	while(1){
		if (PORTC & (1<<PC7)) {
			PORTC &= ~(1<<PC7);
		} else {
			PORTC |= (1<<PC7);
		}
		_delay_ms(500);
	}

	return 0;
}
