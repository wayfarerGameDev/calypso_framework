/// <summary>
/// IO module that reads and writes files
/// </summary>

#pragma once

// Includes
#include <stdlib.h>     // free, realloc
#include <stdio.h>      // File


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
        #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
        CALYPSO_FRAMEWORK_LOG_MESSAGE("io_file","Could not read file (does not exist)",3);
        #endif
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
                #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
                CALYPSO_FRAMEWORK_LOG_MESSAGE("io_file","Could not read file (file to large):",3);
                #endif
                return data;
			}

			tmp = realloc(data, size);
			if (!tmp) 
            {
				free(data);
                #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
                CALYPSO_FRAMEWORK_LOG_MESSAGE("io_file","Could not read file (not enough free memory to read file)",3);
                #endif
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
        #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
        CALYPSO_FRAMEWORK_LOG_MESSAGE("io_file","Could not read file (file to large)",3);
        #endif	
        return 0;
	}

	tmp = realloc(data, used + 1);
	if (!tmp) 
    {
		free(data);
        #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
        CALYPSO_FRAMEWORK_LOG_MESSAGE("io_file","Could not read file (not enough free memory to read file",3);
        #endif
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
        #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
        CALYPSO_FRAMEWORK_LOG_MESSAGE("io_file","Could not read file (does not exist)",3);
        #endif
	}

    // Write FIle
	size_t chunks_written = fwrite(data_buffer, size, 1, file_ptr);
    if (chunks_written != 1)
    {
        #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
        CALYPSO_FRAMEWORK_LOG_MESSAGE("io_file","Write error",3);
        #endif
	}
    
    // Close File
	fclose(file_ptr);

	return 0;
}