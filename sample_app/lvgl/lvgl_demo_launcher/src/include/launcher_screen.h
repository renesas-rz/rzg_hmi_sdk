/**
 * RZ LAUNCHER APP
 */

#ifndef LAUNCHER_SCREEN_H
#define LAUNCHER_SCREEN_H

#include        "lvgl/lvgl.h"
#include	<json-glib/json-glib.h>
#include	"read_conf.h"

#if	LV_USE_LINUX_FBDEV && LV_USE_EVDEV
  #undef	RUNS_ON_WAYLAND
#elif	LV_USE_WAYLAND
  #define	RUNS_ON_WAYLAND
#else
  #error	LVGL drivers configration error.
#endif

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

extern const lv_img_dsc_t renesas_logomark;
extern const lv_img_dsc_t list_icon;

extern const lv_font_t FiraCode_Regular_12;
extern const lv_font_t FiraCode_Regular_16;
extern const lv_font_t FiraCode_Regular_20;
extern const lv_font_t FiraCode_Regular_24;
extern const lv_font_t FiraCode_Regular_28;
extern const lv_font_t FiraCode_Regular_32;
extern const lv_font_t FiraCode_Regular_40;

void launcher_screen(int32_t width, int32_t height, ui_framework_info_st *ui_framework_info);
lv_obj_t* create_select_ui_framework_screen(int32_t width, int32_t height, ui_framework_info_st *ui_framework_info);

#endif  /* LAUNCHER_SCREEN_H */
