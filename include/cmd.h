#ifndef _CMD_H_
#define _CMD_H_

/* Options */

typedef enum {
    INVALID,
    NO_OPTIONS,
    VERSION,
    HELP,
    FILE_OPT,
    INPUT_FROM_STDIN
}cmd_options;

#define TOTAL_PRE_INPUT_OPTIONS 4
#define PROCESS_STDIN 0
#define NO_PROCESS_STDIN 1

int parse_command_line_options(int argc, char** argv, int flag);
void service_option(cmd_options option);
void start_file_processing(char** argv, size_t file_args_start, size_t number_of_files, char* output_file_name);

extern const char* command_line_options[];
extern char** stdin_command_line;
extern size_t word_array_length;


#endif