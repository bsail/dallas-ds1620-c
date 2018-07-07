#ifndef _DS1620_RESET_H
#define _DS1620_RESET_H

#include "ds1620.h"

void ds1620_rst_start(struct ds1620_callbacks * callbacks);
void ds1620_rst_stop(struct ds1620_callbacks * callbacks);

#endif // _DS1620_RESET_H
