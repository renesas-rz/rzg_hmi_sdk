/**
 * HMI SDK / RZ/G Linux sample program for audio playback
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
#define		LSAP_MAJOR_VERSION		(1)
#define		LSAP_MINOR_VERSION		(1)

#define		LSAP_WINDOW_WIDTH		((lv_coord_t)640)
#define		LSAP_WINDOW_HEIGHT		((lv_coord_t)480)

#define		LSAP_BG_COLOR			((uint32_t)0xFFFFFF)
#define		LSAP_MENU_ENABLED_COLOR		((uint32_t)0xFFC4C4)
#define		LSAP_MENU_DISABLED_COLOR	((uint32_t)0xD8E2EF)


typedef struct {
	lv_coord_t x, y;
} lsap_pos_t;

typedef struct {
	lv_coord_t x, y, w, h;
} lsap_rect_t;

typedef enum {
	LSAP_MENU_MP3 = 0,
	LSAP_MENU_WAV,
	LSAP_MENU_AAC,
	LSAP_MENU_NUM
} lsap_menu_t;

typedef enum {
	LSAP_CTRL_PLAY_BTN = 0,
	LSAP_CTRL_STOP_BTN,
	LSAP_CTRL_PAUSE_BTN,
	LSAP_CTRL_BTN_NUM
} lsap_ctrl_btn_t;

typedef enum {
	LSAP_STATUS_STOP = 0,
	LSAP_STATUS_PLAY,
	LSAP_STATUS_PAUSE,
	LSAP_STATUS_NUM
} lsap_status_t;

typedef struct {
	lv_disp_t *disp;
	lv_coord_t width;
	lv_coord_t height;
	const char **audio_file;

	lv_obj_t *screen;
	lv_obj_t *menu[LSAP_MENU_NUM];
        lv_obj_t *playback_ctrl[LSAP_MENU_NUM][LSAP_CTRL_BTN_NUM];
	lv_style_t disabled_style;

	lsap_menu_t enabled_menu;
	lsap_status_t status;
	int32_t quit_flag;
} lsap_sample_app_t;

int32_t lsap_sample_app_setup(int32_t width, int32_t height, lv_disp_t *disp,
							const char **audio);
void lsap_sample_app_quit(void);
void lsap_complete_playing(void);
void lsap_quit_with_error(void);


#endif	/* SAMPLE_APP_H */
