/// <summary>
/// Color module that provies useful colors
/// </summary>

#pragma once

// Includes
#include <stdio.h>
#include <stdint.h>     // uint8_t

// Color Struct
typedef struct {
    uint8_t r,g,b,a;
} CalypsoFrameworkColorsColorRGBA;

// Color Arrays (Main)
const uint8_t _c_calypso_framework_colors_color_byte_array_black[4]              = {0,0,0,255};
const uint8_t _c_calypso_framework_colors_color_byte_array_white[4]              = {255,255,255,255};
const uint8_t _c_calypso_framework_colors_color_byte_array_silver[4]             = {192,192,192};
const uint8_t _c_calypso_framework_colors_color_byte_array_gray[4]               = {128,128,128};
const uint8_t _c_calypso_framework_colors_color_byte_array_red[4]                = {255,0,0,255};
const uint8_t _c_calypso_framework_colors_color_byte_array_blue[4]               = {0,0,255,255};
const uint8_t _c_calypso_framework_colors_color_byte_array_green[4]              = {0,128,0,255};
const uint8_t _c_calypso_framework_colors_color_byte_array_yellow[4]             = {255,255,0,255};
const uint8_t _c_calypso_framework_colors_color_byte_array_purple[4]             = {128,0,128,255};
const uint8_t _c_calypso_framework_colors_color_byte_array_orange[4]             = {255,165,0,255};
const uint8_t _c_calypso_framework_colors_color_byte_array_pink[4]               = {255,192,203};

// Color Arrays (Other)
const uint8_t _c_calypso_framework_colors_color_byte_array_aqua[4]               = {0,255,255,255};
const uint8_t _c_calypso_framework_colors_color_byte_array_cornflower_blue[4]    = {100,149,237,255};
const uint8_t _c_calypso_framework_colors_color_byte_array_magenta[4]            = {255,0,255,255};
const uint8_t _c_calypso_framework_colors_color_byte_array_lime[4]               = {0,255,0,255};
const uint8_t _c_calypso_framework_colors_color_byte_array_teal[4]               = {0,128,128,255};
const uint8_t _c_calypso_framework_colors_color_byte_array_navy[4]               = {0,0,128,255};
const uint8_t _c_calypso_framework_colors_color_byte_array_olive[4]              = {128,128,255};
const uint8_t _c_calypso_framework_colors_color_byte_array_turquoise[4]          = {64,224,208,255};

// Colors (Struct Color RGBA)
CalypsoFrameworkColorsColorRGBA calypso_framework_colors_build_color_rgba_from_color_array(uint8_t color_array[4])
{
    CalypsoFrameworkColorsColorRGBA color = {.r = color_array[0], .g = color_array[1], .b = color_array[2], .a = color_array[3]};
    return color;
}