/**
 * RZ DEMO APP
 */
#ifndef COMMON_H
#define COMMON_H
#include "lvgl/lvgl.h"
#include <stdio.h>
#include <string.h>

typedef enum {
    MACHINE_NAME_RZG2L,
    MACHINE_NAME_RZG2LC,
    MACHINE_NAME_RZG2UL,
    MACHINE_NAME_RZG3E
} MachineName;

typedef enum {
    RESOLUTION_TYPE_FHD,
    RESOLUTION_TYPE_HD
} ResolutionType;

typedef enum {
    FONT_SIZE_L,
    FONT_SIZE_M,
    FONT_SIZE_S,
    FONT_SIZE_XS
} FontSize;

ResolutionType get_resolution_type(void);
MachineName get_machine_name(void);

int adjust_to_res(int val);

const lv_font_t *get_lv_font(FontSize size);

void set_background_width(int width);
int get_background_width(void);
void set_background_height(int height);
int get_background_height(void);

int32_t img_ratio_calc(lv_obj_t* img,int32_t scr_width, int32_t scr_height);

void add_header(lv_obj_t *obj);
lv_obj_t* create_page_background(lv_obj_t *obj);

#endif  /* HOME_PANEL_DEMO_H */
