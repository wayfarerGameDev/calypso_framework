/// <summary>
/// App module that uses SDL as a base
/// </summary>

#pragma once

// Includes
#include <stdio.h>
#include <stdbool.h>	// bool
#include <stdint.h>     // uint8_t

// Logging Callback
typedef void (*calypso_framework_io_log_callback_t)(const char* log_msg, const uint8_t log_type);
calypso_framework_io_log_callback_t _calypso_framework_io_log_callback;

// File
typedef struct calypso_framework_io_file_t_s
{
    char* data;
    char len;
    bool b_is_valid;
}calypso_framework_io_file_t;


/**
* \brief Set io's log callback
* \return void
*/
void calypso_framework_io_set_log_callback(calypso_framework_io_log_callback_t log_callback)
{
    _calypso_framework_io_log_callback = log_callback;
}

/**
* \brief Do io's log callback
* \return void
*/
void calypso_framework_io_do_log_callback(const char* log_msg, const uint8_t log_type)
{
    if (_calypso_framework_io_log_callback == NULL)
        return;

    _calypso_framework_io_log_callback(log_msg,log_type);
}

// Based On https://stackoverflow.com/a/44894946 (not the chosen answer) by Nominal Animal
/**
* \brief Read file
* \param char* file_path
* \return calypso_framework_io_file_t
*/
calypso_framework_io_file_t calypso_framework_io_file_read(const char* file_path)
{
    // 20 MiB, can probably change this to a higher value without issue.
    // Check your target platform.
    const int io_read_chunk_size = 2097152;

    calypso_framework_io_file_t file = { .b_is_valid = false };

    // Open Our File
	FILE *fp = fopen(file_path, "rb");
	if (!fp || ferror(fp)) 
    {
        calypso_framework_io_do_log_callback("IO: Could not read file (does not exist): ",3);
        calypso_framework_io_do_log_callback(file_path,3);
        calypso_framework_io_do_log_callback("\n",3);
	}

	char *data = NULL;
	char *tmp;
	size_t used = 0;
	size_t size = 0;
	size_t n;

	while (true) 
    {
		if (used + io_read_chunk_size + 1 > size) 
        {
			size = used + io_read_chunk_size + 1;

			if (size <= used) 
            {
				free(data);

                calypso_framework_io_do_log_callback("IO: Could not read file (file too large): ",3);
                calypso_framework_io_do_log_callback(file_path,3);
                calypso_framework_io_do_log_callback("\n",3);
                return file;
			}

			tmp = realloc(data, size);
			if (!tmp) 
            {
				free(data);

				calypso_framework_io_do_log_callback("IO: Could not read file (not enough free memory to read file:): ",3);
                calypso_framework_io_do_log_callback(file_path,3);
                calypso_framework_io_do_log_callback("\n",3);
                return file;
			}
			data = tmp;
		}

		n = fread(data + used, 1, io_read_chunk_size, fp);
		if (n == 0)
			break;

		used += n;
	}

	if (ferror(fp)) 
    {
		free(data);

        calypso_framework_io_do_log_callback("IO: Could not read file (file too large): ",3);
        calypso_framework_io_do_log_callback(file_path,3);
        calypso_framework_io_do_log_callback("\n",3);		
        return file;
	}

	tmp = realloc(data, used + 1);
	if (!tmp) 
    {
		free(data);

		calypso_framework_io_do_log_callback("IO: Could not read file (not enough free memory to read file:): ",3);
        calypso_framework_io_do_log_callback(file_path,3);
        calypso_framework_io_do_log_callback("\n",3);
        return file;
	}

	data = tmp;
	data[used] = 0;

	file.data = data;
	file.len = used;
	file.b_is_valid = true;

	return file;
}

/**
* \brief Read file with and just return char array
* \param char* file_path
* \return char*
*/
char* calypso_framework_io_file_read_char_array(const char* file_path)
{
    calypso_framework_io_file_t file = calypso_framework_io_file_read(file_path);
    return file.data;
}