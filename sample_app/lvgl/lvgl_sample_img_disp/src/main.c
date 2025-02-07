/**
 * HMI SDK / RZ/G Linux LVGL sample program for image display
 *
 * Copyright (C) 2024 Renesas Electronics Corp. All rights reserved.
 */


#include	<unistd.h>
#include	<time.h>
#include	<sys/time.h>
#include	<fcntl.h>
#include	<stdlib.h>
#include	<string.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<limits.h>
#include	<errno.h>
#include	<poll.h>
#include	<stdbool.h>
#include	<getopt.h>

#include	"lvgl/lvgl.h"
#include	"sample-app.h"


static void show_usage(void)
{
	printf("Usage: lvgl_sample_img_disp [OPTION]\n\n"
		"Options are:\n"
		"\t-i, --input\tinput evdev device\n"
		"\t\tunless specified, device set to EVDEV_NAME "
		"in lv_drv_conf.h is used.\n"
		"\t\tThis is ineffective when this program runs on weston.\n"
		"\t-f, --fullscreen\tfull screen mode\n"
		"\t\tunless specified, %d x %d\n"
		"\t\tThis is ineffective when this program uses fbdev.\n"
		"\t-v, --version\toutput version information and exit\n"
		"\t-h, --help\tdisplay this help message and exit\n",
		LSID_WINDOW_WIDTH, LSID_WINDOW_HEIGHT);
}

static void check_options(int argc, char *argv[], int32_t *mode, char **input)
{
	int option;
	int index;
	const char *optstring = "i:fvh";
	const struct option longopts[] = {
		{"input", required_argument, NULL, 'i'},
		{"fullscreen", no_argument, NULL, 'f'},
		{"version", no_argument, NULL, 'v'},
		{"help", no_argument, NULL, 'h'},
		{NULL, 0, NULL, 0}
	};

	while (1) {
		option = getopt_long(argc, argv, optstring, longopts, &index);
		if (option == -1)
			break;
		switch(option){
		case 'i':
			if (input)
				*input = optarg;
			break;
		case 'f':
			if (mode)
				*mode = 1;
			break;
		case 'v':
			printf("LVGL sample program for iamge display, "
				"Ver. %d.%02d\n" \
				"Copyright (C) 2024 Renesas Electronics Corp. "
				"All rights reserved.\n",
				LSID_MAJOR_VERSION, LSID_MINOR_VERSION);
			exit(EXIT_SUCCESS);
			break;
		case 'h':
			show_usage();
			exit(EXIT_SUCCESS);
			break;
		default:
			printf("ERROR!! an unsupported option was"
							" specified.\n");
			show_usage();
			exit(EXIT_FAILURE);
			break;
		}
	}
	return;
}

#ifndef RUNS_ON_WAYLAND

/* Create fbdev window with evdev */
static lsid_dispinf_t *create_fbdev_window(char *inputdev)
{
	uint32_t width, height;
	lsid_dispinf_t *dispinf;
	lv_disp_drv_t *disp_drv;
	lv_obj_t *cursor_obj;
	bool ret;

	/* Init Linux frame buffer device for LVGL */
	fbdev_init();
	fbdev_get_sizes(&width, &height, NULL);

	dispinf = lv_mem_alloc(sizeof (lsid_dispinf_t));
	if (!dispinf) {
		printf("ERROR!! memory allocation failed at lv_mem_alloc()\n");
		return NULL;
	}

	dispinf->buff = lv_mem_alloc(width * height * sizeof(lv_color_t));
	if (!dispinf->buff) {
		printf("ERROR!! memory allocation failed at lv_mem_alloc()\n");
		lv_mem_free(dispinf);
		return NULL;
	}
	lv_disp_draw_buf_init(&dispinf->draw_buf, dispinf->buff, NULL,
							width * height);

	disp_drv = &dispinf->drv;
	/* Initialize and register a display driver */
	lv_disp_drv_init(disp_drv);

	disp_drv->draw_buf		= &dispinf->draw_buf;
	disp_drv->flush_cb		= fbdev_flush;
	disp_drv->hor_res		= (lv_coord_t)width;
	disp_drv->ver_res		= (lv_coord_t)height;
	disp_drv->physical_hor_res	= (lv_coord_t)width;
	disp_drv->physical_ver_res	= (lv_coord_t)height;

	dispinf->disp = lv_disp_drv_register(disp_drv);

	dispinf->width = (lv_coord_t)width;
	dispinf->height = (lv_coord_t)height;

	/* Init evdev for LVGL */
	evdev_init();

	if (inputdev) {
		ret = evdev_set_file(inputdev);
		if (!ret) {
			printf("ERROR!! the specified device file does not exist\n");
		}
	}

	lv_indev_drv_init(&dispinf->indev_drv);

	dispinf->indev_drv.type = LV_INDEV_TYPE_POINTER;
	/* This function will be called periodically (by the library)
	   to get the mouse position and state */
	dispinf->indev_drv.read_cb = evdev_read;

	dispinf->mouse_indev = lv_indev_drv_register(&dispinf->indev_drv);

	/* Set a cursor for the mouse */
	LV_IMG_DECLARE(mouse_cursor);
	/* Create an image object for the cursor */
	cursor_obj = lv_img_create(lv_scr_act());
	lv_img_set_src(cursor_obj, &mouse_cursor);
	/* Connect the image  object to the driver */
	lv_indev_set_cursor(dispinf->mouse_indev, cursor_obj);

	return dispinf;
}

