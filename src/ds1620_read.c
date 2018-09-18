#include "ds1620_read.h"
#include "ds1620_receive_data.h"
#include "ds1620_send_command.h"
#include "ds1620_reset.h"

int ds1620_read(int command,
                struct ds1620_callbacks * callbacks)
{
  int value = 0;

  if(callbacks != 0)
  {
    ds1620_rst_start(callbacks);
    ds1620_send_command(command,callbacks); // Next 8 clock cycles output value of config register
    value = ds1620_receive_data(callbacks);
    ds1620_rst_stop(callbacks);
  }
  return (value);
}
