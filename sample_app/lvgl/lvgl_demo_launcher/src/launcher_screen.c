/**
 * RZ LAUNCHER APP
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>


#include	"include/launcher_screen.h"
#include	"include/read_conf.h"

#include	"../lvgl/lvgl.h"
#include	"../lvgl/src/misc/lv_fs.h"
#include	"../lvgl/src/libs/fsdrv/lv_fsdrv.h"

lv_obj_t *ui_framework_screen = NULL;

static int32_t img_ratio_calc(lv_obj_t* img,int32_t scr_width, int32_t scr_height);
void add_close_btn(lv_obj_t* obj);
void add_title_text(lv_obj_t* obj);
void add_logo_img(lv_obj_t* obj);
void add_back_button(lv_obj_t* obj);
lv_obj_t* create_app_screen(ui_framework_info_st *ui_framework_info, gchar *select_ui_framework);
lv_obj_t* create_select_ui_framework_screen(int32_t width, int32_t height, ui_framework_info_st *ui_framework_info);
void launcher_screen(int32_t width, int32_t height, ui_framework_info_st *ui_framework_info);
void back_button_event_cb(lv_event_t* event);
void ui_framework_button_event_cb(lv_event_t* event);
void btn_event_cb(lv_event_t* event);
void close_btn_event_cb(lv_event_t* event);

static int32_t img_ratio_calc(lv_obj_t* img,int32_t scr_width, int32_t scr_height)
{
       int32_t ratio;
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

void add_close_btn(lv_obj_t* obj)
{
       lv_obj_t *close_button = lv_button_create(obj);
       lv_obj_align(close_button, LV_ALIGN_TOP_RIGHT, -20, 10);
       lv_obj_set_style_bg_color(close_button, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
       lv_obj_t *close_button_text = lv_label_create(close_button);
       lv_label_set_text(close_button_text, "X");
       lv_obj_set_style_radius(close_button, 0, 0);

       static lv_style_t close_button_text_style;
       lv_style_init(&close_button_text_style);
       lv_style_set_text_font(&close_button_text_style, &FiraCode_Regular_12);
       lv_obj_add_style(close_button_text, &close_button_text_style, 0);
       lv_style_set_text_color(&close_button_text_style, lv_color_hex(0x06418C));

       lv_obj_add_event_cb(close_button, close_btn_event_cb, LV_EVENT_CLICKED, NULL);
}

void add_title_text(lv_obj_t* obj)
{
       lv_obj_t *title_text = lv_label_create(obj);
       lv_label_set_text(title_text, "HMI SDK Demo Launcher");
       lv_obj_set_pos(title_text, 160, 24);
       static lv_style_t title_text_style;
       lv_style_init(&title_text_style);
       lv_style_set_text_font(&title_text_style, &FiraCode_Regular_28);
       lv_obj_add_style(title_text, &title_text_style, 0);
       lv_style_set_text_color(&title_text_style, lv_color_hex(0xffffff));
}

void add_logo_img(lv_obj_t* obj)
{
       int32_t img_ratio;
       lv_obj_t *logo_image = lv_img_create(obj);
       lv_image_set_src(logo_image,"L:/usr/share/demo-launcher/images/renesas_logomark_white.png");
       lv_obj_set_pos(logo_image, 10, 10);
       lv_obj_update_layout(logo_image);
       img_ratio = img_ratio_calc(logo_image,100, 16);
       lv_obj_set_size(logo_image, 100, 16);
       lv_image_set_scale(logo_image,img_ratio);
}

void add_back_button(lv_obj_t* obj)
{
       lv_obj_t *back_button = lv_button_create(obj);
       lv_obj_align(back_button, LV_ALIGN_TOP_LEFT, 20, 10);
       lv_obj_set_style_bg_color(back_button, lv_color_hex(0xBFBFBF), LV_PART_MAIN);
       lv_obj_add_event_cb(back_button, back_button_event_cb, LV_EVENT_CLICKED, obj);

       lv_obj_t *back_button_text = lv_label_create(back_button);
       lv_label_set_text(back_button_text, "< Back");
       lv_obj_center(back_button_text);
       lv_obj_set_style_radius(back_button, 0, 0);

       static lv_style_t back_button_text_style;
       lv_style_init(&back_button_text_style);
       lv_style_set_text_font(&back_button_text_style, &FiraCode_Regular_12);
       lv_obj_add_style(back_button_text, &back_button_text_style, 0);
       lv_style_set_text_color(&back_button_text_style, lv_color_hex(0xFFFFFF));
}

lv_obj_t* create_app_screen(ui_framework_info_st *ui_framework_info, gchar *select_ui_framework)
{
       int32_t img_ratio;
       lv_obj_t *ret_screen = NULL;
       lv_obj_t *apps_screen = NULL;

#ifndef RUNS_ON_WAYLAND
       ret_screen = lv_obj_create(NULL);
       lv_obj_set_size(ret_screen, lv_pct(100), lv_pct(100));
       lv_obj_set_style_bg_color(ret_screen, lv_color_hex(0x000000), LV_PART_MAIN);
       apps_screen = lv_obj_create(ret_screen);
#else
       apps_screen = lv_obj_create(NULL);
       ret_screen = apps_screen;
#endif
       /*window*/
       lv_obj_set_size(apps_screen, WINDOW_WIDTH, WINDOW_HEIGHT);
       lv_obj_set_align(apps_screen, LV_ALIGN_CENTER);
       lv_obj_set_style_pad_top(apps_screen, 0, LV_PART_MAIN);
       lv_obj_set_style_pad_bottom(apps_screen, 0, LV_PART_MAIN);
       lv_obj_set_style_pad_left(apps_screen, 0, LV_PART_MAIN);
       lv_obj_set_style_pad_right(apps_screen, 0, LV_PART_MAIN);
       lv_obj_set_style_radius(apps_screen, 0, 0);
       lv_obj_set_style_bg_color(apps_screen, lv_color_hex(0x2A289D), LV_PART_MAIN);
       static lv_style_t win_style;
       lv_style_init(&win_style);
       lv_style_set_border_width(&win_style, 0);
       lv_obj_add_style(apps_screen, &win_style, 0);

       add_close_btn(apps_screen);
       add_back_button(apps_screen);
       add_title_text(apps_screen);

       lv_obj_t *guide_text = lv_label_create(apps_screen) ;

       static lv_style_t btn_style;
       lv_style_init(&btn_style);
       lv_style_set_radius(&btn_style, 3);
       lv_style_set_bg_opa(&btn_style, LV_OPA_100);
       lv_style_set_bg_color(&btn_style, lv_color_hex(0xFFFFFF));

       /* btn */
       for (int btn_num = 0; btn_num < ui_framework_info[btn_num].ui_framework_cnt; btn_num++)
       {
              if(g_strcmp0(ui_framework_info[btn_num].ui_framework_name, select_ui_framework) == 0)
              {
                     for(int app_cnt = 0; app_cnt < ui_framework_info[btn_num].apps_info_cnt; app_cnt++)
                     {
                            lv_obj_t *apps_btn = lv_button_create(apps_screen);
                            lv_obj_set_pos(apps_btn, 40, (140 * app_cnt + 80));
                            lv_obj_set_size(apps_btn, 560, 120);
                            lv_obj_add_style(apps_btn, &btn_style, 0);
                            lv_obj_add_event_cb(apps_btn, btn_event_cb, LV_EVENT_CLICKED, &ui_framework_info[btn_num].apps[app_cnt].exe_cmd);

                            /* discription */
                            lv_obj_t *btn_disc =lv_label_create(apps_btn);
                            lv_label_set_text(btn_disc,ui_framework_info[btn_num].apps[app_cnt].discription);
                            lv_obj_set_width(btn_disc, 420);
                            lv_obj_set_height(btn_disc, 90);
                            lv_obj_align(btn_disc, LV_ALIGN_TOP_LEFT, 20, 36);
                            static lv_style_t btn_disc_style;
                            lv_style_init(&btn_disc_style);
                            lv_style_set_text_font(&btn_disc_style, &FiraCode_Regular_24);
                            lv_obj_add_style(btn_disc, &btn_disc_style, 0);
                            lv_style_set_text_color(&btn_disc_style, lv_color_hex(0x06418C));
                     }
              }
       }

       /*Guide_text*/
       lv_label_set_text(guide_text,"Select an application program from the list below.");
       lv_obj_set_pos(guide_text, 50, 56);
       static lv_style_t guide_text_style;
       lv_style_init(&guide_text_style);
       lv_style_set_text_font(&guide_text_style, &FiraCode_Regular_12);
       lv_obj_add_style(guide_text, &guide_text_style, 0);
       lv_style_set_text_color(&guide_text_style, lv_color_hex(0xB9D7FC));

       return ret_screen;
}

