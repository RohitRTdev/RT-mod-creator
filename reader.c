#include <stdio.h>
#include "rt-defs.h"
#include "pe-defs.h"

void parse_pe_file(FILE* pe_fd, u64* image_entry, rt_sect_info* rt_extra);
void create_rt_executable(FILE* out_fd, FILE* pe_fd, rt_sect_info* rt_extra, u64 image_entry);

void start_file_parse(FILE* pe_fd, FILE* out_fd)
{
	rt_sect_info info_array[4] = {0};
	u64 image_entry;
	
	parse_pe_file(pe_fd, &image_entry, info_array);
	create_rt_executable(out_fd, pe_fd, info_array, image_entry);

	fclose(pe_fd);
	fclose(out_fd);
}