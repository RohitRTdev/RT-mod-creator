#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "reader.h"
#include "io.h"
#include "error.h"

static void create_output_file_name(char* def_file_name, char* file_name)
{
	int i;
	for(i = 0; i < strlen(file_name); i++)
	{
		if(file_name[i] == '.')
		{
			break;
		}
		else
		{
			def_file_name[i] = file_name[i];
		}
	}

	def_file_name[i] = '\0';

	strcat(def_file_name, ".rm");
}

FILE* get_pe_file_descriptor(char* pe_file_name)
{
    return fopen(pe_file_name, "rb");
}

FILE* get_out_file_descriptor(char* out_file_name)
{
    return fopen(out_file_name, "wb+");
}


int start_file_processing(char** file_names, size_t file_start_arg, size_t number_of_files, char* output_file_name)
{

    FILE* pe_fd = NULL, *out_fd = NULL;
    char rt_output_name[50];

    if(number_of_files == 1 && output_file_name[0] != '\0')
    {
        pe_fd = get_pe_file_descriptor(file_names[file_start_arg]);
        out_fd = get_out_file_descriptor(output_file_name);

        if(check_for_errors((FILE* []){pe_fd, out_fd}, 2, output_file_name))
        {
            display_error_message("Invalid inputs", INVALID_PARAMETERS);
        }
        start_file_parse(pe_fd, out_fd, output_file_name);

    }
    else
    {
        for(size_t i = 0; i < number_of_files; i++)
        {
            pe_fd = get_pe_file_descriptor(file_names[i+file_start_arg]);

            create_output_file_name(rt_output_name, file_names[i+file_start_arg]);
            
            out_fd = get_out_file_descriptor(rt_output_name);

            if(check_for_errors((FILE* []){pe_fd, out_fd}, 2, rt_output_name))
            {
                display_error_message("Invalid inputs", INVALID_PARAMETERS);
            }

            start_file_parse(pe_fd, out_fd, rt_output_name);

        }
    }

    

}