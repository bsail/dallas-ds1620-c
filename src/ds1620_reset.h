#ifndef _DS1620_RESET_H
#define _DS1620_RESET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ds1620.h"

void ds1620_rst_start(struct ds1620_callbacks * callbacks);
void ds1620_rst_stop(struct ds1620_callbacks * callbacks);

#ifdef __cplusplus
}
#endif

#endif // _DS1620_RESET_H
