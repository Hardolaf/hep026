#include "defines.h"
#include "mux.h"

#include <avr/io.h>

uint8_t mux_state = 0b00111000;

void mux_write_state(void) {
	uint8_t mask = ((mux_state<<1)<<PIN_MUX1_SEL_A);
	if (!(PORTD & mask)) {
		PORTD ^= mask;
	}

	mask = ((mux_state<<2)<<PIN_MUX1_SEL_B);
	if (!(PORTE & mask)) {
		PORTE ^= mask;
	}

	mask = ((mux_state<<3)<<PIN_MUX1_SEL_C);
	if (!(PORTB & mask)) {
		PORTB ^= mask;
	}

	mask = ((mux_state<<4)<<PIN_MUX2_SEL_A);
	if (!(PORTB & mask)) {
		PORTB ^= mask;
	}

	mask = ((mux_state<<5)<<PIN_MUX2_SEL_B);
	if (!(PORTB & mask)) {
		PORTB ^= mask;
	}

	mask = ((mux_state<<6)<<PIN_MUX2_SEL_C);
	if (!(PORTB & mask)) {
		PORTB ^= mask;
	}
}

/*
 * Turns the muxes off.
 */
void mux_off(void) {
	mux_state = 0b00111000;
	mux_write_state();
}

/*
 * Turns the first mux channel on
 */
void mux_on(void) {
	mux_state = 0;
	mux_write_state();
}

/*
 * Advances to the next valid mux state or off
 */
void mux_cycle(void) {
	if (mux_state < 50) {
		mux_state += 1;
	} else {
		mux_off();
	}
}

/*
 * Returns the current state of the mux as an int
 */
int mux_get_state(void) {
	return mux_state;
}
