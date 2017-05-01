/* *
 * pdmotiond - CNC backend deamon
 * (c) 2017 Benedikt M.
 *
 * errors.h: Global, application-wide error-levels
 * */

#ifndef ERRORS_H
#define ERRORS_H

#include <stdint.h>

// Error level typedef
typedef uint16_t elvl_t;

// Error enum
enum {
  ERR_NONE,       // Success
  ERR_ARGNULLP,   // Argument is nullptr
  ERR_ARGINV,     // Argument is invalid
  ERR_ARGRANGE,   // Argument range invalid
  ERR_SYNTAX,     // Invocation syntax invalid
  ERR_DBLINIT,    // Double init
  ERR_FOPEN,      // File open failed
  ERR_IOCTL,      // IOCTL failed

  ERR_EXTERN      // Start of the function specific errors
};

#endif
