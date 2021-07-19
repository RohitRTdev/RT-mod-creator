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
#include "error.h"
#include "reader.h"
#include "misc.h"
#include "cmd.h"

static void create_def_file_name(char* def_file_name, char* file_name)
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
static FILE* get_pe_file_descriptor(int argc, char** argv)
{
	FILE* pe_fd = NULL;
	if(argc >= 2)
	{
		pe_fd = fopen(argv[1], "rb");
	}

	return pe_fd;
}

static FILE* get_output_file_name(int argc, char** argv)
{
	FILE* out_fd = NULL;

	if(argc == 4 && !strcmp(argv[2], "-o"))
	{
		out_fd = fopen(argv[3], "wb+");
	}
	else
	{
		char def_file_name[50];
		create_def_file_name(def_file_name, argv[1]);
		out_fd = fopen(def_file_name, "wb+");
	}

	return out_fd;
}


int main(int argc, char** argv)
{

	FILE* pe_fd = NULL;
	FILE* out_fd = NULL;

	cmd_options option = parse_command_line_options(argc, argv);
	service_option(option);

	pe_fd = get_pe_file_descriptor(argc, argv);
	out_fd = get_output_file_name(argc, argv);

	if(!pe_fd || !out_fd)
		display_error_message("Invalid parameter passed!", INVALID_PARAMETERS);

	start_file_parse(pe_fd, out_fd);

	return 0;
}