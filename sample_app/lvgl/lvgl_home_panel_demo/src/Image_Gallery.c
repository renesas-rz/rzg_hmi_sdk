#include  "include/Home_Panel_Demo.h"

lv_obj_t* Image;
lv_obj_t* after_Image;
lv_obj_t* select_Image_btn[4];
lv_obj_t* select_Image[4];

static void animation_event_handler(lv_event_t* e);

void create_Image_Gallery(void)
{
    lv_obj_t* Image_Gallery_background = lv_obj_create(Image_Gallery);
    lv_obj_set_style_pad_all(Image_Gallery_background, 0, 0);
    lv_obj_set_style_border_width(Image_Gallery_background, 0, 0);
    lv_obj_set_style_outline_width(Image_Gallery_background, 0, 0);
    lv_obj_align(Image_Gallery_background, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_size(Image_Gallery_background, background_width, background_height);

    header_background = lv_obj_create(Image_Gallery_background);
    lv_obj_set_style_bg_color(header_background, lv_color_hex(0xE3E1FF), 0);
    lv_obj_set_size(header_background, background_width, 79);

    header_logo = lv_image_create(header_background);
    lv_image_set_src(header_logo, "L:/usr/share/lvgl-home-panel-demo/images/renesas_logomark_blue.png");
    lv_image_set_scale(header_logo, logo_ratio);
    lv_obj_center(header_logo);

    char Image_btn_cnt = 0;
    int32_t img_ratio = 0;
    static lv_style_t image_btn_style;
    lv_style_init(&image_btn_style);
    lv_style_set_radius(&image_btn_style, 0);

    Image = lv_image_create(Image_Gallery_background);
    lv_obj_set_pos(Image, 564, 344);
    lv_obj_set_size(Image, 959, 539);
    lv_image_set_src(Image, "L:/usr/share/lvgl-home-panel-demo/images/photo_0.jpg");

    after_Image = lv_image_create(Image_Gallery_background);
    lv_obj_set_pos(after_Image, 564, 344);
    lv_obj_set_size(after_Image, 959, 539);

    for (Image_btn_cnt = 0; Image_btn_cnt < 4; Image_btn_cnt++)
    {
        select_Image_btn[Image_btn_cnt] = lv_button_create(Image_Gallery_background);
        select_Image[Image_btn_cnt] = lv_image_create(select_Image_btn[Image_btn_cnt]);
        lv_obj_set_pos(select_Image_btn[Image_btn_cnt], 338, (344 + ((119+20) * Image_btn_cnt)));
        
        lv_obj_set_size(select_Image_btn[Image_btn_cnt], 209, 119);
        lv_obj_set_style_pad_all(select_Image_btn[Image_btn_cnt], 0, 0);
        lv_obj_set_style_border_width(select_Image_btn[Image_btn_cnt], 0, 0);
        lv_obj_set_style_outline_width(select_Image_btn[Image_btn_cnt], 0, 0);
        lv_obj_add_style(select_Image_btn[Image_btn_cnt], &image_btn_style, 0);
    }

    lv_image_set_src(select_Image[0], "L:/usr/share/lvgl-home-panel-demo/images/photo_0.png");
    lv_image_set_src(select_Image[1], "L:/usr/share/lvgl-home-panel-demo/images/photo_1.png");
    lv_image_set_src(select_Image[2], "L:/usr/share/lvgl-home-panel-demo/images/photo_2.png");
    lv_image_set_src(select_Image[3], "L:/usr/share/lvgl-home-panel-demo/images/photo_3.png");

    for (Image_btn_cnt = 0; Image_btn_cnt < 4; Image_btn_cnt++)
    {
        lv_obj_set_pos(select_Image[Image_btn_cnt], 0, 0);
        lv_obj_update_layout(select_Image[Image_btn_cnt]);
        img_ratio = img_ratio_calc(select_Image[Image_btn_cnt], 209, 119);
        lv_obj_set_size(select_Image[Image_btn_cnt], 209, 119);
        lv_image_set_scale(select_Image[Image_btn_cnt],img_ratio);
        lv_obj_set_style_pad_all(select_Image[Image_btn_cnt], 0, 0);
        lv_obj_set_style_border_width(select_Image[Image_btn_cnt], 0, 0);
        lv_obj_set_style_outline_width(select_Image[Image_btn_cnt], 0, 0);

        lv_obj_add_event_cb(select_Image_btn[Image_btn_cnt], animation_event_handler, LV_EVENT_CLICKED, select_Image[Image_btn_cnt]);
    }
}

static void animation_event_handler(lv_event_t* e)
{
    lv_obj_t* after_Image = Image;
    lv_obj_t* select_Image;
    char select_Image_pass[255] = "\n";
    select_Image = lv_event_get_user_data(e);
    strcpy(select_Image_pass, lv_image_get_src(select_Image));
    char pass_length = strlen(select_Image_pass);

    char file_name_length = (pass_length-4);
    sprintf(select_Image_pass+file_name_length, ".jpg");
    lv_obj_fade_out(Image, 2000, 2000);
    lv_image_set_src(Image, select_Image_pass);
    lv_obj_fade_in(Image, 1000, 1000);
}