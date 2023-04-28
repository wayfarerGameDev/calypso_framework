/// <summary>
/// Color module that provies useful colors
/// </summary>

#pragma once

// Includes
#include <stdio.h>
#include <stdint.h>     // uint8_t

// Colors (Hexadecimal)
const int _calypso_framework_math_colors_color_hex_white                                        = 0xffffff;
const int _calypso_framework_math_colors_color_hex_black                                        = 0x000000;
const int _calypso_framework_math_colors_color_hex_red                                          = 0xff0000;
const int _calypso_framework_math_colors_color_hex_green                                        = 0x00ff00;
const int _calypso_framework_math_colors_color_hex_blue                                         = 0x0000ff;
const int _calypso_framework_math_colors_color_hex_yellow                                       = 0xffff00;
const int _calypso_framework_math_colors_color_hex_magenta                                      = 0xff00ff;
const int _calypso_framework_math_colors_color_hex_cyan                                         = 0x00ffff;
const int _calypso_framework_math_colors_color_hex_gray                                         = 0x808080;
const int _calypso_framework_math_colors_color_hex_brown                                        = 0xa52a2a;
const int _calypso_framework_math_colors_color_hex_orange                                       = 0xffa500;
const int _calypso_framework_math_colors_color_hex_pink                                         = 0xffc0cb;
const int _calypso_framework_math_colors_color_hex_purple                                       = 0x800080;
const int _calypso_framework_math_colors_color_hex_lavender                                     = 0xe6e6fa;
const int _calypso_framework_math_colors_color_hex_turquoise                                    = 0x40e0d0;
const int _calypso_framework_math_colors_color_hex_gold                                         = 0xffd700;
const int _calypso_framework_math_colors_color_hex_silver                                       = 0xc0c0c0;
const int _calypso_framework_math_colors_color_hex_navy                                         = 0x000080;
const int _calypso_framework_math_colors_color_hex_maroon                                       = 0x800000;
const int _calypso_framework_math_colors_color_hex_olive                                        = 0x808000;
const int _calypso_framework_math_colors_color_hex_teal                                         = 0x008080;
const int _calypso_framework_math_colors_color_hex_forest_green                                 = 0x228b22;
const int _calypso_framework_math_colors_color_hex_lime_green                                   = 0x00ff00;
const int _calypso_framework_math_colors_color_hex_sky_blue                                     = 0x87ceeb;
const int _calypso_framework_math_colors_color_hex_royal_blue                                   = 0x4169e1;
const int _calypso_framework_math_colors_color_hex_steel_blue                                   = 0x4682b4;
const int _calypso_framework_math_colors_color_hex_slate_gray                                   = 0x708090;
const int _calypso_framework_math_colors_color_hex_dark_gray                                    = 0xa9a9a9;
const int _calypso_framework_math_colors_color_hex_light_gray                                   = 0xd3d3d3;
const int _calypso_framework_math_colors_color_hex_beige                                        = 0xf5f5dc;
const int _calypso_framework_math_colors_color_hex_salmon                                       = 0xfa8072;
const int _calypso_framework_math_colors_color_hex_dark_salmon                                  = 0xe9967a;
const int _calypso_framework_math_colors_color_hex_light_salmon                                 = 0xffa07a;
const int _calypso_framework_math_colors_color_hex_crimson                                      = 0xdc143c;
const int _calypso_framework_math_colors_color_hex_fire_brick                                   = 0xb22222;
const int _calypso_framework_math_colors_color_hex_dark_red                                     = 0x8b0000;
const int _calypso_framework_math_colors_color_hex_hot_pink                                     = 0xff69b4;
const int _calypso_framework_math_colors_color_hex_deep_pink                                    = 0xff1493;
const int _calypso_framework_math_colors_color_hex_medium_violet_red                            = 0xc71585;
const int _calypso_framework_math_colors_color_hex_pale_violet_red                              = 0xdb7093;
const int _calypso_framework_math_colors_color_hex_orchid                                       = 0xda70d6;
const int _calypso_framework_math_colors_color_hex_violet                                       = 0xee82ee;
const int _calypso_framework_math_colors_color_hex_plum                                         = 0xdda0dd;
const int _calypso_framework_math_colors_color_hex_thistle                                      = 0xd8bfd8;
const int _calypso_framework_math_colors_color_hex_lavender_blush                               = 0xfff0f5;
const int _calypso_framework_math_colors_color_hex_papaya_whip                                  = 0xffefd5;
const int _calypso_framework_math_colors_color_hex_sea_shell                                    = 0xfff5ee;
const int _calypso_framework_math_colors_color_hex_cornsilk                                     = 0xfff8dc;
const int _calypso_framework_math_colors_color_hex_lemon_chiffon                                = 0xfffacd;
const int _calypso_framework_math_colors_color_hex_floral_white                                 = 0xfffaf0;
const int _calypso_framework_math_colors_color_hex_snow                                         = 0xfffafa;
const int _calypso_framework_math_colors_color_hex_misty_rose                                   = 0xffe4e1;
const int _calypso_framework_math_colors_color_hex_azure                                        = 0xf0ffff;
const int _calypso_framework_math_colors_color_hex_honeydew                                     = 0xf0fff0;
const int _calypso_framework_math_colors_color_hex_ivory                                        = 0xfffff0;
const int _calypso_framework_math_colors_color_hex_linen                                        = 0xfaf0e6;
const int _calypso_framework_math_colors_color_hex_old_lace                                     = 0xfdf5e6;
const int _calypso_framework_math_colors_color_hex_seashell                                     = 0xfff5ee;
const int _calypso_framework_math_colors_color_hex_antique_white                                = 0xfaebd7;
const int _calypso_framework_math_colors_color_hex_bisque                                       = 0xffe4c4;
const int _calypso_framework_math_colors_color_hex_blanched_almond                              = 0xffebcd;
const int _calypso_framework_math_colors_color_hex_moccasin                                     = 0xffe4b5;
const int _calypso_framework_math_colors_color_hex_navajo_white                                 = 0xffdead;
const int _calypso_framework_math_colors_color_hex_wheat                                        = 0xf5deb3;
const int _calypso_framework_math_colors_color_dark_khaki                                       = 0xbdb76b;
const int _calypso_framework_math_colors_color_hex_burly_wood                                   = 0xdeb887;
const int _calypso_framework_math_colors_color_hex_tan                                          = 0xd2b48c;
const int _calypso_framework_math_colors_color_hex_rosy_brown                                   = 0xbc8f8f;
const int _calypso_framework_math_colors_color_hex_sandy_brown                                  = 0xf4a460;
const int _calypso_framework_math_colors_color_hex_goldenrod                                    = 0xdaa520;
const int _calypso_framework_math_colors_color_hex_dark_goldenrod                               = 0xb8860b;
const int _calypso_framework_math_colors_color_hex_peru                                         = 0xcd853f;
const int _calypso_framework_math_colors_color_hex_chocolate                                    = 0xd2691e;
const int _calypso_framework_math_colors_color_hex_saddle_brown                                 = 0x8b4513;
const int _calypso_framework_math_colors_color_hex_sienna                                       = 0xa0522d;
const int _calypso_framework_math_colors_color_hex_aquamarine                                   = 0x7fffd4;
const int _calypso_framework_math_colors_color_hex_medium_aquamarine                            = 0x66c2a5;
const int _calypso_framework_math_colors_color_hex_paleturquoise                                = 0xafeeee;
const int _calypso_framework_math_colors_color_hex_medium_turquoise                             = 0x48d1cc;
const int _calypso_framework_math_colors_color_hex_dark_turquoise                               = 0x00ced1;
const int _calypso_framework_math_colors_color_hex_light_sea_green                              = 0x20b2aa;
const int _calypso_framework_math_colors_color_hex_cadet_blue                                   = 0x5f9ea0;
const int _calypso_framework_math_colors_color_hex_light_steel_blue                             = 0xb0c4de;
const int _calypso_framework_math_colors_color_hex_powder_blue                                  = 0xb0e0e6;
const int _calypso_framework_math_colors_color_hex_light_blue                                   = 0xadd8e6;
const int _calypso_framework_math_colors_color_hex_deep_sky_blue                                = 0x00bfff;
const int _calypso_framework_math_colors_color_hex_dodger_blue                                  = 0x1e90ff;
const int _calypso_framework_math_colors_color_hex_cornflower_blue                              = 0x6495ed;
const int _calypso_framework_math_colors_color_hex_medium_slate_blue                            = 0x7b68ee;
const int _calypso_framework_math_colors_color_hex_blue_violet                                  = 0x8a2be2;
const int _calypso_framework_math_colors_color_hex_indigo                                       = 0x4b0082;
const int _calypso_framework_math_colors_color_hex_dark_slate_blue                              = 0x483d8b;

