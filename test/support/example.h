#ifndef example_h_
#define example_h_

#include <inttypes.h>

void example_clock_low (void);
void example_clock_high (void);
void example_reset_low (void);
void example_reset_high (void);
void example_dq_set (uint8_t bit);
uint8_t example_dq_get (void);
void example_dq_set_output (void);
void example_dq_set_input (void);
void example_setup_ports (void);
void example_delay (unsigned long);

#endif