#include "ds1620_receive_data.h"

int ds1620_receive_data(struct ds1620_callbacks * callbacks)
{
  int data = 0;
  int n;
  int bit;

  if(callbacks!=0)
  {
    callbacks->dq_set_input_callback();      //pinMode(_DQ, INPUT); // Change Data/DQ pin mode to accept INPUT
    for (n = 0; n < 9; n++) {     // Always receive 9 bits of data
      callbacks->clock_low_callback();       //digitalWrite(_CLK, LOW);
      // bit = digitalRead(_DQ);
      bit = callbacks->dq_get_callback();
      callbacks->clock_high_callback();      //digitalWrite(_CLK, HIGH);
      data = data | bit << n;
    }
    callbacks->dq_set_output_callback();     //pinMode(_DQ, OUTPUT); // Done reading, set back to OUTPUT
  }

  return (data);
}
