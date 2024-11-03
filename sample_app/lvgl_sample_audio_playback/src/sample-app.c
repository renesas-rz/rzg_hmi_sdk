/**
 * HMI SDK / RZ/G Linux sample program for audio playback
 *
 * Copyright (C) 2024 Renesas Electronics Corp. All rights reserved.
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<pthread.h>

#include	"lvgl/lvgl.h"
#include	"lvgl/lv_drivers/wayland/wayland.h"

#include	"sample-app.h"
#include	"sample-player.h"


/* Image data for GUI */
LV_IMG_DECLARE(LSAP_btn_pause);
LV_IMG_DECLARE(LSAP_btn_play);
LV_IMG_DECLARE(LSAP_btn_stop);
LV_IMG_DECLARE(LSAP_text1);
LV_IMG_DECLARE(LSAP_text2);
LV_IMG_DECLARE(LSAP_text3);

/* Sample program object */
static lsap_sample_app_t *app_obj = NULL;
static pthread_mutex_t mutex_app_data = PTHREAD_MUTEX_INITIALIZER;

/** Allocate memory and fill with zero
 *
 */
static void *allocate_memory(size_t size)
{
	void *mem;

	mem = malloc(size);
	if (mem == NULL) {
		fprintf(stderr, "ERROR!! malloc() failed.\n");
		return NULL;
	}
	memset(mem, 0, size);

	return mem;
}

/** Quit applicaiton program due to an error in playback
 *
 */
void lsap_quit_with_error(void)
{
	lsap_sample_app_t *app = app_obj;

	app->quit_flag = 1;

	lv_wayland_close_window(app->disp);
}

/** Change state of buttons
 *
 */
static void change_button_state(lsap_sample_app_t *app)
{
	int i;
	lv_obj_t **btn;

	switch (app->status) {
	case LSAP_STATUS_STOP:
		for (i = 0; i < LSAP_MENU_NUM; i++) {
			btn = app->playback_ctrl[i];
			lv_obj_clear_state(btn[LSAP_CTRL_PLAY_BTN], LV_STATE_DISABLED);
			lv_obj_add_state(btn[LSAP_CTRL_STOP_BTN], LV_STATE_DISABLED);
			lv_obj_add_state(btn[LSAP_CTRL_PAUSE_BTN], LV_STATE_DISABLED);
		}
		break;
	case LSAP_STATUS_PLAY:
		for (i = 0; i < LSAP_MENU_NUM; i++) {
			btn = app->playback_ctrl[i];
			lv_obj_add_state(btn[LSAP_CTRL_PLAY_BTN], LV_STATE_DISABLED);
		}
		btn = app->playback_ctrl[app->enabled_menu];
		lv_obj_clear_state(btn[LSAP_CTRL_STOP_BTN], LV_STATE_DISABLED);
		lv_obj_clear_state(btn[LSAP_CTRL_PAUSE_BTN], LV_STATE_DISABLED);
		break;
	case LSAP_STATUS_PAUSE:
		btn = app->playback_ctrl[app->enabled_menu];
		lv_obj_clear_state(btn[LSAP_CTRL_PLAY_BTN], LV_STATE_DISABLED);
		lv_obj_add_state(btn[LSAP_CTRL_PAUSE_BTN], LV_STATE_DISABLED);
		break;
	default:
		break;
	}
}

/** Complete playing audio
 *
 * Complete palyeng audio at the end of stream
 *
 */
void lsap_complete_playing(void)
{
	lsap_sample_app_t *app = app_obj;

	lv_obj_set_style_bg_color(app->menu[app->enabled_menu],
				lv_color_hex(LSAP_MENU_DISABLED_COLOR), 0);

	pthread_mutex_lock(&mutex_app_data);
	app->enabled_menu = LSAP_MENU_NUM;	/* Set invalid value */
	app->status = LSAP_STATUS_STOP;
	change_button_state(app);
	pthread_mutex_unlock(&mutex_app_data);
}

/** Check target button
 *
 */
static int32_t check_target_btn(lsap_sample_app_t *app, lv_obj_t *target,
				lsap_menu_t *menu, lsap_ctrl_btn_t *btn)
{
	int i, j;
	int done = 0;

	for (i = 0; i < LSAP_MENU_NUM; i++) {
		for (j = 0; j < LSAP_CTRL_BTN_NUM; j++) {
			if (target == app->playback_ctrl[i][j]) {
				*menu = (lsap_menu_t)i;
				*btn = (lsap_ctrl_btn_t)j;
				done = 1;
				break;
			} 
		}
		if (done)
			break;
	}
	return (done) ? 0: -1;
}

/** Play audio
 *
 */
