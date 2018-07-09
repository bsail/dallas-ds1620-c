#ifndef _DS1620_SEND_COMMAND_H
#define _DS1620_SEND_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include "ds1620.h"

void ds1620_send_command(int command,
                         struct ds1620_callbacks * callbacks);

#ifdef __cplusplus
}
#endif

#endif // _DS1620_SEND_COMMAND_H
