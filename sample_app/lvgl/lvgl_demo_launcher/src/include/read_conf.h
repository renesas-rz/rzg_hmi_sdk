#ifndef READ_CONF_H
#define READ_CONF_H

#include	<json-glib/json-glib.h>
#include	"../lvgl/lvgl.h"


#define DISC_STR_MAX              (28)
#define MAX_APPS                   (8)
#define MAX_UI_FRAMEWORKS          (4)
#define CMD_STR_MAX              (128)
#define UI_FRAMEWORK_STR_MAX      (16)
#define IMAGE_ICON_STR_MAX       (128)


typedef struct
{
	gchar exe_cmd[CMD_STR_MAX];
	gchar discription[DISC_STR_MAX];
}apps_info_st;

typedef struct
{
	gchar ui_framework_name[UI_FRAMEWORK_STR_MAX];
	gchar icon_image_path[IMAGE_ICON_STR_MAX];
	apps_info_st apps[MAX_APPS];
	int apps_info_cnt;
	int ui_framework_cnt;
}ui_framework_info_st;

void read_conf(ui_framework_info_st *ui_framework_info);

#endif  /* READ_CONF_H */