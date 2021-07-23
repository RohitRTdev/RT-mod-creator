#include <stdio.h>
#include <string.h>
#include "common.h"


bool check_for_string(char* string, const char** list, size_t number_of_strings)
{
    for(size_t index = 0; index < number_of_strings; index++)
    {
        if(!strcmp(string, list[index]))
        {
            return true;
        }
    }
    return false;
}