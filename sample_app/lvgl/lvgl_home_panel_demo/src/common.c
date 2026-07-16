#include  "include/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SMARC_RZG2L     "smarc-rzg2l"
#define SMARC_RZG2LC    "smarc-rzg2lc"
#define SMARC_RZG2UL    "smarc-rzg2ul"
#define SMARC_RZG3E     "smarc-rzg3e"

int background_width = 1920;
int background_height = 1080;


MachineName get_machine_name(void) {
    char hostname[64];
    MachineName ret = MACHINE_NAME_RZG2L;

    if (0 != gethostname(hostname, sizeof(hostname))) {
        perror("error gethostname");
	return ret;
    }

    if (strcmp(hostname, SMARC_RZG2L) == 0) {
        return MACHINE_NAME_RZG2L;
    }
    else if (strcmp(hostname, SMARC_RZG2LC) == 0) {
        return MACHINE_NAME_RZG2LC;
    }
    else if (strcmp(hostname, SMARC_RZG2UL) == 0) {
        return MACHINE_NAME_RZG2UL;
    }
    else if (strcmp(hostname, SMARC_RZG3E) == 0) {
        return MACHINE_NAME_RZG3E;
    }
    else {
        return MACHINE_NAME_RZG2L;
    }
}

ResolutionType get_resolution_type(void)
{
    if (MACHINE_NAME_RZG2UL == get_machine_name())
        return RESOLUTION_TYPE_HD;
    else
        return RESOLUTION_TYPE_FHD;
}

int adjust_to_res(int val)
{
    if (RESOLUTION_TYPE_HD == get_resolution_type())
        return (int)(val * 0.67);
    else
        return val;
}

const lv_font_t *get_lv_font(FontSize size)
{
    if (RESOLUTION_TYPE_FHD == get_resolution_type())
    {
        switch (size) {
            case FONT_SIZE_L:
            case FONT_SIZE_M:
            case FONT_SIZE_S:
            case FONT_SIZE_XS:
            default:
	        return &lv_font_montserrat_14;
        }
    }
    else
    {
        switch (size) {
            case FONT_SIZE_L:   return &lv_font_montserrat_14;
            case FONT_SIZE_M:   return &lv_font_montserrat_12;
            case FONT_SIZE_S:   return &lv_font_montserrat_10;
            case FONT_SIZE_XS:  return &lv_font_montserrat_8;
            default:            return &lv_font_montserrat_12;
        }
    }
}

void set_background_width(int width)
{
    background_width = width;
}

int get_background_width(void)
{
    return background_width;
}

void set_background_height(int height)
{
    background_height = height;
}

int get_background_height(void)
{
    return background_height;
}

int32_t img_ratio_calc(lv_obj_t* img,int32_t scr_width, int32_t scr_height)
{
    int32_t ratio;
    int32_t img_width;
    int32_t img_height;
    int32_t img_obj_width = lv_obj_get_width(img);
    int32_t img_obj_height = lv_obj_get_height(img);

    if(img_obj_width > img_obj_height)
    {
        ratio = 256.0 * (double)scr_width/(double)img_obj_width;
    }
    else
    {
        ratio = 256.0 * (double)scr_height/(double)img_obj_height;
    }
    return ratio;
}


void add_header(lv_obj_t *obj)
{
    lv_obj_t* header_background;
    lv_obj_t* header_logo;
    header_background = lv_obj_create(obj);
    lv_obj_set_size(header_background, get_background_width(), adjust_to_res(79));
    lv_obj_set_style_bg_color(header_background, lv_color_hex(0xE3E1FF), 0);
    lv_obj_remove_flag(header_background, LV_OBJ_FLAG_SCROLLABLE);

    header_logo = lv_image_create(header_background);
    lv_image_set_src(header_logo, "L:/usr/share/lvgl-home-panel-demo/images/renesas_logomark_blue.png");
    lv_obj_update_layout(header_logo);
    lv_image_set_scale(header_logo, img_ratio_calc(header_logo, adjust_to_res(237), adjust_to_res(30)));
    lv_obj_center(header_logo);
}

lv_obj_t* create_page_background(lv_obj_t *obj)
{
    lv_obj_t *background_obj = lv_obj_create(obj);
    lv_obj_set_size(background_obj, get_background_width(), get_background_height());
    lv_obj_align(background_obj, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_style_pad_all(background_obj, 0, 0);
    lv_obj_set_style_border_width(background_obj, 0, 0);
    lv_obj_set_style_outline_width(background_obj, 0, 0);
    return background_obj;
}
