/**
 * HMI SDK / RZ/G Linux LVGL sample program for image display
 *
 * Copyright (C) 2024, 2025 Renesas Electronics Corp. All rights reserved.
 */

#ifndef	SAMPLE_APP_H
#define	SAMPLE_APP_H

#include	<stdint.h>
#include	<stdbool.h>


#include	"lvgl/lvgl.h"
#include	"lvgl/lv_drivers/lv_drv_conf.h"

#if	USE_FBDEV && USE_EVDEV
  #undef	RUNS_ON_WAYLAND
#elif	USE_WAYLAND
  #define	RUNS_ON_WAYLAND
#else
  #error	LVGL drivers configration error.
#endif

#ifdef	RUNS_ON_WAYLAND
#include	"lvgl/lv_drivers/wayland/wayland.h"

#else
#include	"lvgl/lv_drivers/display/fbdev.h"
#include	"lvgl/lv_drivers/indev/evdev.h"

typedef struct {
	lv_coord_t width;
	lv_coord_t height;
	bool end;
	lv_color_t *buff;
	lv_disp_draw_buf_t draw_buf;
	lv_disp_drv_t drv;
	lv_disp_t *disp;
	lv_indev_drv_t indev_drv;
	lv_indev_t *mouse_indev;
} lsid_dispinf_t;
#endif	/* RUNS_ON_WAYLAND */


/******************************************************************************
 * Declarations and definition for sample applicaiton
 *****************************************************************************/
#define		LSID_MAJOR_VERSION		(1)
#define		LSID_MINOR_VERSION		(2)

#define		LSID_WINDOW_WIDTH		((lv_coord_t)1280)
#define		LSID_WINDOW_HEIGHT		((lv_coord_t)720)

#define		LSID_BG_COLOR			((uint32_t)0xFFFFFF)
#define		LSID_GUIDE_POS_X		((lv_coord_t)24)
#define		LSID_GUIDE_POS_Y		((lv_coord_t)300)
#define		LSID_NUMBER_BTNS		(8)

typedef struct {
	lv_coord_t x, y, w, h;
} lsid_rect_t;

typedef enum {
	LSID_IMG_FORMAT_BMP = 0,
	LSID_IMG_FORMAT_JPG,
	LSID_IMG_FORMAT_PNG,
	LSID_IMG_FORMAT_GIF,

	LSID_IMG_FORMAT_NUM
} lsid_img_format;

typedef struct {
	lsid_img_format format;
	lv_coord_t width, height;
	void *file_path;
} lsid_img_file_t;

typedef struct {
	void *data;
	lsid_img_file_t img_file;
} lsid_img_set_t; 

typedef struct {
	void *disp;
	lv_coord_t width;
	lv_coord_t height;
	int32_t mode;

	lv_obj_t *imgsel_scr;
	lv_obj_t *imgdsp_scr;

	lv_obj_t *img_obj;
	lv_obj_t *quit_btn;
	lv_obj_t *back_btn;
} lsid_sample_app_t;


int32_t lsid_sample_app_setup(int32_t width, int32_t height, void *disp,
								int32_t mode);
void lsid_sample_app_quit(void);


#endif	/* SAMPLE_APP_H */
