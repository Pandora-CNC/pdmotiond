/* *
 * pdmotiond - CNC backend deamon
 * (c) 2017 Benedikt M.
 *
 * driver.h: IOCTL interface to the kernel module (header)
 * */

#ifndef DRIVER_H
#define DRIVER_H

#include "types.h"
#include "errors.h"

// Initializing and cleanup routines
elvl_t driver_open(char* motion_device);
void driver_close(void);

// Raw data r/w routines
elvl_t driver_write(maddr_t address, mreg_t data);
elvl_t driver_read(maddr_t address, mreg_t* data);

#endif
