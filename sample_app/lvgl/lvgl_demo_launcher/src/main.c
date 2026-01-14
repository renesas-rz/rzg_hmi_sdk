/**
 * RZ LAUNCHER APP
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
#include	<json-glib/json-glib.h>

#include	"lvgl/lvgl.h"

#if	LV_USE_LINUX_FBDEV && LV_USE_EVDEV
  #undef	RUNS_ON_WAYLAND
#elif	LV_USE_WAYLAND
  #define	RUNS_ON_WAYLAND
#else
  #error	LVGL drivers configration error.
#endif

#ifdef	RUNS_ON_WAYLAND
  #include	"lvgl/src/drivers/wayland/lv_wayland.h"
#else
#include	"lvgl/src/drivers/display/fb/lv_linux_fbdev.h"
#endif	/* RUNS_ON_WAYLAND */

#include	"include/launcher_screen.h"

#define MAX_JSON_ARR 8
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

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
	int32_t window_width = WINDOW_WIDTH;
	int32_t window_height = WINDOW_HEIGHT;
	int32_t ret = 0;

	config btn_conf[MAX_JSON_ARR];
	int btn_cnt = 0; 

	/*LVGL init*/
	lv_init();

#ifdef RUNS_ON_WAYLAND

	disp = lv_wayland_window_create(window_width,window_height,
						    "Window Demo", NULL);
	if (disp == NULL) {
		printf("ERROR!! lv_wayland_create_window\n");
		goto APP_EXIT;
	}

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

	/*read json file */
	read_conf( &btn_cnt, btn_conf);
	
	/* make_screen */
	ret = launcher_screen(window_width, window_height, btn_cnt, btn_conf);
	if (ret < 0) {
		printf("ERROR!! launcher_screen() failed.\n");
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
#endif	
	}

APP_EXIT:

#ifdef RUNS_ON_WAYLAND
	lv_wayland_window_close(disp);

#else /* FBDEV and EVDEV  */
	close_fbdev_window(disp, pointer);
#endif
	return 0;
}

void read_conf(int *btn_cnt, config *btn_conf)
{
	
	int ary_cnt;
	int disc_str_cnt;
	const gchar *disc;
	JsonParser *parser;
   	JsonNode *root;
   	JsonObject *root_obj;
   	JsonArray *root_ary;
   	GError *error = NULL;
	int i = 0;

   	parser = json_parser_new();

   	if(!json_parser_load_from_file (parser, "/usr/share/demo-launcher/demo-launcher.json", &error))
   	{
   		g_print("can't load config_file");
   	}
   	root = json_parser_get_root (parser);
   	root_ary = json_node_get_array(root);

   	/*  read file */
   	ary_cnt = json_array_get_length(root_ary);
	
	if(ary_cnt > MAX_JSON_ARR){
		ary_cnt = MAX_JSON_ARR;
	}
   	for(i = 0;i < ary_cnt;i++)
   	{
   		root_obj = json_array_get_object_element(root_ary,i);
   		btn_conf[i].exe_cmd = json_object_get_string_member(root_obj, "exe_cmd");
   		disc = json_object_get_string_member(root_obj, "description");
   		
   		disc_str_cnt = strlen(disc);
   		if(disc_str_cnt > (DISC_STR_MAX - 1))
   		{
   		  	strncpy(btn_conf[i].discription,disc,DISC_STR_MAX);
   		  	btn_conf[i].discription[DISC_STR_MAX] = '\0';
   		}
   		else
   		{
   			strcpy(btn_conf[i].discription,disc);
   		}
   		
   		btn_conf[i].icon_image = json_object_get_string_member(root_obj, "icon_image");
   	}
	*btn_cnt = i;
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

