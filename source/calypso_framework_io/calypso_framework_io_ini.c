/// <summary>
/// Ini file parser
/// </summary>

#pragma once

// Includes
#include <stdlib.h>                                             // malloc
#include <string.h>                                             // strcspn
#include <stdio.h>                                              // File

// Defines
#define CALYPSO_FRAMEWORK_IO_INI_MAX_LINE_LENGTH                1024

/*------------------------------------------------------------------------------
Calypso Framework IO(ini) : Parse
------------------------------------------------------------------------------*/

// int calypso_framework_io_ini_get_value_int(const char* data_buffer, const char* section_name, const char* key_name, int* value_ptr)
// {
//     // No String
//     if (data_buffer == NULL)
//         return 0;
// 
//     // Read Data Buffer Line By Line
//     {
//         // Data
//         char* line = NULL;
//         char line_copy[CALYPSO_FRAMEWORK_IO_INI_MAX_LINE_LENGTH];
//         char line_section[100];
//         int in_section = 0;
// 
//         // Go TO First Line
//         line = strtok(data_buffer, "\n");
// 
//         // read lines
//         while (line != NULL) 
//         {
//             // Copy Line
//             strncpy(line_copy, line, CALYPSO_FRAMEWORK_IO_INI_MAX_LINE_LENGTH -1);
// 
//             // Line Is A Section | Check Ff Section Is Wanted Section
//             if (sscanf(line, "[%99[^]]]", line_section) == 1) 
//                 in_section = strcmp(line_section, section_name) == 0 ? 1 : 0;
// 
//             else if (in_section == 1)
//             {
//                 // Print Line               
//                 printf("%s\n", line_copy);
//             }
// 
//             // Go To Next Line
//             line = strtok(NULL, "\n");
//         }   
//     }
// 
//     return 1;
// }