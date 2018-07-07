#ifndef _DS1620_SEND_DATA_H
#define _DS1620_SEND_DATA_H

#include "ds1620.h"

void ds1620_send_data(int data,
                      struct ds1620_callbacks * callbacks);

#endif // _DS1620_SEND_DATA_H
