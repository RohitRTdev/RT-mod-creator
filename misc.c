#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "error.h"

#define APP_VERSION "1.0"
#define HELP_MSG_PATH "resources/help-msg.txt"
#define VERSION_FILE_PATH "resources/version-msg.txt"

static bool read_file_msg(const char* msg_file_name)
{
    static size_t max_line_length = 10000;
    FILE* msg_fd = fopen(msg_file_name, "r");

    if(msg_fd == NULL)
        return false;

    char* msg_buffer = malloc(max_line_length);
    size_t buf_size = max_line_length;
    while(!feof(msg_fd))
    {
        getline(&msg_buffer, &buf_size, msg_fd);
        printf("%s", msg_buffer);
        msg_buffer[0] = '\0';
    }

    fclose(msg_fd);
    free(msg_buffer);
    return true;

}

void display_version()
{
    if(!read_file_msg(VERSION_FILE_PATH))
    {
        display_error_message("Version message not found!", RESOURCE_NOT_FOUND);
    }
}

void display_help()
{
    if(!read_file_msg(HELP_MSG_PATH))
    {
        display_error_message("Help message not found!", RESOURCE_NOT_FOUND);
    }
        
}