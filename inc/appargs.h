 /* *
  * pdmotiond - CNC backend deamon
  * (c) 2017 Benedikt M.
  *
  * appargs.h: Command line argument parsing (header)
  * */

#ifndef APPARGS_H
#define APPARGS_H

#include <stdio.h>
#include <string.h>

#include "defs.h"
#include "errors.h"

#define APPARGS_INIT { .flags = 0, .files_count = 0, .help_topic = NULL, .file_path = NULL, \
  .device_path = DEVICE_DEFAULT_PATH }

#define SET_ARG(ARG, ARGS) (ARGS) |= (1 << ((ARG) - 2))
#define HAS_ARG(ARG, ARGS) ((((ARGS) >> (ARG)) & 1) > 0)

// Application command line arguments
typedef struct {
  unsigned int flags;         // Application flags
  unsigned int files_count;   // Count of generic file path(s) (last argument(s))
  char* help_topic;           // Help topic to display
  char* file_path;            // Generic file path(s) (last argument(s))
  char* device_path;          // Path to the motion device
  float x;                    // X-axis parameter
  float y;                    // Y-axis parameter
  float z;                    // Z-axis parameter
  float a;                    // A-axis parameter
} appargs_t;

// Function specific errors enum
enum {
  ERR_UNKNOWN_FLAG    = ERR_EXTERN,     // Unknwon flag
  ERR_MIXED_ARGS      = ERR_EXTERN + 1  // Args mixed with file names
};

// Handled levels
enum {
  CLI_ARG_REQUIRED,
  CLI_ARG_HANDLED,
  CLI_ARG_OPTIONAL
};

// Flags enum
enum {
  CLI_ARGFIRST,         // Placeholder for the first argument
  CLI_ARGHANDLED,       // Placeholder for a handled argument
  CLI_FLAG_HELP,        // -h || --help
  CLI_FLAG_VERSION,     // --version
  CLI_FLAG_DEAMONIZE,   // -d || --deamonize
  CLI_FLAG_KILL_DEAMON, // -k || --kill; only with -d
  CLI_FLAG_FILENAME,    // Last filename in the command line args
  CLI_FLAG_MOVE,        // Move to absolute position
  CLI_FLAG_INCREMENT,   // Incrementally move to position
  CLI_FLAG_AXIS_X,      // X-axis modification flag
  CLI_FLAG_AXIS_Y,      // Y-axis modification flag
  CLI_FLAG_AXIS_Z,      // Z-axis modification flag
  CLI_FLAG_AXIS_A       // A-axis modification flag
};

elvl_t appargs_parse(unsigned int argc, char* argv[], appargs_t* args);
elvl_t appargs_attempt_parse_int(char* str, int* value);
elvl_t appargs_attempt_parse_uint(char* str, unsigned int* value);
elvl_t appargs_attempt_parse_float(char* str, float* value);

#endif
