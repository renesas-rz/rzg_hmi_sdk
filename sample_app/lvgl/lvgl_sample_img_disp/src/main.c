/**
 * HMI SDK / RZ/G Linux LVGL sample program for image display
 *
 * Copyright (C) 2024-2026 Renesas Electronics Corp. All rights reserved.
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
			printf("LVGL sample program for image display, "
				"Ver. %d.%02d\n" \
				"Copyright (C) 2024-2026 "
				"Renesas Electronics Corp. "
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

static void close_fbdev_window(lv_display_t *dispinf, lv_indev_t *pointerinf)
{
	if (!dispinf) {
		printf("ERROR!! no object to be freed.\n");
		return;
	}

	if (pointerinf)
		lv_indev_delete(pointerinf);

	if (dispinf)
		lv_display_delete(dispinf);

	lv_mem_deinit();
}

static const char *getenv_default(const char *name, const char *dflt)
{
    return getenv(name) ? : dflt;
}
#endif

int main(int argc, char *argv[])
{
	lv_display_t *disp;
#ifdef RUNS_ON_WAYLAND
	struct pollfd pfd;
	uint32_t time_till_next;
	int sleep;
#else /* FBDEV and EVDEV  */
#endif
	int32_t width = LSID_WINDOW_WIDTH;
	int32_t height = LSID_WINDOW_HEIGHT;
	int32_t ret;
	int32_t mode = 0;
	char *inputdev = NULL;

	check_options(argc, argv, &mode, &inputdev);

	/* LittlevGL init */
	lv_init();
	lv_tjpgd_init();

#ifdef RUNS_ON_WAYLAND
	disp = lv_wayland_window_create(width, height, "Window Demo", NULL);
	if (disp == NULL) {
		printf("ERROR!! lv_wayland_create_window\n");
		goto APP_EXIT;
	}

	if (mode)
		lv_wayland_window_set_fullscreen(disp, true);

	pfd.fd = lv_wayland_get_fd();
	pfd.events = POLLIN;

#else /* FBDEV and EVDEV  */
	const char *device = getenv_default("LV_LINUX_FBDEV_DEVICE", "/dev/fb0");
	disp =  lv_linux_fbdev_create();
	if (disp == NULL) {
		printf("ERROR!! lv_linux_fbdev_create\n");
		goto APP_EXIT;
	}
	if (inputdev == NULL) {
		inputdev = "/dev/input/event1";
	}
	lv_indev_t *pointer = lv_evdev_create(LV_INDEV_TYPE_POINTER, inputdev);
	LV_IMG_DECLARE(mouse_cursor);
	lv_obj_t* cursor_obj = lv_image_create(lv_screen_active());
	lv_img_set_src(cursor_obj, &mouse_cursor);
	lv_indev_set_cursor(pointer, cursor_obj);
	lv_indev_set_display(pointer, disp);
	lv_linux_fbdev_set_file(disp, device);
	mode = 1;
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

		if (end == true)
			break;
#else /* FBDEV and EVDEV  */
		lv_timer_handler();
		usleep(5000);
		if (end == true)
			break;
#endif
	}

	lsid_sample_app_quit();
APP_EXIT:

#ifdef RUNS_ON_WAYLAND
	lv_wayland_window_close(disp);

#else /* FBDEV and EVDEV  */
	close_fbdev_window(disp, pointer);
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

