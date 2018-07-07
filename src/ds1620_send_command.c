#include "ds1620_send_command.h"

void ds1620_send_command(int command,
                         struct ds1620_callbacks * callbacks)
{
  int n;
  int bit;

  for (n = 0; n < 8; n++) {     // Always send 8 bits of data
    // Arithmetic bitwise shift command to the right, then AND with
    // bitmask (00000001) to return next bit, least significant (rightmost) first
    bit = (command >> n) & 0x01;
    callbacks->dq_set_callback(bit);       //digitalWrite(_DQ, bit); // DQ HIGH or LOW based on bit
    callbacks->clock_low_callback();       //digitalWrite(_CLK, LOW);  // CLK LOW then HIGH to make one cycle
    callbacks->clock_high_callback();      //digitalWrite(_CLK, HIGH);  
  }
}
