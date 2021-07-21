#include <stdio.h>
#include "rt-defs.h"
#include "pe-defs.h"
#include "error.h"
#include "io.h"


int parse_pe_file(FILE* pe_fd, u64* image_entry, rt_sect_info* rt_extra);
void create_rt_executable(FILE* out_fd, FILE* pe_fd, rt_sect_info* rt_extra, u64 image_entry);

void start_file_parse(FILE* pe_fd, FILE* out_fd, char* output_file_name)
{
	rt_sect_info info_array[4] = {0};
	u64 image_entry = 0;
	
	int error_code = parse_pe_file(pe_fd, &image_entry, info_array);

	/* Delete created template files in case of error */
	if(ERROR(error_code))
	{
		close_handles((FILE* []){pe_fd, out_fd}, 2);
		remove(output_file_name);
		display_error_message("Invalid PE file", error_code);
	}
	create_rt_executable(out_fd, pe_fd, info_array, image_entry);

	close_handles((FILE* []){pe_fd, out_fd}, 2);
	
}