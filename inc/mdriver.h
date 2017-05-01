/* *
 * pdmotiond - CNC backend deamon
 * (c) 2017 Benedikt M.
 *
 * mdriver.c: IOCTL interface to the motion driver kernel module (header)
 * */

#ifndef MDRIVER_H
#define MDRIVER_H

#include "types.h"
#include "errors.h"

// Initializing and cleanup routines
elvl_t mdriver_open(char* motion_device);
void mdriver_close(void);

// Raw register data r/w routines
elvl_t mdriver_write_reg(maddr_t address, mreg_t data);
elvl_t mdriver_read_reg(maddr_t address, mreg_t* data);

#endif
