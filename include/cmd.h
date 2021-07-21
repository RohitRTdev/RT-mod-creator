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


int parse_command_line_options(int argc, char** argv, size_t* file_args_start);
void service_option(cmd_options option);
void start_file_processing(char** argv, size_t file_args_start, size_t number_of_files, char* output_file_name);


#endif