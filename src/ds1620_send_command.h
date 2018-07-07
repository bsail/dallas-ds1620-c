#ifndef _DS1620_SEND_COMMAND_H
#define _DS1620_SEND_COMMAND_H

#include <inttypes.h>
#include "ds1620.h"

void ds1620_send_command(int command,
                         struct ds1620_callbacks callbacks);

#endif // _DS1620_SEND_COMMAND_H