static void play_audio(lsap_sample_app_t *app, lsap_menu_t type)
{
	const char *path = NULL;
	lsap_format_t format;
	int32_t ret;

	switch (type) {
	case LSAP_MENU_MP3:
		path = app->audio_file[LSAP_MENU_MP3];
		format = LSAP_FORMAT_MP3;
		break;
	case LSAP_MENU_WAV:
		path = app->audio_file[LSAP_MENU_WAV];
		format = LSAP_FORMAT_WAV;
		break;
	case LSAP_MENU_AAC:
		path = app->audio_file[LSAP_MENU_AAC];
		format = LSAP_FORMAT_AAC;
		break;
	default:
		return;
	}
	ret = lsap_play_new_file(path, format);
	if (ret)	/* When playing the file fails, do nothing */
		return;

	lv_obj_set_style_bg_color(app->menu[type],
				lv_color_hex(LSAP_MENU_ENABLED_COLOR), 0);

	app->enabled_menu = type;
	app->status = LSAP_STATUS_PLAY;
	change_button_state(app);
}

/** Stop audio
 *
 */
static void stop_audio(lsap_sample_app_t *app, lsap_menu_t type)
{
	int32_t ret;

	ret = lsap_stop_playback();
	if (ret)
		return;

	lv_obj_set_style_bg_color(app->menu[type],
				lv_color_hex(LSAP_MENU_DISABLED_COLOR), 0);

	app->enabled_menu = LSAP_MENU_NUM;	/* Set invalid value */
	app->status = LSAP_STATUS_STOP;
	change_button_state(app);
}

/** Pause audio
 *
 */
static void pause_audio(lsap_sample_app_t *app, lsap_menu_t type)
{
	int32_t ret;

	ret = lsap_pause_playback();
	if (ret)
		return;

	app->status = LSAP_STATUS_PAUSE;
	change_button_state(app);
}

/** Restart audio
 *
 */
static void restart_audio(lsap_sample_app_t *app, lsap_menu_t type)
{
	int32_t ret;

	ret = lsap_restart_playback();
	if (ret)
		return;

	app->status = LSAP_STATUS_PLAY;
	change_button_state(app);
}

/** Playback control button callback
 *
 * This function is called when a playback control button is clicked.
 *
 */
static void button_clicked_cb(lv_event_t *e)
{
	lv_obj_t *target = lv_event_get_target(e);
	lsap_sample_app_t *app;
	lsap_menu_t menu;
	lsap_ctrl_btn_t ctrl_btn;
	int32_t ret;

	app = (lsap_sample_app_t *)lv_event_get_user_data(e);

	ret = check_target_btn(app, target, &menu, &ctrl_btn);
	if (ret) {
		fprintf(stderr, "ERROR!! clicked button was not identified.\n");
		return;
	}

	pthread_mutex_lock(&mutex_app_data);

	switch (app->status) {
	case LSAP_STATUS_STOP:
		if (ctrl_btn == LSAP_CTRL_PLAY_BTN) {
			play_audio(app, menu);
		}
		break;
	case LSAP_STATUS_PLAY:
		if (menu != app->enabled_menu)
			break;

		if (ctrl_btn == LSAP_CTRL_STOP_BTN) {
			stop_audio(app, menu);
		}
		else if (ctrl_btn == LSAP_CTRL_PAUSE_BTN) {
			pause_audio(app, menu);
		}
		break;
	case LSAP_STATUS_PAUSE:
		if (menu != app->enabled_menu)
			break;

		if (ctrl_btn == LSAP_CTRL_PLAY_BTN) {
			restart_audio(app, menu);
		}
		else if (ctrl_btn == LSAP_CTRL_STOP_BTN) {
			stop_audio(app, menu);
		}
		break;
	default:
		break;
	}
	pthread_mutex_unlock(&mutex_app_data);

}

/** Create buttons for playback control
 *
 */
static int32_t create_buttons(lsap_sample_app_t *app, lv_obj_t *obj,
							lsap_menu_t menu)
{
	lv_obj_t *imgbtn;
	lv_style_t *style_ptr = &app->disabled_style;

	/* Play button */
	imgbtn = lv_imgbtn_create(obj);
	if (imgbtn == NULL) {
		fprintf(stderr, "ERROR!! lv_imgbtn_create() failed.\n");
		return -1;
	}
        app->playback_ctrl[menu][LSAP_CTRL_PLAY_BTN] = imgbtn;

	lv_imgbtn_set_src(imgbtn, LV_IMGBTN_STATE_RELEASED, NULL, &LSAP_btn_play, NULL);
	lv_obj_set_size(imgbtn, 80, 80);
	lv_obj_align(imgbtn, LV_ALIGN_TOP_LEFT, 260, 0);
	lv_obj_add_event_cb(imgbtn, button_clicked_cb, LV_EVENT_CLICKED, app);
	lv_obj_add_style(imgbtn, style_ptr, LV_PART_MAIN | LV_STATE_DISABLED);

	/* Stop button */
	imgbtn = lv_imgbtn_create(obj);
	if (imgbtn == NULL) {
		fprintf(stderr, "ERROR!! lv_imgbtn_create() failed.\n");
		return -1;
	}
        app->playback_ctrl[menu][LSAP_CTRL_STOP_BTN] = imgbtn;

	lv_imgbtn_set_src(imgbtn, LV_IMGBTN_STATE_RELEASED, NULL, &LSAP_btn_stop, NULL);
	lv_obj_set_size(imgbtn, 80, 80);
	lv_obj_align(imgbtn, LV_ALIGN_TOP_LEFT, 350, 0);
	lv_obj_add_event_cb(imgbtn, button_clicked_cb, LV_EVENT_CLICKED, app);
	lv_obj_add_style(imgbtn, style_ptr, LV_PART_MAIN | LV_STATE_DISABLED);

	/* Pause button */
	imgbtn = lv_imgbtn_create(obj);
	if (imgbtn == NULL) {
		fprintf(stderr, "ERROR!! lv_imgbtn_create() failed.\n");
		return -1;
	}
        app->playback_ctrl[menu][LSAP_CTRL_PAUSE_BTN] = imgbtn;

	lv_imgbtn_set_src(imgbtn, LV_IMGBTN_STATE_RELEASED, NULL, &LSAP_btn_pause, NULL);
	lv_obj_set_size(imgbtn, 80, 80);
	lv_obj_align(imgbtn, LV_ALIGN_TOP_LEFT, 440, 0);
	lv_obj_add_event_cb(imgbtn, button_clicked_cb, LV_EVENT_CLICKED, app);
	lv_obj_add_style(imgbtn, style_ptr, LV_PART_MAIN | LV_STATE_DISABLED);

	return 0;
}

