/**
 * HMI SDK / RZ/G Linux sample program for video playback
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
LV_IMG_DECLARE(LSVP_btn_pause);
LV_IMG_DECLARE(LSVP_btn_play);
LV_IMG_DECLARE(LSVP_btn_stop);
LV_IMG_DECLARE(LSVP_text);

/* Sample program object */
static lsvp_sample_app_t *app_obj = NULL;
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
void lsvp_quit_with_error(void)
{
	lsvp_sample_app_t *app = app_obj;

	app->quit_flag = 1;

	lv_wayland_close_window(app->disp);
}

/** Change state of buttons
 *
 */
static void change_button_state(lsvp_sample_app_t *app)
{
	switch (app->status) {
	case LSVP_STATUS_STOP:
		lv_obj_clear_state(app->playback_ctrl[LSVP_CTRL_PLAY_BTN], LV_STATE_DISABLED);
		lv_obj_add_state(app->playback_ctrl[LSVP_CTRL_STOP_BTN], LV_STATE_DISABLED);
		lv_obj_add_state(app->playback_ctrl[LSVP_CTRL_PAUSE_BTN], LV_STATE_DISABLED);
		break;
	case LSVP_STATUS_PLAY:
		lv_obj_add_state(app->playback_ctrl[LSVP_CTRL_PLAY_BTN], LV_STATE_DISABLED);
		lv_obj_clear_state(app->playback_ctrl[LSVP_CTRL_STOP_BTN], LV_STATE_DISABLED);
		lv_obj_clear_state(app->playback_ctrl[LSVP_CTRL_PAUSE_BTN], LV_STATE_DISABLED);
		break;
	case LSVP_STATUS_PAUSE:
		lv_obj_clear_state(app->playback_ctrl[LSVP_CTRL_PLAY_BTN], LV_STATE_DISABLED);
		lv_obj_clear_state(app->playback_ctrl[LSVP_CTRL_STOP_BTN], LV_STATE_DISABLED);
		lv_obj_add_state(app->playback_ctrl[LSVP_CTRL_PAUSE_BTN], LV_STATE_DISABLED);
		break;
	default:
		break;
	}
}

/** Complete playing video
 *
 * Complete palyeng video at the end of stream
 *
 */
void lsvp_complete_playing(void)
{
	lsvp_sample_app_t *app = app_obj;

	pthread_mutex_lock(&mutex_app_data);
	app->status = LSVP_STATUS_STOP;
	change_button_state(app);
	pthread_mutex_unlock(&mutex_app_data);
}

/** Play video
 *
 */
static void play_video(lsvp_sample_app_t *app)
{
	int32_t ret;

	ret = lsvp_play_new_file(app->input);
	if (ret)
		return;

	app->status = LSVP_STATUS_PLAY;
	change_button_state(app);
}

/** Stop video
 *
 */
static void stop_video(lsvp_sample_app_t *app)
{
	int32_t ret;

	ret = lsvp_stop_playback();
	if (ret)
		return;

	app->status = LSVP_STATUS_STOP;
	change_button_state(app);
}

/** Pause video
 *
 */
static void pause_video(lsvp_sample_app_t *app)
{
	int32_t ret;

	ret = lsvp_pause_playback();
	if (ret)
		return;

	app->status = LSVP_STATUS_PAUSE;
	change_button_state(app);
}

/** Restart video
 *
 */
static void restart_video(lsvp_sample_app_t *app)
{
	int32_t ret;

	ret = lsvp_restart_playback();
	if (ret)
		return;

	app->status = LSVP_STATUS_PLAY;
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
	lsvp_sample_app_t *app;
	lsvp_ctrl_btn_t ctrl_btn;
	int32_t ret;

	app = (lsvp_sample_app_t *)lv_event_get_user_data(e);
	if (target == app->playback_ctrl[LSVP_CTRL_PLAY_BTN])
		ctrl_btn = LSVP_CTRL_PLAY_BTN;
	else if (target == app->playback_ctrl[LSVP_CTRL_STOP_BTN])
		ctrl_btn = LSVP_CTRL_STOP_BTN;
	else
		ctrl_btn = LSVP_CTRL_PAUSE_BTN;

	switch (app->status) {
	case LSVP_STATUS_STOP:
		if (ctrl_btn == LSVP_CTRL_PLAY_BTN) {
			play_video(app);
		}
		break;
	case LSVP_STATUS_PLAY:
		if (ctrl_btn == LSVP_CTRL_STOP_BTN) {
			stop_video(app);
		}
		else if (ctrl_btn == LSVP_CTRL_PAUSE_BTN) {
			pause_video(app);
		}
		break;
	case LSVP_STATUS_PAUSE:
		if (ctrl_btn == LSVP_CTRL_PLAY_BTN) {
			restart_video(app);
		}
		else if (ctrl_btn == LSVP_CTRL_STOP_BTN) {
			stop_video(app);
		}
		break;
	default:
		break;
	}
}

/** Create buttons for playback control
 *
 */
