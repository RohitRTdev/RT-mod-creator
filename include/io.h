#ifndef _IO_H_
#define _IO_H_

#include <stdio.h>
#include <stdbool.h>
#include "defs.h"

void move_file_ptr(FILE* fd, u64 offset);
size_t read_file_content(FILE* fd, void* buffer, u64 size);
void write_to_file(FILE* fd, u64 offset, void* buffer, u64 size);
void read_from_file(FILE* fd, u64 offset, void* buffer, u64 size);
void close_handles(FILE* file_ptr_array[], size_t number_of_handles);
bool check_for_errors(FILE* file_handles[], size_t number_of_files, char* output_file_name);


#endif