#include "ds1620_send_data.h"

void ds1620_send_data(int data,
                      struct ds1620_callbacks * callbacks)
{
  int n;
  int bit;

  if(callbacks!=0)
    for (int n = 0; n < 9; n++) { // Send all nine bits of temperature
      bit = (data >> n) & 0x01;
      callbacks->dq_set_callback(bit);       //digitalWrite(_DQ, bit); // DQ HIGH or LOW based on bit
      callbacks->clock_low_callback();       //digitalWrite(_CLK, LOW);  // CLK LOW then HIGH to make one cycle
      callbacks->clock_high_callback();      //digitalWrite(_CLK, HIGH);  
    }
}
