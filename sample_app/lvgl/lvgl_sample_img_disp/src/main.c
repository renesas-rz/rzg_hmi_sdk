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
#include	"lvgl/lv_drivers/wayland/wayland.h"

#include	"sample-app.h"


static int32_t check_options(int argc, char *argv[], int32_t *mode)
{
	int option;
	int index;
	int32_t ret = 0;
	const char *optstring = "fvh";
	const struct option longopts[] = {
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
			ret = 1;
			break;
		case 'h':
			printf("Usage: lvgl_sample_img_disp [OPTION]\n\n"
				"Options are:\n"
				"\t-f, --fullscreen\tfull screen mode\n"
				"\t\t\tunless specified, %d x %d\n"
				"\t-v, --version"
				"\toutput version information and exit\n"
				"\t-h, --help"
				"\tdisplay this help message and exit\n",
				LSID_WINDOW_WIDTH, LSID_WINDOW_HEIGHT);
			ret = 1;
			break;
		default:
			ret = -1;
			break;
		}
	}
	return ret;
}

int main(int argc, char *argv[])
{
	struct pollfd pfd;
	uint32_t time_till_next;
	int sleep;
	lv_coord_t width = LSID_WINDOW_WIDTH;
	lv_coord_t height = LSID_WINDOW_HEIGHT;
	int32_t ret;
	int32_t mode = 0;
	lv_disp_t *disp;

	ret = check_options(argc, argv, &mode);
	if (ret < 0) {
		return 1;
	}
	else if (ret > 0) {
		return 0;
	}

	/*LittlevGL init*/
	lv_init();

	lv_wayland_init();

	disp = lv_wayland_create_window(width, height, "Window Demo", NULL);
	if (disp == NULL) {
		printf("ERROR!! lv_wayland_create_window\n");
		lv_wayland_deinit();
		return 1;
	}

	if (mode)
		lv_wayland_window_set_fullscreen(disp, true);

	pfd.fd = lv_wayland_get_fd();
	pfd.events = POLLIN;

	ret = lsid_sample_app_setup(width, height, disp, mode);
	if (ret < 0) {
		printf("ERROR!! lb_demo_gui() failed.\n");
		lv_wayland_deinit();
		return 1;
	}

	while(1) {
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
	}

	lsid_sample_app_quit();

	lv_wayland_deinit();

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