// Colors (RGBA)
const uint8_t _calypso_framework_math_colors_color_rgba_white[4]                                = {255, 255, 255, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_black[4]                                = {0, 0, 0, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_red[4]                                  = {255, 0, 0, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_green[4]                                = {0, 255, 0, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_blue[4]                                 = {0, 0, 255, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_yellow[4]                               = {255, 255, 0, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_magenta[4]                              = {255, 0, 255, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_cyan[4]                                 = {0, 255, 255, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_gray[4]                                 = {128, 128, 128, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_brown[4]                                = {165, 42, 42, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_orange[4]                               = {255, 165, 0, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_pink[4]                                 = {255, 192, 203, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_purple[4]                               = {128, 0, 128, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_lavender[4]                             = {230, 230, 250, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_turquoise[4]                            = {64, 224, 208, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_gold[4]                                 = {255, 215, 0, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_silver[4]                               = {192, 192, 192, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_navy[4]                                 = {0, 0, 128, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_maroon[4]                               = {128, 0, 0, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_olive[4]                                = {128, 128, 0, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_teal[4]                                 = {0, 128, 128, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_forest_green[4]                         = {34, 139, 34, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_lime_green[4]                           = {0, 255, 0, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_sky_blue[4]                             = {135, 206, 235, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_royal_blue[4]                           = {65, 105, 225, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_steel_blue[4]                           = {70, 130, 180, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_slate_gray[4]                           = {112, 128, 144, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_dark_gray[4]                            = {169, 169, 169, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_light_gray[4]                           = {211, 211, 211, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_beige[4]                                = {245, 245, 220, 255};
const uint8_t _calypso_framework_math_colors_color_rgba_salmon[4]                               = {250, 128, 114, 255};