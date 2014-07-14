/* Project include */
#include "defines.h"

/* Standard library includes */
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	// Set pin 13 for output
	DDRC |= (1<<PC7);
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
