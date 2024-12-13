/**
 * HMI SDK / RZ/G Linux sample program for video playback
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

static void show_usage(void)
{
	printf("Usage: lvgl_sample_video_playback [OPTION]\n\n"
		"Options are:\n"
		"\t-i, --input"
		"\tinput movie file\n"
		"\t\tThis option is mandatory.\n"
		"\t-a, --audio"
		"\tplayback a movie with sound\n"
		"\t\tWhen a movie file that has audio data is played with"
		" this option, audio will be output.\n"
		"\t-v, --version"
		"\toutput version information and exit\n"
		"\t-h, --help"
		"\tdisplay this help message and exit\n");
}

static void check_options(int argc, char *argv[], char **input, int32_t *audio)
{
	int option;
	int index;
	const char *optstring = "i:avh";
	const struct option longopts[] = {
		{"input", required_argument, NULL, 'i'},
		{"audio", no_argument, NULL, 'a'},
		{"version", no_argument, NULL, 'v'},
		{"help", no_argument, NULL, 'h'},
		{NULL, 0, NULL, 0}
	};
	if (audio)
		*audio = 0;

	while (1) {
		option = getopt_long(argc, argv, optstring, longopts, &index);
		if (option == -1)
			break;
		switch(option){
		case 'i':
			if (input)
				*input = optarg;
			break;
		case 'a':
			if (audio)
				*audio = 1;
			break;
		case 'v':
			printf("LVGL sample program for video playback, "
				"Ver. %d.%02d\n" 
				"Copyright (C) 2024 Renesas Electronics Corp. "
				"All rights reserved.\n",
				LSVP_MAJOR_VERSION, LSVP_MINOR_VERSION);
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

int main(int argc, char *argv[])
{
	struct pollfd pfd;
	uint32_t time_till_next;
	int sleep;
	lv_coord_t width = LSVP_WINDOW_WIDTH;
	lv_coord_t height = LSVP_WINDOW_HEIGHT;
	int32_t ret;
	lv_disp_t *disp;
	char *input = NULL;
	int32_t audio = 0;

	check_options(argc, argv, &input, &audio);
	if (input == NULL) {
		printf("ERROR!! input movie file is not set.\n");
		return 1;
	}
	/* check input file */
	ret = access(input, R_OK);
	if (ret) {
		printf("ERROR!! the input movie file '%s' cannot be read.\n",
									input);
		return 1;
	}

	if (pthread_create (&id_playback_thread, NULL, lsvp_playback_loop,
							(void *)&audio)) {
		printf("ERROR!! pthread_create() failed.\n");
	}

	/*LittlevGL init */
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

	ret = lsvp_sample_app_setup(width, height, disp, input, audio);
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

	lsvp_sample_app_quit();

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

