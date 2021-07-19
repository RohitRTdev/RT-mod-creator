#ifndef _PE_DEFS_H_
#define _PE_DEFS_H_

#include "defs.h"

#define MS_SIGN "PE\0"
#define MS_SIGN_OFFSET 0x3c
#pragma pack(1)

typedef struct{
	u32 virtual_address;
	u32 size;
}image_data_dir;

typedef struct{
	u16 machine;
	u16 no_of_sections;
	u32 time_date_stamp;
	u32 ptr_to_symbol_table;
	u32 no_of_symbols;
	u16 size_of_opt_hdr;
	u16 characteristics;
}pe_coff_hdr;

typedef struct{
	u16 magic;
	u8 major_linker_version;
	u8 minor_linker_version;
	u32 size_of_code;
	u32 size_of_int_data;
	u32 size_of_unint_data;
	u32 address_of_entry;
	u32 base_of_code;
}pe_opt_hdr;

typedef struct{
	pe_coff_hdr ms_hdr;
	pe_opt_hdr std_opt_hdr;
	u64 image_base;
	u32 section_alignment;
	u32 file_alignment;
	u16 major_os_version;
	u16 minot_os_version;
	u16 major_img_version;
	u16 minor_image_version;
	u16 major_sub_version;
	u16 minor_sub_version;
	u32 win32_value;
	u32 size_of_image;
	u32 size_of_hdr;
	u32 check_sum;
	u16 subsystem;
	u16 dll_chars;
	u64 size_of_stack_res;
	u64 size_of_stack_commit;
	u64 size_of_heap_res;
	u64 size_of_heap_commit;
	u32 loader_flags;
	u32 number_of_rva;
	image_data_dir data_dir[];
}pe_hdr;

typedef struct{
	char name[8];
	u32 virtual_size;
	u32 virtual_address;
	u32 size_of_raw_data;
	u32 ptr_to_raw_data;
	u32 ptr_to_reloc;
	u32 ptr_to_ln;
	u16 number_of_reloc;
	u16 number_of_lines;
	u32 characteristics;
}sect_table;


#pragma pack()

#endif