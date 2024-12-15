/**
 * RZ LAUNCHER APP
 */

#ifndef LAUNCHER_SCREEN_H
#define LAUNCHER_SCREEN_H

#include        "lvgl/lvgl.h"
#include	<json-glib/json-glib.h>

#define DISC_STR_MAX (28)

typedef struct
{
	const gchar *exe_cmd;
	const gchar *icon_image;
	char discription[DISC_STR_MAX];
	lv_obj_t *btn;
}config;

extern const lv_img_dsc_t renesas_logomark;
extern const lv_img_dsc_t list_icon;

extern const lv_font_t FiraCode_Regular_12;
extern const lv_font_t FiraCode_Regular_16;
extern const lv_font_t FiraCode_Regular_20;
extern const lv_font_t FiraCode_Regular_24;
extern const lv_font_t FiraCode_Regular_28;
extern const lv_font_t FiraCode_Regular_32;
extern const lv_font_t FiraCode_Regular_40;


void read_conf(int *btn_cnt, config *btn_conf);

int32_t launcher_screen(int32_t width, int32_t height, int btn_cnt, config *btn_conf);

#endif  /* LAUNCHER_SCREEN_H */
