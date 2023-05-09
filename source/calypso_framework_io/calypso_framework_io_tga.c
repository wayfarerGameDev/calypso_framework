#pragma once

#include <stdlib.h>     // malloc, free

unsigned char* calypso_framework_io_tga_read_data(const char* data_buffer, int* width_ptr, int* height_ptr)
{
    // Read TGA Header (18 bytes)
    const unsigned char* ptr = data_buffer;             // TGA wants unisgned bytes
    ptr += 2;                                           // Skip image id
    *width_ptr = *(int*)(ptr + 13);                     // Width is bytes 13-16
    *height_ptr = *(int*)(ptr + 14);                    // Width is bytes 15-18
    const int pixel_depth = *(ptr + 16);                // Pixel depth is bytes 17
    ptr += 18;                                          // Skip Descriptor and Color Map

    printf("Width: %d\n", *width_ptr);

    //// Get Pixel Count
    //int pixel_count = *width_ptr * *height_ptr;
    //int pixel_bytes = pixel_depth / 8;                  // Bytes per pixel (RGBA = 32bits, RGB = 24 bits)
//
    //// Create And Allocate Pixel BUffer
    //unsigned char* pixel_buffer = (unsigned char*)malloc(pixel_count * sizeof(unsigned char) * 4);
//
    //// Read Pixel Data (32-bit RGB Format)
    //for (int i = 0; i < pixel_count; i++) 
    //{
    //    // RGB
    //    pixel_buffer[i * 4 + 2] = *ptr++;
    //    pixel_buffer[i * 4 + 1] = *ptr++;
    //    pixel_buffer[i * 4 + 0] = *ptr++;
//
    //    // A
    //    if (pixel_bytes == 4)
    //        pixel_buffer[i * 4 + 3] = *ptr++;  // Alpha channel
    //    else
    //        pixel_buffer[i * 4 + 3] = 255;     // Alpha channel set to 255
    //}
//
    //return pixel_buffer;
}