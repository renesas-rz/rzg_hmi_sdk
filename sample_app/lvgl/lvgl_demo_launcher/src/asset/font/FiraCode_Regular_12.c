/*******************************************************************************
 * Size: 15 px
 * Bpp: 1
 * Opts: --bpp 1 --size 15 --no-compress --font FiraCode-Regular.ttf --range 32-127 --format lvgl -o FiraCode_Regular_12.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef FIRACODE_REGULAR_12
#define FIRACODE_REGULAR_12 1
#endif

#if FIRACODE_REGULAR_12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x55, 0x54, 0xf0,

    /* U+0022 "\"" */
    0x99, 0x99,

    /* U+0023 "#" */
    0x24, 0x4b, 0xf9, 0x26, 0x48, 0xbf, 0xa4, 0x48,
    0x90,

    /* U+0024 "$" */
    0x10, 0x20, 0xe7, 0xb9, 0x12, 0x1c, 0x1e, 0x16,
    0x24, 0x4c, 0xb7, 0xc2, 0x4, 0x0,

    /* U+0025 "%" */
    0x1, 0x31, 0xa4, 0x92, 0x86, 0xc0, 0x40, 0x5c,
    0x51, 0x28, 0xa4, 0x61, 0xc0,

    /* U+0026 "&" */
    0x3c, 0x44, 0x40, 0x60, 0x1f, 0x62, 0x82, 0x82,
    0xc2, 0x7c,

    /* U+0027 "'" */
    0xf0,

    /* U+0028 "(" */
    0x1, 0x24, 0x48, 0x88, 0x88, 0x84, 0x42, 0x10,

    /* U+0029 ")" */
    0x8, 0x42, 0x21, 0x11, 0x11, 0x12, 0x24, 0x80,

    /* U+002A "*" */
    0x10, 0x23, 0x5b, 0xe3, 0x85, 0x11, 0x0,

    /* U+002B "+" */
    0x10, 0x20, 0x47, 0xf1, 0x2, 0x4, 0x0,

    /* U+002C "," */
    0xfe, 0x80,

    /* U+002D "-" */
    0xfc,

    /* U+002E "." */
    0xfc,

    /* U+002F "/" */
    0x2, 0x4, 0x10, 0x20, 0x81, 0x4, 0x8, 0x20,
    0x41, 0x2, 0x8, 0x0, 0x0,

    /* U+0030 "0" */
    0x38, 0x9a, 0x3c, 0xd9, 0xb6, 0x68, 0xf1, 0x64,
    0x70,

    /* U+0031 "1" */
    0x33, 0xc9, 0x4, 0x10, 0x41, 0x4, 0x13, 0xf0,

    /* U+0032 "2" */
    0x7a, 0x30, 0x41, 0xc, 0x21, 0x8, 0x43, 0xf0,

    /* U+0033 "3" */
    0x7a, 0x10, 0x41, 0x38, 0x30, 0x41, 0x8d, 0xe0,

    /* U+0034 "4" */
    0x18, 0x20, 0xc1, 0x6, 0x48, 0xb1, 0x7f, 0x4,
    0x8,

    /* U+0035 "5" */
    0x7e, 0x81, 0x3, 0xe0, 0x60, 0x40, 0x81, 0x44,
    0xf0,

    /* U+0036 "6" */
    0x3c, 0x82, 0x5, 0xec, 0x70, 0x60, 0xc1, 0x44,
    0x70,

    /* U+0037 "7" */
    0xfc, 0x10, 0x82, 0x10, 0x43, 0x8, 0x61, 0x0,

    /* U+0038 "8" */
    0x3c, 0x85, 0xa, 0x13, 0xc9, 0xa0, 0xc1, 0xc6,
    0xf8,

    /* U+0039 "9" */
    0x38, 0x8a, 0xc, 0x18, 0x38, 0xde, 0x82, 0x4,
    0x31, 0x80,

    /* U+003A ":" */
    0xfc, 0x0, 0x3f,

    /* U+003B ";" */
    0xfc, 0x1, 0xff, 0xd0,

    /* U+003C "<" */
    0x4, 0x18, 0xc7, 0x8, 0xc, 0xe, 0x6, 0x0,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0x40, 0xc0, 0x60, 0x70, 0x21, 0x8c, 0x30, 0x0,

    /* U+003F "?" */
    0x7b, 0x10, 0x42, 0x10, 0x82, 0x0, 0x30, 0xc0,

    /* U+0040 "@" */
    0x7c, 0xc2, 0x2, 0x1, 0x79, 0xc9, 0x89, 0x89,
    0x89, 0x89, 0x79, 0x6,

    /* U+0041 "A" */
    0xc, 0xa, 0x5, 0x2, 0xc2, 0x21, 0x10, 0xfc,
    0x82, 0x41, 0x60, 0xc0,

    /* U+0042 "B" */
    0xf9, 0xa, 0x14, 0x2f, 0x90, 0xe0, 0xc1, 0x87,
    0xf0,

    /* U+0043 "C" */
    0x3e, 0x87, 0x4, 0x8, 0x10, 0x20, 0x60, 0x42,
    0x7c,

    /* U+0044 "D" */
    0xf9, 0xa, 0xc, 0x18, 0x30, 0x60, 0xc3, 0x8d,
    0xf0,

    /* U+0045 "E" */
    0xfe, 0x8, 0x20, 0xfa, 0x8, 0x20, 0x83, 0xf0,

    /* U+0046 "F" */
    0xfe, 0x8, 0x20, 0xfa, 0x8, 0x20, 0x82, 0x0,

    /* U+0047 "G" */
    0x3c, 0x83, 0x4, 0x8, 0xf0, 0x60, 0xc1, 0x42,
    0x78,

    /* U+0048 "H" */
    0x83, 0x6, 0xc, 0x1f, 0xf0, 0x60, 0xc1, 0x83,
    0x4,

    /* U+0049 "I" */
    0xfc, 0x41, 0x4, 0x10, 0x41, 0x4, 0x13, 0xf0,

    /* U+004A "J" */
    0x3c, 0x10, 0x41, 0x4, 0x10, 0x41, 0x8f, 0xe0,

    /* U+004B "K" */
    0x85, 0x12, 0x65, 0x8e, 0x14, 0x24, 0x4c, 0x8d,
    0xc,

    /* U+004C "L" */
    0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0x83, 0xf0,

    /* U+004D "M" */
    0xc3, 0xe7, 0xe7, 0xa5, 0xa5, 0xbd, 0x99, 0x99,
    0x81, 0x81,

    /* U+004E "N" */
    0xc3, 0x86, 0x8d, 0x19, 0x32, 0x66, 0xc5, 0x8f,
    0xc,

    /* U+004F "O" */
    0x3c, 0x42, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
    0x42, 0x3c,

    /* U+0050 "P" */
    0xf9, 0xe, 0xc, 0x18, 0x7f, 0x20, 0x40, 0x81,
    0x0,

    /* U+0051 "Q" */
    0x3c, 0x21, 0x20, 0x50, 0x28, 0x14, 0xa, 0x5,
    0x2, 0x42, 0x1e, 0x0, 0xc0, 0x20,

    /* U+0052 "R" */
    0xf9, 0x1a, 0x14, 0x28, 0xdf, 0x24, 0x4c, 0x8d,
    0x8,

    /* U+0053 "S" */
    0x7d, 0x82, 0x6, 0x7, 0x81, 0x80, 0x81, 0x86,
    0xf8,

    /* U+0054 "T" */
    0xff, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8,
    0x8, 0x8,

    /* U+0055 "U" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0xc6,
    0xf0,

    /* U+0056 "V" */
    0x41, 0xa0, 0x98, 0x44, 0x62, 0x21, 0x90, 0x58,
    0x28, 0x1c, 0x6, 0x0,

    /* U+0057 "W" */
    0x80, 0xe6, 0x73, 0x2a, 0xb5, 0x52, 0xa9, 0x54,
    0xaa, 0x73, 0x31, 0x80,

    /* U+0058 "X" */
    0x61, 0x11, 0xd, 0x82, 0x80, 0x80, 0xe0, 0x58,
    0x44, 0x63, 0x20, 0x80,

    /* U+0059 "Y" */
    0x41, 0x31, 0x88, 0x86, 0xc1, 0x40, 0x40, 0x20,
    0x10, 0x8, 0x4, 0x0,

    /* U+005A "Z" */
    0x7e, 0xc, 0x10, 0x41, 0x82, 0x8, 0x30, 0x41,
    0xfc,

    /* U+005B "[" */
    0xf8, 0x88, 0x88, 0x88, 0x88, 0x88, 0x8f,

    /* U+005C "\\" */
    0x81, 0x81, 0x3, 0x2, 0x6, 0x4, 0xc, 0x8,
    0x18, 0x10, 0x30, 0x20, 0x0,

    /* U+005D "]" */
    0xf1, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1f,

    /* U+005E "^" */
    0x10, 0x70, 0xa2, 0x2c, 0x60,

    /* U+005F "_" */
    0xff,

    /* U+0060 "`" */
    0x9c, 0x80,

    /* U+0061 "a" */
    0xf8, 0x8, 0x13, 0xec, 0x50, 0xa3, 0x3b,

    /* U+0062 "b" */
    0x82, 0x8, 0x2e, 0xce, 0x18, 0x61, 0x86, 0x2f,
    0x80,

    /* U+0063 "c" */
    0x3d, 0x18, 0x20, 0x82, 0x4, 0x4f,

    /* U+0064 "d" */
    0x4, 0x10, 0x5f, 0x46, 0x18, 0x61, 0x87, 0x37,
    0x40,

    /* U+0065 "e" */
    0x3c, 0x8e, 0xf, 0xf8, 0x10, 0x10, 0x1e,

    /* U+0066 "f" */
    0x1e, 0x40, 0x81, 0xf, 0xc4, 0x8, 0x10, 0x20,
    0x40, 0x80,

    /* U+0067 "g" */
    0x2, 0xfe, 0x14, 0x28, 0x4f, 0x20, 0x60, 0x7c,
    0x6, 0xb, 0xe0,

    /* U+0068 "h" */
    0x82, 0x8, 0x2e, 0xc6, 0x18, 0x61, 0x86, 0x18,
    0x40,

    /* U+0069 "i" */
    0x30, 0xc0, 0x3c, 0x10, 0x41, 0x4, 0x10, 0x4f,
    0xc0,

    /* U+006A "j" */
    0x18, 0xc1, 0xf0, 0x84, 0x21, 0x8, 0x42, 0x33,
    0x60,

    /* U+006B "k" */
    0x81, 0x2, 0x4, 0x69, 0x96, 0x38, 0x58, 0x99,
    0x12, 0x10,

    /* U+006C "l" */
    0xe0, 0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0x81,
    0xc0,

    /* U+006D "m" */
    0xff, 0x26, 0x4c, 0x99, 0x32, 0x64, 0xc9,

    /* U+006E "n" */
    0xbb, 0x18, 0x61, 0x86, 0x18, 0x61,

    /* U+006F "o" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x51, 0x1c,

    /* U+0070 "p" */
    0xbb, 0x38, 0x61, 0x86, 0x18, 0xbe, 0x82, 0x8,
    0x0,

    /* U+0071 "q" */
    0x7d, 0x18, 0x61, 0x86, 0x1c, 0xdd, 0x4, 0x10,
    0x40,

    /* U+0072 "r" */
    0xdd, 0x94, 0x50, 0x41, 0x4, 0x3c,

    /* U+0073 "s" */
    0x7a, 0x18, 0x1c, 0xc, 0x18, 0x7e,

    /* U+0074 "t" */
    0x20, 0x43, 0xf1, 0x2, 0x4, 0x8, 0x10, 0x20,
    0x3c,

    /* U+0075 "u" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0xdd,

    /* U+0076 "v" */
    0x83, 0x8d, 0x13, 0x22, 0xc5, 0xe, 0xc,

    /* U+0077 "w" */
    0xc0, 0xa6, 0xd3, 0x6a, 0xa5, 0x52, 0xa9, 0x5c,
    0x66,

    /* U+0078 "x" */
    0x46, 0xc8, 0xa0, 0xc3, 0x85, 0x91, 0x63,

    /* U+0079 "y" */
    0xc3, 0x8d, 0x12, 0x22, 0xc5, 0xa, 0xc, 0x10,
    0x61, 0x80,

    /* U+007A "z" */
    0x7e, 0xc, 0x30, 0xc1, 0x4, 0x18, 0x7f,

    /* U+007B "{" */
    0x19, 0x8, 0x42, 0x13, 0x4, 0x31, 0x8, 0x42,
    0xc,

    /* U+007C "|" */
    0xff, 0xfc,

    /* U+007D "}" */
    0xc1, 0x8, 0x42, 0x10, 0x64, 0x61, 0x8, 0x42,
    0x60,

    /* U+007E "~" */
    0x62, 0x92, 0x8c
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 148, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 148, .box_w = 2, .box_h = 10, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 148, .box_w = 4, .box_h = 4, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 6, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 148, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 29, .adv_w = 148, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 42, .adv_w = 148, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 148, .box_w = 1, .box_h = 4, .ofs_x = 4, .ofs_y = 7},
    {.bitmap_index = 53, .adv_w = 148, .box_w = 4, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 61, .adv_w = 148, .box_w = 4, .box_h = 15, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 69, .adv_w = 148, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 76, .adv_w = 148, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 83, .adv_w = 148, .box_w = 2, .box_h = 5, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 85, .adv_w = 148, .box_w = 6, .box_h = 1, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 86, .adv_w = 148, .box_w = 3, .box_h = 2, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 87, .adv_w = 148, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 100, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 148, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 148, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 148, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 148, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 148, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 187, .adv_w = 148, .box_w = 3, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 190, .adv_w = 148, .box_w = 3, .box_h = 10, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 194, .adv_w = 148, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 148, .box_w = 6, .box_h = 4, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 205, .adv_w = 148, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 148, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 148, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 233, .adv_w = 148, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 254, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 148, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 148, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 148, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 148, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 322, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 148, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 148, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 148, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 377, .adv_w = 148, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 391, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 148, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 419, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 428, .adv_w = 148, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 440, .adv_w = 148, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 148, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 464, .adv_w = 148, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 476, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 148, .box_w = 4, .box_h = 14, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 492, .adv_w = 148, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 505, .adv_w = 148, .box_w = 4, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 512, .adv_w = 148, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 517, .adv_w = 148, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 518, .adv_w = 148, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 9},
    {.bitmap_index = 520, .adv_w = 148, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 527, .adv_w = 148, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 148, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 148, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 551, .adv_w = 148, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 558, .adv_w = 148, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 148, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 579, .adv_w = 148, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 588, .adv_w = 148, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 597, .adv_w = 148, .box_w = 5, .box_h = 14, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 606, .adv_w = 148, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 616, .adv_w = 148, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 625, .adv_w = 148, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 632, .adv_w = 148, .box_w = 6, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 638, .adv_w = 148, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 645, .adv_w = 148, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 654, .adv_w = 148, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 663, .adv_w = 148, .box_w = 6, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 669, .adv_w = 148, .box_w = 6, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 675, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 684, .adv_w = 148, .box_w = 6, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 690, .adv_w = 148, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 697, .adv_w = 148, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 706, .adv_w = 148, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 713, .adv_w = 148, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 723, .adv_w = 148, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 730, .adv_w = 148, .box_w = 5, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 739, .adv_w = 148, .box_w = 1, .box_h = 14, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 741, .adv_w = 148, .box_w = 5, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 750, .adv_w = 148, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t FiraCode_Regular_12 = {
#else
lv_font_t FiraCode_Regular_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if FIRACODE_REGULAR_12*/

