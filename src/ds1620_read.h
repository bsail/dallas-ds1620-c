#ifndef _DS1620_READ_H
#define _DS1620_READ_H

#include "ds1620.h"

int ds1620_read(int command,
                struct ds1620_callbacks * callbacks);

#endif // _DS1620_READ_H
