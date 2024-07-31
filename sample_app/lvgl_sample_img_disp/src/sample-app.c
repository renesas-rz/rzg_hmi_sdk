/**
 * HMI SDK / RZ/G Linux LVGL sample program for image display
 *
 * Copyright (C) 2024 Renesas Electronics Corp. All rights reserved.
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

#include	"lvgl/lvgl.h"
#include	"lvgl/lv_drivers/wayland/wayland.h"

#include	"sample-app.h"

/* Image data for GUI */
LV_IMG_DECLARE(LSID_1_btn1);
LV_IMG_DECLARE(LSID_1_btn2);
LV_IMG_DECLARE(LSID_1_btn3);
LV_IMG_DECLARE(LSID_1_btn4);
LV_IMG_DECLARE(LSID_1_btn5);
LV_IMG_DECLARE(LSID_1_btn6);
LV_IMG_DECLARE(LSID_1_btn7);
LV_IMG_DECLARE(LSID_1_btn8);
LV_IMG_DECLARE(LSID_1_guide);
LV_IMG_DECLARE(LSID_1_btn_quit);
LV_IMG_DECLARE(LSID_2_btn_back);

/* Sample program object */
static lsid_sample_app_t *app_obj = NULL;

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

/** Quit button callback
 *
 * This function is called when quit button is clicked.
 *
 */
static void quit_button_clicked_cb(lv_event_t *e)
{
	lsid_sample_app_t *app;

	app = (lsid_sample_app_t *)lv_event_get_user_data(e);

	lv_wayland_close_window(app->disp);
}

/** Create a quit button
 *
 * The button is used when fullscreen mode is enabled.
 *
 */
static int32_t create_quit_button(lsid_sample_app_t *app, lv_obj_t *obj)
{
	lv_obj_t *imgbtn;

	imgbtn = lv_imgbtn_create(obj);
	if (imgbtn == NULL) {
		fprintf(stderr, "ERROR!! lv_imgbtn_create() failed.\n");
		return -1;
	}
	if (app->imgdsp_scr == obj)
		app->quit_btn = imgbtn;	/* quit button in the image file display screen */

	lv_imgbtn_set_src(imgbtn, LV_IMGBTN_STATE_RELEASED, NULL, &LSID_1_btn_quit, NULL);

	lv_obj_add_event_cb(imgbtn, quit_button_clicked_cb, LV_EVENT_CLICKED, app);
	lv_obj_set_size(imgbtn, 60, 60);
	lv_obj_align(imgbtn, LV_ALIGN_TOP_RIGHT, -24, 24);

	return 0;
}

/** Image file selection screen
 *
 */
static void set_image(lsid_sample_app_t *app, lsid_img_file_t *img_file)
{
	lv_obj_t *img;

	if (img_file->format == LSID_IMG_FORMAT_GIF) {
		img = lv_gif_create(app->imgdsp_scr);
		lv_gif_set_src(img, img_file->file_path);
	}
	else {
		img = lv_img_create(app->imgdsp_scr);
		lv_img_set_src(img, img_file->file_path);
	}
	lv_obj_align(img, LV_ALIGN_TOP_LEFT, 0, 0);
	lv_obj_set_size(img, img_file->width, img_file->height);

	app->img_obj = img;
}

/** Image button callback
 *
 */
static void img_button_clicked_cb(lv_event_t *e)
{
	lsid_img_set_t *imgset;
	lsid_sample_app_t *app;

	imgset = (lsid_img_set_t *)lv_event_get_user_data(e);
	app = (lsid_sample_app_t *)imgset->data;

	set_image(app, &imgset->img_file);

	/* quit button is valid only when fullscreen mode is enabled */
	if (app->mode)
		lv_obj_move_foreground(app->quit_btn);
	lv_obj_move_foreground(app->back_btn);

	/* Screen transition */
	lv_scr_load(app->imgdsp_scr);
}

/** Create 8 buttons
 *
 */
static int32_t create_buttons(lsid_sample_app_t *app, lv_obj_t *obj)
{
	int i;
	lv_obj_t *imgbtn;

	lsid_rect_t rect[LSID_NUMBER_BTNS] = {
		{640, 36, 256, 144},  {640, 204, 256, 144},
		{640, 372, 256, 144}, {640, 540, 256, 144},
		{920, 36, 256, 144},  {920, 204, 256, 144},
		{920, 372, 256, 144}, {920, 540, 256, 144}
	};
	const void *btn_img[LSID_NUMBER_BTNS] = {
		&LSID_1_btn1, &LSID_1_btn2, &LSID_1_btn3, &LSID_1_btn4,
		&LSID_1_btn5, &LSID_1_btn6, &LSID_1_btn7, &LSID_1_btn8
	};
	static lsid_img_set_t img_data[LSID_NUMBER_BTNS] = {
	{
		NULL, 
		{LSID_IMG_FORMAT_BMP, 1280, 720,
		 "L:/usr/share/images/sample_image_1280x720.bmp"}
	},
	{
		NULL, 
		{LSID_IMG_FORMAT_BMP, 640, 360,
		"L:/usr/share/images/sample_image_640x360.bmp"}
	},
	{
		NULL, 
		{LSID_IMG_FORMAT_JPG, 1280, 720,
		"L:/usr/share/images/sample_image_1280x720.sjpg"}
	},
	{
		NULL, 
		{LSID_IMG_FORMAT_JPG, 640, 360,
		"L:/usr/share/images/sample_image_640x360.jpg"}
	},
	{
		NULL, 
		{LSID_IMG_FORMAT_PNG, 1280, 720,
		"L:/usr/share/images/sample_image_1280x720.png"}
	},
	{
		NULL, 
		{LSID_IMG_FORMAT_PNG, 640, 360,
		"L:/usr/share/images/sample_image_640x360.png"}
	},
	{
		NULL, 
		{LSID_IMG_FORMAT_GIF, 1280, 720,
		"L:/usr/share/images/sample_image_1280x720.gif"}
	},
	{
		NULL, 
		{LSID_IMG_FORMAT_GIF, 640, 360,
		"L:/usr/share/images/sample_image_640x360.gif"}
	}};
	lsid_img_set_t *imgset;

	imgset = &img_data[0];
	for (i = 0; i < LSID_NUMBER_BTNS; i++) {
		imgbtn = lv_imgbtn_create(obj);
		if (imgbtn == NULL) {
			fprintf(stderr, "ERROR!! lv_imgbtn_create() failed.\n");
			return -1;
		}
		lv_imgbtn_set_src(imgbtn, LV_IMGBTN_STATE_RELEASED, NULL, btn_img[i], NULL);

		imgset->data = app;
		lv_obj_add_event_cb(imgbtn, img_button_clicked_cb, LV_EVENT_CLICKED, imgset);
		lv_obj_set_size(imgbtn, rect[i].w, rect[i].h);
		lv_obj_align(imgbtn, LV_ALIGN_TOP_LEFT, rect[i].x, rect[i].y);
		imgset++;
	}
	return 0;
}

