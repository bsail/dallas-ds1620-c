#include "ds1620_reset.h"

void ds1620_rst_start(struct ds1620_callbacks * callbacks)
{
  if(callbacks!=0)
  {
    callbacks->reset_low_callback();         // digitalWrite(_RST, LOW);
    callbacks->clock_high_callback();        //digitalWrite(_CLK, HIGH);
    callbacks->reset_high_callback();        //digitalWrite(_RST, HIGH); // All communications start by taking RST HIGH
  }
}

void ds1620_rst_stop(struct ds1620_callbacks * callbacks)
{
  if(callbacks!=0)
    callbacks->reset_low_callback();         //digitalWrite(_RST, LOW); // Taking RST LOW will terminate any communication
}
