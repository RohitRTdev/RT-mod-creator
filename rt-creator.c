#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "rt-defs.h"
#include "pe-defs.h"
#include "io.h"

static bool check_null_section(rt_sect_info* section)
{
	static rt_sect_info null_structure = {0};
	if(!memcmp(&section->ptr_to_sect, &null_structure, sizeof(null_structure) - 8))
		return true;
	else
		return false;
}


static void zero_hdr(FILE* out_fd, u64 size_of_hdr)
{
	char* zero_bytes = malloc(size_of_hdr);
	
	/* zero initialise the buffer */
	for(u64 byte = 0; byte < size_of_hdr; byte++)
	{
		zero_bytes[byte] = 0;
	}

	fwrite(zero_bytes, 1, size_of_hdr, out_fd);

	free(zero_bytes);
}

static void adjust_reloc_section(FILE* out_fd, rt_sect_info* rt_reloc_section, u64 pe_image_base)
{
	if(!check_null_section(rt_reloc_section))
	{
		u32 new_page_rva;
		read_from_file(out_fd, rt_reloc_section->ptr_to_sect, &new_page_rva, sizeof(u32));
	
		new_page_rva -= pe_image_base;
		write_to_file(out_fd, rt_reloc_section->ptr_to_sect, &new_page_rva, sizeof(u32));
	}
	
}

static void copy_section(rt_sect_info* rt_sect, FILE* pe_fd, FILE* out_fd)
{
	char* file_bytes = malloc(rt_sect->size_of_sect);

	move_file_ptr(pe_fd, rt_sect->ptr_to_sect);
	fread(file_bytes, 1, rt_sect->size_of_sect, pe_fd);

	fwrite(file_bytes, 1, rt_sect->size_of_sect, out_fd);

	free(file_bytes);
}

/* Having a section with 0 for all fields indicates that the section is not present */

void create_rt_executable(FILE* out_fd, FILE* pe_fd, rt_sect_info* rt_extra, u64 image_entry, u64 bss_size)
{
	/* Fill rt_hdr structure */

	rt_hdr hdr = {0};

	u64 pe_image_base = rt_extra[0].virtual_address;;
	hdr.image_entry = image_entry - pe_image_base;
	zero_hdr(out_fd, sizeof(rt_hdr));

	u8 reloc_index = 0;

	/* Copy all the relevant sections */
	for(u8 arr_index = 0; arr_index < TOTAL_SECTIONS; arr_index++)
	{
		if(check_null_section(&rt_extra[arr_index]))
		{
			continue;
		}

		if(!strcmp(rt_extra[arr_index].sect_name, ".reloc"))
		{
			reloc_index = arr_index;
		}
		strcpy(hdr.rt_sections[arr_index].sect_name, rt_extra[arr_index].sect_name);
		if(strcmp(rt_extra[arr_index].sect_name, ".bss"))
		{
			hdr.rt_sections[arr_index].ptr_to_sect = ftell(out_fd);
			hdr.rt_sections[arr_index].size_of_sect = rt_extra[arr_index].size_of_sect;
			hdr.rt_sections[arr_index].virtual_address = rt_extra[arr_index].virtual_address - pe_image_base;

			copy_section(&rt_extra[arr_index], pe_fd, out_fd);
		}
		else
		{
			hdr.rt_sections[arr_index].ptr_to_sect = 0;
			hdr.rt_sections[arr_index].size_of_sect = 0;
			hdr.rt_sections[arr_index].virtual_address = rt_extra[arr_index].virtual_address - pe_image_base;
		}

		hdr.image_size += ALIGN(hdr.rt_sections[arr_index].size_of_sect, DEFAULT_SECTION_ALIGNMENT);
			
	}

	hdr.image_size += ALIGN(bss_size , DEFAULT_SECTION_ALIGNMENT);

	adjust_reloc_section(out_fd, &hdr.rt_sections[reloc_index], pe_image_base);
	memcpy(hdr.rt_sign, RT_SIGN, SIZE_OF_RT_SIGN);

	write_to_file(out_fd, 0, &hdr, sizeof(rt_hdr));
	
}