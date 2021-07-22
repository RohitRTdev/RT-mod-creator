#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "error.h"
#include "cmd.h"
#include "misc.h"
#include "defs.h"

#define PROCESS_FURTHER break

typedef enum{
    REGULAR_FILE,
    KEYBOARD
}devices;

const char* command_line_options[] = {"-h", "--help",
                                      "-v", "--version"};

char** stdin_command_line;
size_t word_array_length;

static int get_stdin_device()
{
    struct stat device_info;
    fstat(STDIN_FILENO, &device_info);

    if(S_ISCHR(device_info.st_mode) || S_ISBLK(device_info.st_mode))
        return KEYBOARD;
    else
        return REGULAR_FILE;
}

static bool retrieve_input_stdin()
{
#define UNIT_STDIN_CHUNK_SIZE 1000
#define MAX_WORD_QUANTITY 1000
    if(get_stdin_device() == KEYBOARD)
    {
        return false;
    }

    char* stdin_input_buffer = malloc(UNIT_STDIN_CHUNK_SIZE);
    size_t actual_size = read(STDIN_FILENO, stdin_input_buffer, UNIT_STDIN_CHUNK_SIZE);

    size_t bytes_read = actual_size, buffer_size = 2 * UNIT_STDIN_CHUNK_SIZE;

    while(bytes_read == UNIT_STDIN_CHUNK_SIZE)
    {
        stdin_input_buffer = realloc(stdin_input_buffer, buffer_size);
        bytes_read = read(STDIN_FILENO, stdin_input_buffer, bytes_read);
        actual_size += bytes_read;
        buffer_size += UNIT_STDIN_CHUNK_SIZE;
    }


    char** word_array = malloc(MAX_WORD_QUANTITY);
    size_t word = 1;

    word_array[0] = prog_name;

    size_t ch = 0;

    /* Remove leading whitespaces */
    while(stdin_input_buffer[ch] == ' ' && ch < actual_size)
    {
        ch++;
    }

    while(ch < actual_size)
    {
        word_array[word++] = &stdin_input_buffer[ch];
        while(stdin_input_buffer[ch] != ' ' && stdin_input_buffer[ch] != '\n' && stdin_input_buffer[ch] != '\0')
        {
            ch++;
        }

        stdin_input_buffer[ch] = '\0';
        ch++;
    }

    stdin_command_line = word_array;
    word_array_length = word;

    if(word_array_length > MAX_WORD_QUANTITY)
    {
        display_error_message("you have overcome the max number of arguments in list", RESOURCE_OVERFLOW);
    }

    return true;

}


int parse_command_line_options(int argc, char** argv, int flag)
{
    switch(argc)
    {
        case 1: {

            if(flag == PROCESS_STDIN && retrieve_input_stdin())
            {
                return INPUT_FROM_STDIN;
            }
            else
            {
                return NO_OPTIONS;
            }
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