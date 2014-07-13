/* Standard library includes */
#include <avr/io.h>
#include <util/delay.h>

/* Project include */
#include "defines.h"

int main(void) {
	// Set pin 13 for output
	DDRB |= (1<<PB5);
	while(1){
		if (PORTB & (1<<PB5)) {
			PORTB &= ~(1<<PB5);
		} else {
			PORTB |= (1<<PB5);
		}
		_delay_ms(200);
	}

	return 0;
}
