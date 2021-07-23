#ifndef _RT_DEFS_H_
#define _RT_DEFS_H_

#include "defs.h"

#define RT_SIGN "_RTMOD_"

#pragma pack(1)

typedef struct{
	char sect_name[8];
	u64 ptr_to_sect;
	u64 size_of_sect;
	u64 virtual_address;
}rt_sect_info;

typedef struct{
	char rt_sign[8];
	u64 image_size;
	u64 image_entry;
	rt_sect_info rt_sections[4];
}rt_hdr;

#define SIZE_OF_RT_SIGN 8
#define TOTAL_SECTIONS 4

#pragma pack()

#endif