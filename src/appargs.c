/* *
 * pdmotiond - CNC backend deamon
 * (c) 2017 Benedikt M.
 *
 * appargs.c: Command line argument parsing
 * */

#include "appargs.h"

// Shorthand is string equal function
#define STREQ(s,t) (strcmp(s,t) == 0)

elvl_t appargs_parse(unsigned int argc, char* argv[], appargs_t* args)
{
  // Check the arguments for validity
  if(!argc)
    return ERR_ARGRANGE;
  if(!argv || !args)
    return ERR_ARGNULLP;


  unsigned int arg;
  int lastflag = CLI_ARGFIRST, lasthandled = CLI_ARG_HANDLED;
  char* argstr;

  // Loop through the arguments
  for(arg = 1; arg < argc; arg++) {
    argstr = argv[arg];

    // Skip empty arguments
    if(!strlen(argstr))
      continue;

    // Check required arguments
    if(argstr[0] != '-' || lastflag == CLI_FLAG_FILENAME || lasthandled == CLI_ARG_REQUIRED) {
      int check_file_exist = 0;
      // Check the last set flag
      switch(lastflag) {
        // Check if we already had an anonymous file name as the last argument
        case CLI_FLAG_FILENAME:
          if(argstr[0] != '-') {
            // We can't have multiple anonymous file names following each other
            fprintf(stderr, "Error: Unexpected filename '%s'!\n", argstr);
            return ERR_SYNTAX;
          } else {
            // Mixed filenames / flags, which is forbidden
            fprintf(stderr, "Error: Unexpected argument '%s' after filename!\n", argstr);
            return ERR_MIXED_ARGS;
          }
        break;

        case CLI_FLAG_HELP:
          // Store the help topic
          args->help_topic = argstr;
          // Mark the argument as handled and done
          lasthandled = CLI_ARG_HANDLED;
        break;

        // Deamonize allows optionally specifying the device path
        case CLI_FLAG_DEAMONIZE:
          // Since it is specified, it must exist
          check_file_exist = 1;
          // Now store the filename
          args->device_path = argstr;
          // Mark the argument as handled and done
          lasthandled = CLI_ARG_HANDLED;
        break;

        case CLI_ARGFIRST:
          // Always fail, as a sole filename is not a valid syntax here
          fprintf(stderr, "Error: Unexpected filename '%s'!\n", argstr);
          return ERR_SYNTAX;
        break;

        case CLI_FLAG_AXIS_X:
          // Try to read the float into our register
          if(appargs_attempt_parse_float(argstr, &(args->x)) != ERR_NONE) {
            fprintf(stderr, "Error: Failed to parse -x '%s' as float!\n", argstr);
            return ERR_ARGINV;
          }
          // Mark argument as handled
          lasthandled = CLI_ARG_HANDLED;
        break;

        case CLI_FLAG_AXIS_Y:
          // Try to read the float into our register
          if(appargs_attempt_parse_float(argstr, &(args->y)) != ERR_NONE) {
            fprintf(stderr, "Error: Failed to parse -y '%s' as float!\n", argstr);
            return ERR_ARGINV;
          }
          // Mark argument as handled
          lasthandled = CLI_ARG_HANDLED;
        break;

        case CLI_FLAG_AXIS_Z:
          // Try to read the float into our register
          if(appargs_attempt_parse_float(argstr, &(args->z)) != ERR_NONE) {
            fprintf(stderr, "Error: Failed to parse -z '%s' as float!\n", argstr);
            return ERR_ARGINV;
          }
          // Mark argument as handled
          lasthandled = CLI_ARG_HANDLED;
        break;

        case CLI_FLAG_AXIS_A:
          // Try to read the float into our register
          if(appargs_attempt_parse_float(argstr, &(args->a)) != ERR_NONE) {
            fprintf(stderr, "Error: Failed to parse -a '%s' as float!\n", argstr);
            return ERR_ARGINV;
          }
          // Mark argument as handled
          lasthandled = CLI_ARG_HANDLED;
        break;

        default:
          // Anonymous filename as last argument
          SET_ARG((lastflag = CLI_FLAG_FILENAME), args->flags);
          // Store the filename
          args->file_path = argstr;
          // Must exist
          check_file_exist = 1;
        break;
      }

      // Check if the file exists
      if(check_file_exist) {

      }

    } else if(STREQ(argstr, "-h") || STREQ(argstr, "--help")) {
      SET_ARG((lastflag = CLI_FLAG_HELP), args->flags);
      lasthandled = CLI_ARG_OPTIONAL;
    } else if(STREQ(argstr, "--version")) {
      SET_ARG((lastflag = CLI_FLAG_VERSION), args->flags);
      lasthandled = CLI_ARG_HANDLED;
    } else if(STREQ(argstr, "-d") || STREQ(argstr, "--deamonize")) {
      SET_ARG((lastflag = CLI_FLAG_DEAMONIZE), args->flags);
      lasthandled = CLI_ARG_OPTIONAL;
    } else if(STREQ(argstr, "-k") || STREQ(argstr, "--kill-deamon")) {
      SET_ARG((lastflag = CLI_FLAG_KILL_DEAMON), args->flags);
      lasthandled = CLI_ARG_HANDLED;
    } else if(STREQ(argstr, "-m") || STREQ(argstr, "--move-linear")) {
      SET_ARG((lastflag = CLI_FLAG_MOVE), args->flags);
      lasthandled = CLI_ARG_HANDLED;
    } else if(STREQ(argstr, "-i") || STREQ(argstr, "--increment")) {
      SET_ARG((lastflag = CLI_FLAG_INCREMENT), args->flags);
      lasthandled = CLI_ARG_HANDLED;
    } else if(STREQ(argstr, "-x")) {
      SET_ARG((lastflag = CLI_FLAG_AXIS_X), args->flags);
      lasthandled = CLI_ARG_REQUIRED;
    } else if(STREQ(argstr, "-y")) {
      SET_ARG((lastflag = CLI_FLAG_AXIS_Y), args->flags);
      lasthandled = CLI_ARG_REQUIRED;
    } else if(STREQ(argstr, "-z")) {
      SET_ARG((lastflag = CLI_FLAG_AXIS_Z), args->flags);
      lasthandled = CLI_ARG_REQUIRED;
    } else if(STREQ(argstr, "-a")) {
      SET_ARG((lastflag = CLI_FLAG_AXIS_A), args->flags);
      lasthandled = CLI_ARG_REQUIRED;
    } else { // Invalid command
      fprintf(stderr, "Error: Unknown flag '%s'!\n", argstr);
      return ERR_UNKNOWN_FLAG;
    }

  }

  return ERR_NONE;
}

elvl_t appargs_attempt_parse_int(char* str, int* value)
{
  return (!sscanf(str, "%i", value)) ? ERR_ARGINV : ERR_NONE;
}

elvl_t appargs_attempt_parse_uint(char* str, unsigned int* value)
{
  return (!sscanf(str, "%u", value)) ? ERR_ARGINV : ERR_NONE;
}

elvl_t appargs_attempt_parse_float(char* str, float* value)
{
  return (!sscanf(str, "%f", value)) ? ERR_ARGINV : ERR_NONE;
}
