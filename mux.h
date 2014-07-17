#ifndef MUX_H_INNCLUDED
#define MUX_H_INNCLUDED

void mux_write_state(void);

extern void mux_off(void);

extern void mux_on(void);

extern void mux_cycle(void);

extern int mux_get_state(void);

#endif
