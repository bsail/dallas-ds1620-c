#ifndef _DS1620_RECEIVE_DATA_H
#define _DS1620_RECEIVE_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ds1620.h"

int ds1620_receive_data(struct ds1620_callbacks * callbacks);

#ifdef __cplusplus
}
#endif

#endif // _DS1620_RECEIVE_DATA_H
