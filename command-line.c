#include <string.h>
#include <stdlib.h>
#include "cmd.h"
#include "error.h"
#include "misc.h"
#include "defs.h"

#define PROCESS_FURTHER break

int parse_command_line_options(int argc, char** argv, size_t* file_args_start)
{
    switch(argc)
    {
        case 1: {
            return NO_OPTIONS;
            break;
        }
        case 2: {
            if(STRING_CHECK(1, -v, --version))
                return VERSION;
            else if(STRING_CHECK(1, -h, --help))
                return HELP;
            else
                return FILE_OPT;
            break;
        }
        default: {
            return FILE_OPT;
        }
    }
    return INVALID;
}

void service_option(cmd_options option)
{
    switch(option)
    {
        case NO_OPTIONS: {
            display_error_message("Please pass an option or input a file", INVALID_PARAMETERS);
        }
        case HELP: {
            display_help();
            exit(0);
        }       
        case VERSION: {
            display_version();
            exit(0);
        }
        case INVALID: {
            display_error_message("Invalid parameters!", INVALID_PARAMETERS);
        }
        default: {
            PROCESS_FURTHER;
        }
    }
}