/** Create image file selection screen
 *
 */
static int32_t create_image_file_selection_screen(lsid_sample_app_t *app)
{
	lv_obj_t *screen;
	lv_obj_t *guide;
	int32_t ret;

	screen = lv_scr_act();
	lv_obj_set_style_bg_color(screen, lv_color_hex(LSID_BG_COLOR), 0);

	/* Ceate a image for guide */
	guide = lv_img_create(screen);
	if (guide == NULL) {
		fprintf(stderr, "ERROR!! lv_img_create() failed.\n");
		return -1;
	}
	lv_img_set_src(guide, &LSID_1_guide);
	lv_obj_align(guide, LV_ALIGN_TOP_LEFT, LSID_GUIDE_POS_X, LSID_GUIDE_POS_Y);

	/* Create 8 buttons */
	ret = create_buttons(app, screen);
	if (ret)
		return -1;

	/* Create a quit button when fullscreen mode is enabled */
	if (app->mode)
		ret = create_quit_button(app, screen);

	app->imgsel_scr = screen;

	return ret;
}

/** Back button callback
 *
 * This function is called when back button is clicked.
 *
 */
static void back_button_clicked_cb(lv_event_t *e)
{
	lsid_sample_app_t *app;

	app = (lsid_sample_app_t *)lv_event_get_user_data(e);

	/* Delete image object with a delay */
	lv_obj_del_async(app->img_obj);

	/* Screen transition */
	lv_scr_load(app->imgsel_scr);
}

/** Create a back button
 *
 */
static int32_t create_back_button(lsid_sample_app_t *app, lv_obj_t *obj)
{
	lv_obj_t *imgbtn;

	imgbtn = lv_imgbtn_create(obj);
	if (imgbtn == NULL) {
		fprintf(stderr, "ERROR!! lv_imgbtn_create() failed.\n");
		return -1;
	}
	app->back_btn = imgbtn;

	lv_imgbtn_set_src(imgbtn, LV_IMGBTN_STATE_RELEASED, NULL, &LSID_2_btn_back, NULL);

	lv_obj_add_event_cb(imgbtn, back_button_clicked_cb, LV_EVENT_CLICKED, app);
	lv_obj_set_size(imgbtn, 160, 64);
	lv_obj_align(imgbtn, LV_ALIGN_BOTTOM_RIGHT, -24, -24);

	return 0;
}

/** Create image file display screen
 *
 */
static int32_t create_image_file_display_screen(lsid_sample_app_t *app)
{
	lv_obj_t *screen;
	lv_obj_t *img;
	int32_t ret;

	screen = lv_obj_create(NULL);
	lv_obj_set_style_bg_color(screen, lv_color_hex(LSID_BG_COLOR), 0);

	app->imgdsp_scr = screen;

	/* Create back button */
	ret = create_back_button(app, screen);
	if (ret)
		return -1;

	/* Create a quit button when fullscreen mode is enabled */
	if (app->mode)
		ret = create_quit_button(app, screen);

	return ret;
}

/** Create sample app objects
 *
 * Basic objects for each screen are created, and data structures are allocated.
 */
int32_t lsid_sample_app_setup(int32_t width, int32_t height, lv_disp_t *disp, int32_t mode)
{
	int32_t ret;

	app_obj = allocate_memory(sizeof (lsid_sample_app_t));
	if (app_obj == NULL) {
		return -1;
	}

	app_obj->width = (lv_coord_t)width;
	app_obj->height = (lv_coord_t)height;
	app_obj->disp = disp;
	app_obj->mode = mode;

	/* create image file selectio screen */
	ret = create_image_file_selection_screen(app_obj);
	if (ret)
		return ret;

	/* create iamge file display screen */
	ret = create_image_file_display_screen(app_obj);
	if (ret)
		return ret;

	return 0;
}

/** Quit sample app
 *
 * All objects and data structures are released.
 */
void lsid_sample_app_quit(void)
{
	lsid_sample_app_t *app = app_obj;

	if (!app)
		return;

	lv_obj_del(app->imgsel_scr);
	lv_obj_del(app->imgdsp_scr);

	/* Release memory for GUI screen */
	free(app);
}


