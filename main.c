/*
 * Program to create a RT executable 
 * from a PE file.
 * The RT format is really easy
 * and it's design allows for
 * only 4 sections as of v1
 * .text, .data, .bss, .reloc
 * 
 * Format is as follows
 * [RT_HEADER](Metadata)
 * [TEXT](Raw data)
 * [DATA](Raw data)
 * [RELOC](Raw data)
 * 
 * Note that .bss section is 
 * not present in the file itself
 * and should be allocated by the 
 * loader when the image is loaded 
 * into memory.
 * 
 * The format for the above 
 * structures can be found within the 
 * header file rt-defs.h.
 * 
 * If any section is not present
 * in the image file, then it 
 * simply places a value of 0
 * for all the members in that
 * section entry to indicate the
 * section is not present.
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "error.h"
#include "misc.h"
#include "cmd.h"
#include "defs.h"
#include "common.h"

char prog_name[50];

static bool check_arg_opt(char* option)
{
	if(option[0] == '-')
		return true;
	else	
		return false;
}

static bool check_option_validity(char* option)
{
	if(check_arg_opt(option))
	{
		if(check_for_string(option, command_line_options, TOTAL_PRE_INPUT_OPTIONS))
			return false;
	}

	return true;
}

static void get_file_args(int argc, char** argv, size_t* number_of_files, size_t* file_args_start, char* output_file_name)
{
	int file_start = -1;
	for(size_t i = 1; i < argc ; i++)
	{
		if(STRING_CHECK(i, -o, --output))
		{
			if(*number_of_files > 1)
			{
				display_error_message("Cannot supply multiple input files with '-o' flag", INVALID_PARAMETERS);
			}
			else
			{
				if(i == argc - 1)
				{
					display_error_message("'-o' option mentioned with no output file name", OUTPUT_FILE_MISSING);
				}
				strcpy(output_file_name, argv[i+1]);
				*number_of_files = 1;
			}
			break;
		}
		if(!check_arg_opt(argv[i]) || !check_option_validity(argv[i]))
		{
			if(file_start == -1)
			{
				file_start = i;
				*file_args_start = i;
			}

			(*number_of_files)++;
		}
	}
}


int main(int argc, char** argv)
{
	size_t file_args_start = 0, number_of_files = 0;

	strcpy(prog_name, argv[0]);

	char output_file_name[50] = {'\0'};
	cmd_options option = parse_command_line_options(argc, argv, PROCESS_STDIN);
	service_option(option);

	char** command_line = argv;
	size_t commands = argc;

	if(option == INPUT_FROM_STDIN)
	{
		commands = word_array_length;
		command_line = stdin_command_line;

		option = parse_command_line_options(commands, command_line, NO_PROCESS_STDIN);
		service_option(option);
	}
	
	if(option == FILE_OPT)
		get_file_args(commands ,command_line, &number_of_files, &file_args_start, output_file_name);

	if(number_of_files == 0)
	{
		display_error_message("No input files", INVALID_PARAMETERS);
	}
	else
	{
		start_file_processing(command_line, file_args_start, number_of_files, output_file_name);
	}


	return 0;
}