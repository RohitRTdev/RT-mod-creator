#ifndef _ERROR_H_
#define _ERROR_H_

#define NO_ERROR 0
#define INVALID_PARAMETERS 1
#define INVALID_PE_FILE 2

#define ERROR(error_code) (error_code != 0)

void display_error_message(char* message, int exit_code);


#endif