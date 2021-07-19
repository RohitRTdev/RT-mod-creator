#include "error.h"
#include <stdio.h>
#include <stdlib.h>

void display_error_message(char* message, int exit_code)
{
	printf("rtmodx64:%s\r\n", message);

	exit(exit_code);
}