static int32_t create_buttons(lsvp_sample_app_t *app, lv_obj_t *obj)
{
	lv_obj_t *imgbtn;
	lv_style_t *style_ptr = &app->disabled_style;

	/* Set up a style for disabled buttons */
	lv_style_init(style_ptr);
	lv_style_set_img_recolor_opa(style_ptr, LV_OPA_50);
	lv_style_set_img_recolor(style_ptr, lv_color_white());

	/* Play button */
	imgbtn = lv_imgbtn_create(obj);
	if (imgbtn == NULL) {
		fprintf(stderr, "ERROR!! lv_imgbtn_create() failed.\n");
		return -1;
	}
	app->playback_ctrl[LSVP_CTRL_PLAY_BTN] = imgbtn;

	lv_imgbtn_set_src(imgbtn, LV_IMGBTN_STATE_RELEASED, NULL, &LSVP_btn_play, NULL);
	lv_obj_set_size(imgbtn, 80, 80);
	lv_obj_align(imgbtn, LV_ALIGN_TOP_LEFT, 24, 136);
	lv_obj_add_event_cb(imgbtn, button_clicked_cb, LV_EVENT_CLICKED, app);
	lv_obj_add_style(imgbtn, style_ptr, LV_PART_MAIN | LV_STATE_DISABLED);

	/* Stop button */
	imgbtn = lv_imgbtn_create(obj);
	if (imgbtn == NULL) {
		fprintf(stderr, "ERROR!! lv_imgbtn_create() failed.\n");
		return -1;
	}
	app->playback_ctrl[LSVP_CTRL_STOP_BTN] = imgbtn;

	lv_imgbtn_set_src(imgbtn, LV_IMGBTN_STATE_RELEASED, NULL, &LSVP_btn_stop, NULL);
	lv_obj_set_size(imgbtn, 80, 80);
	lv_obj_align(imgbtn, LV_ALIGN_TOP_LEFT, 120, 136);
	lv_obj_add_event_cb(imgbtn, button_clicked_cb, LV_EVENT_CLICKED, app);
	lv_obj_add_style(imgbtn, style_ptr, LV_PART_MAIN | LV_STATE_DISABLED);

	/* Pause button */
	imgbtn = lv_imgbtn_create(obj);
	if (imgbtn == NULL) {
		fprintf(stderr, "ERROR!! lv_imgbtn_create() failed.\n");
		return -1;
	}
	app->playback_ctrl[LSVP_CTRL_PAUSE_BTN] = imgbtn;

	lv_imgbtn_set_src(imgbtn, LV_IMGBTN_STATE_RELEASED, NULL, &LSVP_btn_pause, NULL);
	lv_obj_set_size(imgbtn, 80, 80);
	lv_obj_align(imgbtn, LV_ALIGN_TOP_LEFT, 216, 136);
	lv_obj_add_event_cb(imgbtn, button_clicked_cb, LV_EVENT_CLICKED, app);
	lv_obj_add_style(imgbtn, style_ptr, LV_PART_MAIN | LV_STATE_DISABLED);

	return 0;
}

/** Create video file play back screen
 *
 */
static int32_t create_video_file_playback_screen(lsvp_sample_app_t *app)
{
	lv_obj_t *screen;
	lv_obj_t *img;
	int32_t ret;
	lv_obj_t *txtimg;

	screen = lv_scr_act();
	lv_obj_set_style_bg_color(screen, lv_color_hex(LSVP_BG_COLOR), 0);

	/* Create image for text */
	txtimg = lv_img_create(screen);
	if (txtimg == NULL) {
		fprintf(stderr, "ERROR!! lv_img_create() failed.\n");
		return -1;
	}
	lv_img_set_src(txtimg, &LSVP_text);
	lv_obj_align(txtimg, LV_ALIGN_TOP_LEFT, 20, 20);

	ret = create_buttons(app, screen);
	if (ret)
		return -1;

	app->screen = screen;
	app->status = LSVP_STATUS_STOP;
	change_button_state(app);

	return ret;
}

/** Create sample app objects
 *
 * Basic objects for each screen are created, and data structures are allocated.
 */
int32_t lsvp_sample_app_setup(int32_t width, int32_t height, lv_disp_t *disp,
													char *input, int32_t audio)
{
	int32_t ret;

	app_obj = allocate_memory(sizeof (lsvp_sample_app_t));
	if (app_obj == NULL) {
		return -1;
	}

	app_obj->width = (lv_coord_t)width;
	app_obj->height = (lv_coord_t)height;
	app_obj->disp = disp;
	app_obj->input = input;
	app_obj->audio = audio;

	/* create video file playback screen */
	ret = create_video_file_playback_screen(app_obj);
	if (ret)
		return ret;

	return 0;
}

/** Quit sample app
 *
 * All objects and data structures are released.
 */
void lsvp_sample_app_quit(void)
{
	lsvp_sample_app_t *app = app_obj;

	if (!app)
		return;

	if (!app->quit_flag)	/* Quit player */
		lsvp_quit_playback();

	lv_obj_del(app->screen);

	/* Release memory for GUI screen */
	free(app);
}
