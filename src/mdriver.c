/* *
 * pdmotiond - CNC backend deamon
 * (c) 2017 Benedikt M.
 *
 * mdriver.c: IOCTL interface to the motion driver kernel module
 * */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "mdriver.h"

// The device file descriptor
int mdriver_fp = -1;

// The internal ioctl constants
// Read and write from and to 16-bit registers
const unsigned int MOTION_REG_WRITE  = 0x4620u;
const unsigned int MOTION_REG_READ   = 0x4621u;
// Load interpolation data from user-space to the FPGA
const unsigned int MOTION_IPOL_LOAD  = 0x4622u;
// Unknown ioctl, not used in original application
const unsigned int MOTION_UNKNOWN_0  = 0x4623u;
// Read and write from and to FRAM (not inplemented in driver)
const unsigned int MOTION_FRAM_WRITE = 0x4624u;
const unsigned int MOTION_FRAM_READ  = 0x4625u;

elvl_t mdriver_open(char* motion_device)
{
  if(mdriver_fp =! -1)
    return ERR_DBLINIT;
  if((mdriver_fp = open(motion_device, O_RDWR)) == -1)
    return ERR_FOPEN;
  return ERR_NONE;
}

void mdriver_close(void)
{
  if(mdriver_fp != -1)
    close(mdriver_fp);
  mdriver_fp = -1;
}

elvl_t mdriver_write_reg(maddr_t address, mreg_t data)
{
  unsigned int buf[2];
  buf[0] = address;
  buf[1] = data;

  if(ioctl(mdriver_fp, MOTION_REG_WRITE, &buf) != 0)
    return ERR_IOCTL;
  return ERR_NONE;
}

elvl_t mdriver_read_reg(maddr_t address, mreg_t* data)
{
  unsigned int buf[2];
  buf[0] = address;
  buf[1] = (unsigned int)-1;

  if(ioctl(mdriver_fp, MOTION_REG_READ, &buf) != 0)
    return ERR_IOCTL;
  *data = buf[1];
  return ERR_NONE;
}
