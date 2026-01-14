/**
 * LVGL HomePanelDemo
 */
#include	<unistd.h>
#include	<time.h>
#include	<sys/time.h>
#include	<fcntl.h>
#include	<stdlib.h>
#include	<string.h>
#include	<stdlib.h>
#include	<limits.h>
#include	<errno.h>
#include	<poll.h>
#include	<stdbool.h>
#include	<getopt.h>
#include	<pthread.h>

#include  "include/Home_Panel_Demo.h"
#include 	"../lvgl/src/misc/lv_fs_private.h"

#ifdef	RUNS_ON_WAYLAND
  #include	"lvgl/src/drivers/wayland/lv_wayland.h"
#else
#include	"lvgl/src/drivers/display/fb/lv_linux_fbdev.h"

#endif	/* RUNS_ON_WAYLAND */

lv_obj_t* sc1;

lv_obj_t* anim_btn;
lv_obj_t* anim_btn2;
lv_obj_t* before_obj;
lv_obj_t* after_obj;
lv_obj_t* obj_space;
lv_obj_t* background;
lv_obj_t* header_background;
lv_obj_t* header_logo;
int32_t logo_ratio = 0;

int background_width;
int background_height;

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
#endif		
	int32_t window_width = 1920;
	int32_t window_height = 1080;
	int32_t ret = 0;

	/*LVGL init*/
	lv_init();
    lv_fs_init();
    lv_fs_stdio_init();
    lv_lodepng_init();
	lv_tjpgd_init();

#ifdef RUNS_ON_WAYLAND
	disp = lv_wayland_window_create(window_width,window_height,
						    "Window Demo", NULL);
	if (disp == NULL)
	{
		printf("ERROR!! lv_wayland_window_create\n");
		goto APP_EXIT;
	}
    lv_wayland_window_set_fullscreen(disp,true);

	pfd.fd = lv_wayland_get_fd();
	pfd.events = POLLIN;

#else /* FBDEV and EVDEV  */
	const char *device = getenv_default("LV_LINUX_FBDEV_DEVICE", "/dev/fb0");
	disp =  lv_linux_fbdev_create();
	if (disp == NULL) {
		printf("ERROR!! lv_linux_fbdev_create\n");
		goto APP_EXIT;
	}
	lv_indev_t *pointer = lv_evdev_create(LV_INDEV_TYPE_POINTER, "/dev/input/event1");
	LV_IMG_DECLARE(mouse_cursor);
	lv_obj_t* cursor_obj = lv_image_create(lv_screen_active());
	lv_img_set_src(cursor_obj, &mouse_cursor);
	lv_indev_set_cursor(pointer, cursor_obj);
	lv_indev_set_display(pointer, disp);
	lv_linux_fbdev_set_file(disp, device);
#endif

	background_width = lv_display_get_horizontal_resolution(disp);
	background_height = lv_display_get_vertical_resolution(disp);

	create_menu();
	create_Dashboard();
	create_Image_Gallery();
	create_Home_Automation();
	create_Weather_History();

	int32_t timer_cnt = 0;
	while(1)
	{
#ifdef RUNS_ON_WAYLAND
		timer_cnt++;
		/* Draw a seek bar every 200ms when playing audio */
		if(music_state == 1 && timer_cnt > 40)
		{
			cb_print_position();
			timer_cnt = 0;
		}
		/* Handle any Wayland/LVGL timers/events */
		time_till_next = lv_wayland_timer_handler();

		/* Run until the last window closes */
		if (!lv_wayland_window_is_open(NULL))
		{
			break;
		}

		/* Wait for something interesting to happen */
		if (time_till_next == LV_NO_TIMER_READY)
		{
			sleep = -1;
		} else if (time_till_next > INT_MAX)
		{
			sleep = INT_MAX;
		} else 
		{
			sleep = time_till_next;
		}
		while ((poll(&pfd, 1, sleep) < 0) && (errno == EINTR));
#else /* FBDEV and EVDEV  */
		lv_timer_handler();
#endif	
		usleep(5000);
	}

APP_EXIT:

#ifdef RUNS_ON_WAYLAND
	/* cleanup */
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (GST_OBJECT (pipeline));
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

	if(start_ms == 0)
	{
		gettimeofday(&tv_start, NULL);
		start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
	}
	gettimeofday(&tv_now, NULL);
	now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

	return (uint32_t)(now_ms - start_ms);
}