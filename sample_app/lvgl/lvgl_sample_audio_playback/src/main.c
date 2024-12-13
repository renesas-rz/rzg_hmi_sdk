/**
 * HMI SDK / RZ/G Linux sample program for audio playback
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
#include	<pthread.h>

#include	"lvgl/lvgl.h"
#include	"lvgl/lv_drivers/wayland/wayland.h"

#include	"sample-app.h"
#include	"sample-player.h"

static pthread_t id_playback_thread = 0;

static const char *audio_file[LSAP_MENU_NUM] = {
	"/usr/share/sounds/sample/sample_audio_stereo.mp3",
	"/usr/share/sounds/sample/sample_audio_stereo.wav",
	"/usr/share/sounds/sample/sample_audio_stereo.aac"
};

static void show_usage(void)
{
	printf("Usage: lvgl_sample_audio_playback [OPTION]\n\n"
		"Options are:\n"
		"\t-v, --version"
		"\toutput version information and exit\n"
		"\t-h, --help"
		"\tdisplay this help message and exit\n");
}

static void check_options(int argc, char *argv[])
{
	int option;
	int index;
	const char *optstring = "vh";
	const struct option longopts[] = {
		{"version", no_argument, NULL, 'v'},
		{"help", no_argument, NULL, 'h'},
		{NULL, 0, NULL, 0}
	};

	while (1) {
		option = getopt_long(argc, argv, optstring, longopts, &index);
		if (option == -1)
			break;
		switch(option){
		case 'v':
			printf("LVGL sample program for audio playback, "
				"Ver. %d.%02d\n" 
				"Copyright (C) 2024 Renesas Electronics Corp. "
				"All rights reserved.\n",
				LSAP_MAJOR_VERSION, LSAP_MINOR_VERSION);
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

static int32_t check_audio_files(void)
{
	int i;
	int ret;

	for (i = 0; i < LSAP_MENU_NUM; i++) {
		ret = access(audio_file[i], R_OK);
		if (ret) {
			printf("ERROR!! the sample audio file "
				"'%s' cannot be read.\n", audio_file[i]);
			return 1;
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	struct pollfd pfd;
	uint32_t time_till_next;
	int sleep;
	lv_coord_t width = LSAP_WINDOW_WIDTH;
	lv_coord_t height = LSAP_WINDOW_HEIGHT;
	int32_t ret;
	lv_disp_t *disp;

	check_options(argc, argv);

	/* check audio files */
	ret = check_audio_files();
	if (ret)
		return 1;

	if (pthread_create (&id_playback_thread, NULL, lsap_playback_loop, NULL)) {
		printf("ERROR!! pthread_create() failed.\n");
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

	pfd.fd = lv_wayland_get_fd();
	pfd.events = POLLIN;

	ret = lsap_sample_app_setup(width, height, disp, audio_file);
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

	lsap_sample_app_quit();

	lv_wayland_deinit();

	pthread_join(id_playback_thread, NULL);

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

