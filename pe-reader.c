#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "pe-defs.h"
#include "io.h"
#include "error.h"
#include "rt-defs.h"

#define SET_RT_EXTRA(sect_number) {																		  \
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


void parse_pe_file(FILE* pe_fd, u64* image_entry, rt_sect_info* rt_extra)
{
	if(!verify_pe_file(pe_fd))
		display_error_message("Invalid PE file!", INVALID_PE_FILE);

	/* Read PE header */

	u64 start_of_pe_hdr = ftell(pe_fd);
	pe_hdr hdr;
	read_file_content(pe_fd, &hdr, sizeof(hdr));

	*image_entry = hdr.std_opt_hdr.address_of_entry;
	
	/* Read section table */
	move_file_ptr(pe_fd, start_of_pe_hdr + sizeof(pe_coff_hdr) + hdr.ms_hdr.size_of_opt_hdr);

	sect_table ms_sect_table;

	for(u8 sect_entry = 0; sect_entry < hdr.ms_hdr.no_of_sections; sect_entry++)
	{
		read_file_content(pe_fd, &ms_sect_table, sizeof(sect_table));

		if(!strcmp(ms_sect_table.name, ".text"))
		{
			SET_RT_EXTRA(0);
		}
		else if(!strcmp(ms_sect_table.name, ".data"))
		{
			SET_RT_EXTRA(1);	
		}
		else if(!strcmp(ms_sect_table.name, ".bss"))
		{
			SET_RT_EXTRA(2);
		}
		else if(!strcmp(ms_sect_table.name, ".reloc"))
		{
			SET_RT_EXTRA(3);
		}
	}
}