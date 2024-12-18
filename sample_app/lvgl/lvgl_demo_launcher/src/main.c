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
#include	"lvgl/lv_drivers/lv_drv_conf.h"

#if	USE_FBDEV && USE_EVDEV
  #undef	RUNS_ON_WAYLAND
#elif	USE_WAYLAND
  #define	RUNS_ON_WAYLAND
#else
  #error	LVGL drivers configration error.
#endif

#ifdef	RUNS_ON_WAYLAND
  #include	"lvgl/lv_drivers/wayland/wayland.h" 
#else
#include	"lvgl/lv_drivers/display/fbdev.h"
#include	"lvgl/lv_drivers/indev/evdev.h"

typedef struct {
	lv_coord_t width;
	lv_coord_t height;
	bool end;
	lv_color_t *buff;
	lv_disp_draw_buf_t draw_buf;
	lv_disp_drv_t drv;
	lv_disp_t *disp;
	lv_indev_drv_t indev_drv;
	lv_indev_t *mouse_indev;
} dispinf_fbevdev_t;
#endif	/* RUNS_ON_WAYLAND */

#include	"include/launcher_screen.h"

#define MAX_JSON_ARR 8
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#ifndef RUNS_ON_WAYLAND

/* Create fbdev window with evdev */
static dispinf_fbevdev_t *create_fbdev_window()
{
	uint32_t width, height;
	dispinf_fbevdev_t *dispinf;
	lv_disp_drv_t *disp_drv;
	lv_obj_t *cursor_obj;
	bool ret;

	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	
	/* Init Linux frame buffer device for LVGL */
	fbdev_init();

	dispinf = lv_mem_alloc(sizeof (dispinf_fbevdev_t));
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

static void close_fbdev_window(dispinf_fbevdev_t *dispinf)
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
	dispinf_fbevdev_t *disp;
#endif		
	int32_t window_width = WINDOW_WIDTH;
	int32_t window_height = WINDOW_HEIGHT;
	int32_t ret = 0;

	config btn_conf[MAX_JSON_ARR];
	int btn_cnt = 0; 


	/*LVGL init*/
	lv_init();

#ifdef RUNS_ON_WAYLAND
	lv_wayland_init();

	disp = lv_wayland_create_window(window_width,window_height,
						    "Window Demo", NULL);
	if (disp == NULL) {
		printf("ERROR!! lv_wayland_create_window\n");
		goto APP_EXIT;
	}

	pfd.fd = lv_wayland_get_fd();
	pfd.events = POLLIN;

#else /* FBDEV and EVDEV  */
	disp = create_fbdev_window();
	if (disp == NULL) {
		printf("ERROR!! lv_wayland_create_window\n");
		goto APP_EXIT;
	}
	/* Clear end flag */
	disp->end = false;
	window_width = disp->width;
	window_height = disp->height;
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
		if (disp->end)
			break;
#endif	
	}

APP_EXIT:

#ifdef RUNS_ON_WAYLAND
	lv_wayland_deinit();

#else /* FBDEV and EVDEV  */
	close_fbdev_window(disp);
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