static void close_fbdev_window(lsid_dispinf_t *dispinf)
{
	if (!dispinf) {
		printf("ERROR!! no object to be freed.\n");
		return;
	}

	if (dispinf->mouse_indev)
		lv_indev_delete(dispinf->mouse_indev);

	if (dispinf->disp)
		lv_disp_remove(dispinf->disp);

	if (dispinf->buff)
		lv_mem_free(dispinf->buff);

	lv_mem_free(dispinf);

	fbdev_exit();
}
#endif

int main(int argc, char *argv[])
{
#ifdef RUNS_ON_WAYLAND
	struct pollfd pfd;
	uint32_t time_till_next;
	int sleep;
	lv_disp_t *disp;
#else /* FBDEV and EVDEV  */
	lsid_dispinf_t *disp;
#endif
	lv_coord_t width = LSID_WINDOW_WIDTH;
	lv_coord_t height = LSID_WINDOW_HEIGHT;
	int32_t ret;
	int32_t mode = 0;
	char *inputdev = NULL;

	check_options(argc, argv, &mode, &inputdev);

	/* LittlevGL init */
	lv_init();

#ifdef RUNS_ON_WAYLAND
	lv_wayland_init();

	disp = lv_wayland_create_window(width, height, "Window Demo", NULL);
	if (disp == NULL) {
		printf("ERROR!! lv_wayland_create_window\n");
		goto APP_EXIT;
	}

	if (mode)
		lv_wayland_window_set_fullscreen(disp, true);

	pfd.fd = lv_wayland_get_fd();
	pfd.events = POLLIN;

#else /* FBDEV and EVDEV  */
	disp = create_fbdev_window(inputdev);
	if (disp == NULL) {
		printf("ERROR!! lv_wayland_create_window\n");
		goto APP_EXIT;
	}
	/* Clear end flag */
	disp->end = false;
	/* The fullscreen mode is always '1' when weston is not used. */
	mode = 1;
	width = disp->width;
	height = disp->height;

#endif
	ret = lsid_sample_app_setup(width, height, (void *)disp, mode);
	if (ret < 0) {
		printf("ERROR!! lb_demo_gui() failed.\n");
		goto APP_EXIT;
	}

	while(1) {
#ifdef RUNS_ON_WAYLAND
		/* Handle any Wayland/LVGL timers/events */
		time_till_next = lv_wayland_timer_handler();

		/* Run until the last window closes */
		if (!lv_wayland_window_is_open(NULL)) {
			break;
		}

		/* Wait for something interesting to happen */
		if (time_till_next == LV_NO_TIMER_READY) {
			sleep = -1;
		} else if (time_till_next > INT_MAX) {
			sleep = INT_MAX;
		} else {
			sleep = time_till_next;
		}
		while ((poll(&pfd, 1, sleep) < 0) && (errno == EINTR));

#else /* FBDEV and EVDEV  */
		lv_timer_handler();
		usleep(5000);
		if (disp->end)
			break;
#endif
	}

	lsid_sample_app_quit();
APP_EXIT:

#ifdef RUNS_ON_WAYLAND
	lv_wayland_deinit();

#else /* FBDEV and EVDEV  */
	close_fbdev_window(disp);
#endif
	return 0;
}

/**
 * Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`
 */
uint32_t custom_tick_get(void)
{
	static uint64_t start_ms = 0;
	struct timeval tv_start;
	struct timeval tv_now;
	uint64_t now_ms;

	if(start_ms == 0) {
		gettimeofday(&tv_start, NULL);
		start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
	}
	gettimeofday(&tv_now, NULL);
	now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

	return (uint32_t)(now_ms - start_ms);
}