/** Create playback menu
 *
 */
static int32_t create_playback_menu(lsap_sample_app_t *app, lv_obj_t *screen)
{
	lv_obj_t *menu;
	lv_obj_t *txtimg;
	lv_style_t *style_ptr = &app->disabled_style;
	const lsap_rect_t menu_rect[LSAP_MENU_NUM] = {
		{40,  40, 560, 120},
		{40, 180, 560, 120},
		{40, 320, 560, 120}
	};
	const lsap_pos_t text_pos[LSAP_MENU_NUM] = {
		{42, 86}, {42, 226}, {42, 366}
	};
	const void *img_src[LSAP_MENU_NUM] = {
		&LSAP_text1, &LSAP_text2, &LSAP_text3
	};
	int i;
	int32_t ret;

	/* Set up a style for disabled buttons */
	lv_style_init(style_ptr);
	lv_style_set_img_recolor_opa(style_ptr, LV_OPA_50);
	lv_style_set_img_recolor(style_ptr, lv_color_white());

	for (i = 0; i < LSAP_MENU_NUM; i++) {
		menu = lv_obj_create(screen);
		if (menu == NULL) {
			fprintf(stderr, "ERROR!! lv_obj_create() failed.\n");
			return -1;
		}
		txtimg = lv_img_create(screen);
		if (txtimg == NULL) {
			fprintf(stderr, "ERROR!! lv_img_create() failed.\n");
			return -1;
		}
		lv_obj_align(menu, LV_ALIGN_TOP_LEFT,
				menu_rect[i].x, menu_rect[i].y);
		lv_obj_set_size(menu, menu_rect[i].w, menu_rect[i].h);
		lv_obj_set_style_bg_color(menu,
				lv_color_hex(LSAP_MENU_DISABLED_COLOR), 0);

		lv_img_set_src(txtimg, img_src[i]);
		lv_obj_align(txtimg, LV_ALIGN_TOP_LEFT,
				text_pos[i].x, text_pos[i].y);

		app->menu[i] = menu;

		/* Create buttons */
		ret = create_buttons(app, menu, (lsap_menu_t)i);
		if (ret)
			return -1;
	}
	return 0;
}

/** Create audio filel play back screen
 *
 */
static int32_t create_audio_file_playback_screen(lsap_sample_app_t *app)
{
	lv_obj_t *screen;
	lv_obj_t *img;
	int32_t ret;

	screen = lv_scr_act();
	lv_obj_set_style_bg_color(screen, lv_color_hex(LSAP_BG_COLOR), 0);

	/* Create playback menu */
	ret = create_playback_menu(app, screen);
	if (ret)
		return -1;

	app->screen = screen;
	app->enabled_menu = LSAP_MENU_NUM;
	app->status = LSAP_STATUS_STOP;
	change_button_state(app);

	return ret;
}

/** Create sample app objects
 *
 * Basic objects for each screen are created, and data structures are allocated.
 */
int32_t lsap_sample_app_setup(int32_t width, int32_t height, lv_disp_t *disp,
							const char **audio)
{
	int32_t ret;

	app_obj = allocate_memory(sizeof (lsap_sample_app_t));
	if (app_obj == NULL) {
		return -1;
	}

	app_obj->width = (lv_coord_t)width;
	app_obj->height = (lv_coord_t)height;
	app_obj->disp = disp;
	app_obj->audio_file = audio;

	/* create audio file playback screen */
	ret = create_audio_file_playback_screen(app_obj);
	if (ret)
		return ret;

	return 0;
}

/** Quit sample app
 *
 * All objects and data structures are released.
 */
void lsap_sample_app_quit(void)
{
	lsap_sample_app_t *app = app_obj;

	if (!app)
		return;

	if (!app->quit_flag)	/* Quit player */
		lsap_quit_playback();

	lv_obj_del(app->screen);

	/* Release memory for GUI screen */
	free(app);
}

