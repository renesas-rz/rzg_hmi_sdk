/**
 * HMI SDK / RZ/G Linux sample program for video playback
 *
 * Copyright (C) 2024 Renesas Electronics Corp. All rights reserved.
 */

#ifndef	SAMPLE_APP_H
#define	SAMPLE_APP_H

#include	<stdint.h>
#include	<stdbool.h>


#include	"lvgl/lvgl.h"
#include	"lvgl/lv_drivers/wayland/wayland.h"

/******************************************************************************
 * Declarations and definition for sample applicaiton
 *****************************************************************************/
#define		LSVP_MAJOR_VERSION		(1)
#define		LSVP_MINOR_VERSION		(1)

#define		LSVP_WINDOW_WIDTH		((lv_coord_t)320)
#define		LSVP_WINDOW_HEIGHT		((lv_coord_t)240)

#define		LSVP_BG_COLOR			((uint32_t)0xFFFFFF)

typedef struct {
	lv_coord_t x, y;
} lsvp_pos_t;

typedef struct {
	lv_coord_t x, y, w, h;
} lsvp_rect_t;

typedef enum {
	LSVP_CTRL_PLAY_BTN = 0,
	LSVP_CTRL_STOP_BTN,
	LSVP_CTRL_PAUSE_BTN,
	LSVP_CTRL_BTN_NUM
} lsvp_ctrl_btn_t;

typedef enum {
	LSVP_STATUS_STOP = 0,
	LSVP_STATUS_PLAY,
	LSVP_STATUS_PAUSE,
	LSVP_STATUS_NUM
} lsvp_status_t;

typedef struct {
	lv_disp_t *disp;
	lv_coord_t width;
	lv_coord_t height;

	char *input;
	int32_t audio;

	lv_obj_t *screen;
	lv_obj_t *playback_ctrl[LSVP_CTRL_BTN_NUM];
	lv_style_t disabled_style;

	lsvp_status_t status;
	int32_t quit_flag;
} lsvp_sample_app_t;

int32_t lsvp_sample_app_setup(int32_t width, int32_t height, lv_disp_t *disp,
						char *input, int32_t audio);
void lsvp_sample_app_quit(void);
void lsvp_complete_playing(void);
void lsvp_quit_with_error(void);


#endif	/* SAMPLE_APP_H */
