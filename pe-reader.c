#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "pe-defs.h"
#include "io.h"
#include "error.h"
#include "rt-defs.h"
#include "common.h"


const char* rt_section_table[] = {".text", ".data", ".bss", ".reloc"};

#define RT_SECTION_TABLE_SIZE 4

#define SET_RT_EXTRA(sect_number) {																		  \
									strcpy(rt_extra[sect_number].sect_name, ms_sect_table.name);          \
									rt_extra[sect_number].ptr_to_sect = ms_sect_table.ptr_to_raw_data;    \
 									rt_extra[sect_number].size_of_sect = ms_sect_table.size_of_raw_data;  \
									rt_extra[sect_number].virtual_address = ms_sect_table.virtual_address;\
 								  }

static bool verify_pe_file(FILE* pe_fd)
{
	u8 offset;
	u32 ms_sign;

	/* Read offset */
	read_from_file(pe_fd, MS_SIGN_OFFSET, &offset, sizeof(u8));

	/* Read signature */
	read_from_file(pe_fd, offset, &ms_sign, sizeof(u32));

	if(!memcmp(&ms_sign, MS_SIGN, 4))
		return true;
	else
		return false;
}


int parse_pe_file(FILE* pe_fd, u64* image_entry, u64* bss_size, rt_sect_info* rt_extra)
{
	if(!verify_pe_file(pe_fd))
		return INVALID_PE_FILE;

	/* Read PE header */

	u64 start_of_pe_hdr = ftell(pe_fd);
	pe_hdr hdr;
	read_file_content(pe_fd, &hdr, sizeof(hdr));

	*image_entry = hdr.std_opt_hdr.address_of_entry;
	*bss_size = hdr.std_opt_hdr.size_of_unint_data;

	/* Read section table */
	move_file_ptr(pe_fd, start_of_pe_hdr + sizeof(pe_coff_hdr) + hdr.ms_hdr.size_of_opt_hdr);

	sect_table ms_sect_table;
	u8 valid_section_index = 0;


	for(u8 sect_entry = 0; sect_entry < hdr.ms_hdr.no_of_sections; sect_entry++)
	{
		read_file_content(pe_fd, &ms_sect_table, sizeof(sect_table));

		if(check_for_string(ms_sect_table.name, rt_section_table, RT_SECTION_TABLE_SIZE))
		{
			SET_RT_EXTRA(valid_section_index)
			valid_section_index++;
		}
	
	}

	return NO_ERROR;
}