#ifndef _CMD_H_
#define _CMD_H_

/* Options */

typedef enum {
    INVALID,
    NO_OPTIONS,
    VERSION,
    HELP,
    FILE_OPT
}cmd_options;


int parse_command_line_options(int argc, char** argv);
void service_option(cmd_options option);


#endif