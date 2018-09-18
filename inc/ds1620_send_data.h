#ifndef _DS1620_SEND_DATA_H
#define _DS1620_SEND_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ds1620.h"

void ds1620_send_data(int data,
                      struct ds1620_callbacks * callbacks);

#ifdef __cplusplus
}
#endif

#endif // _DS1620_SEND_DATA_H
