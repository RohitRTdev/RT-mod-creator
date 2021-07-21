#ifndef _DEFS_H_
#define _DEFS_H_

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned int u32;
typedef unsigned long long int u64;


#define MAX_FILE_NAME_SIZE 50
#define DEFAULT_SECTION_ALIGNMENT 4096
#define ALIGN(value, boundary) ((value + boundary - 1) & ~(boundary - 1))
#define STRING_CHECK(index, string1, string2) (!strcmp(argv[index], #string1) || !strcmp(argv[index], #string2))

#endif