lv_obj_t* create_select_ui_framework_screen(int32_t width, int32_t height, ui_framework_info_st *ui_framework_info)
{
       int32_t img_ratio;
       lv_obj_t *ret_screen = NULL;
       lv_obj_t *uf_screen = NULL;

#ifndef RUNS_ON_WAYLAND
       ret_screen = lv_obj_create(NULL);
       lv_obj_set_size(ret_screen, lv_pct(100), lv_pct(100));
       lv_obj_set_style_bg_color(ret_screen, lv_color_hex(0x0000000), LV_PART_MAIN);
       uf_screen = lv_obj_create(ret_screen);
#else
       uf_screen = lv_obj_create(NULL);
       ret_screen = uf_screen;
#endif
       lv_obj_set_size(uf_screen, WINDOW_WIDTH, WINDOW_HEIGHT);
       lv_obj_set_align(uf_screen, LV_ALIGN_CENTER);
       lv_obj_set_style_pad_all(uf_screen, 0, LV_PART_MAIN);
       lv_obj_set_style_border_width(uf_screen, 0, LV_PART_MAIN);
       lv_obj_set_style_radius(uf_screen, 0, LV_PART_MAIN);
       lv_obj_set_size(uf_screen, WINDOW_WIDTH, WINDOW_HEIGHT);
       lv_obj_set_style_bg_color(uf_screen, lv_color_hex(0x2A289D), LV_PART_MAIN);
       static lv_style_t btn_style;
       lv_style_init(&btn_style);
       lv_style_set_radius(&btn_style, 3);
       lv_style_set_bg_opa(&btn_style, LV_OPA_100);
       lv_style_set_bg_color(&btn_style, lv_color_hex(0xFFFFFF));

       lv_obj_t *guide_text = lv_label_create(uf_screen);
       lv_label_set_text(guide_text,"Select an HMI software platform from the option below.");
       lv_obj_set_pos(guide_text, 50, 56);
       static lv_style_t guide_text_style;
       lv_style_init(&guide_text_style);
       lv_style_set_text_font(&guide_text_style, &FiraCode_Regular_12);
       lv_obj_add_style(guide_text, &guide_text_style, 0);
       lv_style_set_text_color(&guide_text_style, lv_color_hex(0xB9D7FC));


       for (int btn_num = 0; btn_num < ui_framework_info[btn_num].ui_framework_cnt; btn_num++)
       {
              lv_obj_t *ui_framework_btn = lv_button_create(uf_screen);
              lv_obj_set_size(ui_framework_btn, 260, 160);
              lv_obj_align(ui_framework_btn, LV_ALIGN_TOP_LEFT, (btn_num % 2) * 300 + 40, (btn_num / 2) * 180 + 100);
              lv_obj_add_style(ui_framework_btn, &btn_style, 0);
              lv_obj_add_event_cb(ui_framework_btn, ui_framework_button_event_cb, LV_EVENT_CLICKED, &ui_framework_info[btn_num]);

              lv_obj_t *icon_img = lv_image_create(ui_framework_btn);
              lv_image_set_src(icon_img,ui_framework_info[btn_num].icon_image_path);
              lv_obj_center(icon_img);
              lv_obj_update_layout(icon_img);
              img_ratio = img_ratio_calc(icon_img,260, 160);
              lv_image_set_scale(icon_img,img_ratio);
       }

       /* add_commmon_parts */
       add_logo_img(uf_screen);
       add_close_btn(uf_screen);
       add_title_text(uf_screen);

       /* screen_load */
       lv_screen_load(ret_screen);

       return ret_screen;
}

void launcher_screen(int32_t width, int32_t height, ui_framework_info_st *ui_framework_info)
{
       lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x000000), LV_PART_MAIN);
       ui_framework_screen = create_select_ui_framework_screen(width, height, ui_framework_info);
}


void back_button_event_cb(lv_event_t* event)
{
       lv_screen_load(ui_framework_screen);
       lv_obj_t *apps_screen = lv_event_get_user_data(event);
       lv_obj_clean(apps_screen);

}

void ui_framework_button_event_cb(lv_event_t* event)
{
       ui_framework_info_st *select_button = lv_event_get_user_data(event);

       lv_obj_t* apps_screen = create_app_screen(select_button, select_button->ui_framework_name);
       lv_screen_load(apps_screen);
}

void btn_event_cb(lv_event_t* event)
{
       gchar *launch_cmd = lv_event_get_user_data(event);
       execlp(launch_cmd,launch_cmd,NULL);
       perror(launch_cmd);
}

void close_btn_event_cb(lv_event_t* event)
{
       _exit(0);
}