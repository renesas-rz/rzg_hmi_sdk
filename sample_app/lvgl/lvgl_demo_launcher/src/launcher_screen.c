/**
 * RZ LAUNCHER APP
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>


#include	"include/launcher_screen.h"

#include	"../lvgl/lvgl.h"
#include	"../lvgl/src/misc/lv_fs.h"
#include	"../lvgl/src/extra/libs/png/lv_png.h"
#include	"../lvgl/src/extra/libs/fsdrv/lv_fsdrv.h"

int32_t lb_demo_gui(int32_t width, int32_t height, lv_disp_t *disp, char *cfg_path);
static void btn_event_cb(lv_event_t* event);
static uint16_t img_ratio_calc(lv_obj_t* img,uint16_t scr_width, uint16_t scr_height);

int32_t launcher_screen(int32_t width, int32_t height, int btn_cnt, config *btn_conf)
{
	int btn_num = 0;
	uint16_t img_ratio;
	
       /* init */
       _lv_fs_init();
       lv_fs_stdio_init();
       lv_init();
       lv_png_init();

       /*window*/
       static lv_style_t win_style;
       lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x2A289D),LV_PART_MAIN);

       lv_obj_t *title_text = lv_label_create(lv_scr_act()) ;
       lv_obj_t *guide_text = lv_label_create(lv_scr_act()) ;
       lv_obj_t *logo_image = lv_img_create(lv_scr_act());

       static lv_style_t btn_style;
       lv_style_init(&btn_style);
       lv_style_set_radius(&btn_style, 3);
       lv_style_set_bg_opa(&btn_style, LV_OPA_100);
       lv_style_set_bg_color(&btn_style, lv_color_hex(0xFFFFFF));
       lv_style_set_bg_grad_color(&btn_style, lv_palette_darken(LV_PALETTE_BLUE, 2));

       for(btn_num = 0; btn_num < btn_cnt;btn_num++)
       {
       	/* btn */
       	btn_conf[btn_num].btn = lv_btn_create(lv_scr_act());
       	lv_obj_set_pos(btn_conf[btn_num].btn, 40, (140 * btn_num + 80));
       	lv_obj_set_size(btn_conf[btn_num].btn, 560, 120);
       	lv_obj_add_style(btn_conf[btn_num].btn, &btn_style, 0);
       	lv_obj_add_event_cb(btn_conf[btn_num].btn, btn_event_cb, LV_EVENT_CLICKED, &btn_conf[btn_num]);

       	/* discription */
       	lv_obj_t* btn_disc =lv_label_create(btn_conf[btn_num].btn);
       	lv_label_set_text(btn_disc,btn_conf[btn_num].discription);
       	lv_obj_set_width(btn_disc, 420);
       	lv_obj_set_height(btn_disc, 90);
       	lv_obj_set_pos(btn_disc, 115, 36);
       	static lv_style_t btn_disc_style;
   		lv_style_init(&btn_disc_style);
   		lv_style_set_text_font(&btn_disc_style, &FiraCode_Regular_24);
   		lv_obj_add_style(btn_disc, &btn_disc_style, 0);
   		lv_style_set_text_color(&btn_disc_style, lv_color_hex(0x06418C));

   		/* icon_img */
   		lv_obj_t* icon_img = lv_img_create(btn_conf[btn_num].btn);
   		lv_img_set_src(icon_img,btn_conf[btn_num].icon_image);
   		lv_obj_set_align(icon_img,LV_ALIGN_LEFT_MID);
   		lv_obj_update_layout(icon_img);
   		img_ratio = img_ratio_calc(icon_img,100, 100);
   		
   		lv_img_set_zoom(icon_img,img_ratio);
   		lv_img_set_size_mode(icon_img, LV_IMG_SIZE_MODE_REAL);
   		lv_obj_set_size(icon_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

       }
       /*Title_text*/
       lv_label_set_text(title_text,"HMI SDK Demo Launcher");
       lv_obj_set_pos(title_text, 160, 24);
       static lv_style_t title_text_style;
       lv_style_init(&title_text_style);
       lv_style_set_text_font(&title_text_style, &FiraCode_Regular_28);
       lv_obj_add_style(title_text, &title_text_style, 0);
       lv_style_set_text_color(&title_text_style, lv_color_hex(0xffffff));

       /*Guide_text*/
       lv_label_set_text(guide_text,"Select a demo below");
       lv_obj_set_pos(guide_text, 50, 56);
       static lv_style_t guide_text_style;
       lv_style_init(&guide_text_style);
       lv_style_set_text_font(&guide_text_style, &FiraCode_Regular_12);
       lv_obj_add_style(guide_text, &guide_text_style, 0);
       lv_style_set_text_color(&guide_text_style, lv_color_hex(0xB9D7FC));

       /*Logo image */
       lv_img_set_src(logo_image,"L:/usr/share/demo-launcher/images/renesas_logomark_white.png");
       lv_obj_set_pos(logo_image, 10, 10);
       lv_obj_update_layout(logo_image);
       img_ratio = img_ratio_calc(logo_image,100, 16);
       lv_img_set_zoom(logo_image,img_ratio);
       lv_img_set_size_mode(logo_image, LV_IMG_SIZE_MODE_REAL);
       lv_obj_set_size(logo_image, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

	return 0;
}

static void btn_event_cb(lv_event_t* event)
{	
	config *cmd = lv_event_get_user_data(event);
	
	execlp(cmd->exe_cmd,cmd->exe_cmd,NULL);
	perror(cmd->exe_cmd);
}

static uint16_t img_ratio_calc(lv_obj_t* img,uint16_t scr_width, uint16_t scr_height)
{
	uint16_t ratio;
	u_int16_t img_width;
	u_int16_t img_height;
	u_int16_t img_obj_width = lv_obj_get_width(img);
	u_int16_t img_obj_height = lv_obj_get_height(img);
	
	if(img_obj_width > img_obj_height)
	{
		ratio = 256.0 * (double)scr_width/(double)img_obj_width;
	}
	else
	{
		ratio = 256.0 * (double)scr_height/(double)img_obj_height;
	}
	return ratio;
}
