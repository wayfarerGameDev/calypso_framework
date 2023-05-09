/// <summary>
/// IO module that reads and writes files
/// </summary>

#pragma once

// Includes
#include <stdlib.h>     // free, realloc
#include <stdio.h>      // File

// Logging Callback
typedef void (*calypso_framework_io_log_callback_t)(const char* log_msg, const unsigned char log_type);
calypso_framework_io_log_callback_t _calypso_framework_io_log_callback;

/*------------------------------------------------------------------------------
Calypso Framework IO(File) : Log
------------------------------------------------------------------------------*/

void calypso_framework_io_file_set_log_callback(calypso_framework_io_log_callback_t log_callback)
{
    _calypso_framework_io_log_callback = log_callback;
}

void calypso_framework_io_file_do_log_callback(const char* log_msg, const unsigned char log_type)
{
    if (_calypso_framework_io_log_callback == NULL)
        return;

    _calypso_framework_io_log_callback(log_msg,log_type);
}

/*------------------------------------------------------------------------------
Calypso Framework IO(File) : Read
------------------------------------------------------------------------------*/

// Based On https://stackoverflow.com/a/44894946 (not the chosen answer) by Nominal Animal
char* calypso_framework_io_file_read(const char* file_path)
{
    // 20 MiB, can probably change this to a higher value without issue.
    // Check your target platform.
    const int io_read_chunk_size = 2097152;

    // Open Our File
	FILE *file_ptr = fopen(file_path, "rb");
	if (!file_ptr || ferror(file_ptr)) 
    {
        calypso_framework_io_file_do_log_callback("IO: Could not read file (does not exist): ",3);
        calypso_framework_io_file_do_log_callback(file_path,3);
        calypso_framework_io_file_do_log_callback("\n",3);
        return ((void*)0);;
	}

	char *data = ((void*)0);
	char *tmp;
	size_t used = 0;
	size_t size = 0;
	size_t n;

	while (1) 
    {
		if (used + io_read_chunk_size + 1 > size) 
        {
			size = used + io_read_chunk_size + 1;

			if (size <= used) 
            {
				free(data);

                calypso_framework_io_file_do_log_callback("IO_File: Could not read file (file too large): ",3);
                calypso_framework_io_file_do_log_callback(file_path,3);
                calypso_framework_io_file_do_log_callback("\n",3);
                return data;
			}

			tmp = realloc(data, size);
			if (!tmp) 
            {
				free(data);

				calypso_framework_io_file_do_log_callback("IO_File: Could not read file (not enough free memory to read file:): ",3);
                calypso_framework_io_file_do_log_callback(file_path,3);
                calypso_framework_io_file_do_log_callback("\n",3);
                return 0;
			}
			data = tmp;
		}

		n = fread(data + used, 1, io_read_chunk_size, file_ptr);
		if (n == 0)
			break;

		used += n;
	}

	if (ferror(file_ptr)) 
    {
		free(data);
        calypso_framework_io_file_do_log_callback("IO_File: Could not read file (file too large): ",3);
        calypso_framework_io_file_do_log_callback(file_path,3);
        calypso_framework_io_file_do_log_callback("\n",3);		
        return 0;
	}

	tmp = realloc(data, used + 1);
	if (!tmp) 
    {
		free(data);
		calypso_framework_io_file_do_log_callback("IO_Flie: Could not read file (not enough free memory to read file:): ",3);
        calypso_framework_io_file_do_log_callback(file_path,3);
        calypso_framework_io_file_do_log_callback("\n",3);
        return 0;
	}

	data = tmp;
	data[used] = 0;
	return data;
}

/*------------------------------------------------------------------------------
Calypso Framework IO(File) : Write
------------------------------------------------------------------------------*/

int io_file_write(const char* file_path, void *data_buffer, size_t size) 
{   
	// Open Our File
	FILE *file_ptr = fopen(file_path, "wb");
	if (!file_ptr || ferror(file_ptr)) 
    {
        calypso_framework_io_file_do_log_callback("IO_File: Could not read file (does not exist): ",3);
        calypso_framework_io_file_do_log_callback(file_path,3);
        calypso_framework_io_file_do_log_callback("\n",3);
	}

    // Write FIle
	size_t chunks_written = fwrite(data_buffer, size, 1, file_ptr);
    if (chunks_written != 1)
     {
        calypso_framework_io_file_do_log_callback("IO_File: Write error: ",3);
        calypso_framework_io_file_do_log_callback(file_path,3);
        calypso_framework_io_file_do_log_callback("\n",3);
	}
    
    // Close File
	fclose(file_ptr);

	return 0;
}