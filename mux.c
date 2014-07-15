#include "defines.h"
#include "mux.h"

uint_8 mux1_state = B00000111;
uint_8 mux2_state = 0;

/*
 * Writes the current state of mux1_state and mux2_state to the muxes.
 */
void mux_write_state(void) {
	// Write the state of the first mux in order (A, B, C)
	if ((mux1_state<<1) != (PORTD<<PIN_MUX1_SEL_A)) {
		PORTD ^= PIN_MUX1_SEL_A;
	}
	if ((mux1_state<<2) != (PORTE<<PIN_MUX1_SEL_B)) {
		PORTE ^= PIN_MUX1_SEL_B;
	}
	if ((mux1_state<<3) != (PORTB<<PIN_MUX1_SEL_C)) {
		PORTB ^= PIN_MUX1_SEL_C;
	}

	// Write the state of the second mux in order (A, B, C)
	if ((mux2_state<<1) != (PORTB<<PIN_MUX2_SEL_A)) {
		PORTB ^= PIN_MUX2_SEL_A;
	}
	if ((mux2_state<<2) != (PORTB<<PIN_MUX2_SEL_B)) {
		PORTB ^= PIN_MUX2_SEL_B;
	}
	if ((mux2_state<<3) != (PORTB<<PIN_MUX2_SEL_C)) {
		PORTB ^= PIN_MUX2_SEL_C;
	}
}

void mux_off(void) {
	mux1_state = B00000111;
	mux2_state = 0;
	mux_write_state();
}

/*
 * Advances to the next valid mux state or off
 */
void mux_cycle(void) {
	if (mux1_state < 6) { 
		if (++mux2_state == 8) {
			mux1_state += 1;
			mux2_state = 0;
		}
		mux_write_state();
	} else if (mux1_state == 6) {
		if (++mux2_state == 2) {
			mux_off();
		}
		mux_write_state();
	}
}
