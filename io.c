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

void close_handles(FILE* file_ptr_array[], size_t number_of_handles)
{
	for(size_t i = 0; i < number_of_handles; i++)
	{
		fclose(file_ptr_array[i]);
	}
}

static bool check_for_open_errors(FILE* file_handles[], size_t number_of_files)
{
    for(size_t i = 0; i < number_of_files; i++)
    {
        if(file_handles[i] == NULL)
        {
            return true;
        }
    }
    return false;
}

bool check_for_errors(FILE* file_handles[], size_t number_of_files, char* output_file_name)
{
    if(check_for_open_errors(file_handles, number_of_files))
    {
		fclose(file_handles[1]);
        remove(output_file_name);
        return true;
    }

    return false;
}