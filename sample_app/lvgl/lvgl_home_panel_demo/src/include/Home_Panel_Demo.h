/**
 * RZ LAUNCHER APP
 */
#include <stdio.h>
#include "lvgl/lvgl.h"
#include	"lvgl/lv_drivers/lv_drv_conf.h"
#ifndef HOME_PANEL_DEMO_H
#define HOME_PANEL_DEMO_H

#if	USE_FBDEV && USE_EVDEV
  #undef	RUNS_ON_WAYLAND
#elif	USE_WAYLAND
  #define	RUNS_ON_WAYLAND
#else
  #error	LVGL drivers configration error.
#endif

#ifdef	RUNS_ON_WAYLAND
    #include <gst/gst.h>
    extern bool music_state;
    extern void cb_print_position(void);
    extern GstElement* pipeline;
    extern lv_obj_t* music_state_btn_icon;
    extern lv_obj_t* time_text;
    LV_IMG_DECLARE(music_btn_play_icon);
#endif

//Menu
extern int background_width;
extern int background_height;
extern lv_obj_t* header_background;
extern lv_obj_t* header_logo;
extern uint16_t logo_ratio;
extern lv_obj_t* Dashboard;
extern lv_obj_t* Image_Gallery;
extern lv_obj_t* Image_Gallery_cont;
extern lv_obj_t* Home_Automation;
extern lv_obj_t* Home_Automation_cont;
extern lv_obj_t* Weather_History;
extern lv_obj_t* Weather_History_cont;
extern uint16_t img_ratio_calc(lv_obj_t* img,uint16_t scr_width, uint16_t scr_height);

//Chart
extern lv_chart_series_t* ser;
extern uint32_t pcnt;

//Dashboard
extern void create_menu(void);
extern void create_Dashboard(void);
extern void create_Image_Gallery(void);
extern void create_Home_Automation(void);
extern void create_Weather_History(void);

#endif  /* HOME_PANEL_DEMO_H */
