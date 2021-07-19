#include <string.h>
#include <stdlib.h>
#include "cmd.h"
#include "error.h"
#include "misc.h"


#define STRING_CHECK(index, string1, string2) (!strcmp(argv[index], #string1) || !strcmp(argv[index], #string2))

int parse_command_line_options(int argc, char** argv)
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
        case 4: {
            if(STRING_CHECK(2, -o, --output))
                return FILE_OPT;
            else
                return INVALID;
            
            break;
        }
        default: {
            return INVALID;
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
        case FILE_OPT: {
            break;
        }
        default: {
            display_error_message("Invalid parameters!", INVALID_PARAMETERS);
        }
    }
}