#include "io.h"

void move_file_ptr(FILE* fd, u64 offset)
{
	fseek(fd, offset, SEEK_SET);
}

size_t read_file_content(FILE* fd, void* buffer, u64 size)
{
	return fread(buffer, 1, size, fd);
}

void write_to_file(FILE* fd, u64 offset, void* buffer, u64 size)
{
	move_file_ptr(fd, offset);

	fwrite(buffer, 1, size, fd);
}

void read_from_file(FILE* fd, u64 offset, void* buffer, u64 size)
{
	move_file_ptr(fd, offset);
	read_file_content(fd, buffer, size);
}