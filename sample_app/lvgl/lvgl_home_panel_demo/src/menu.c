#include  "include/Home_Panel_Demo.h"

lv_obj_t* Image_Gallery;
lv_obj_t* Image_Gallery_section;
lv_obj_t* Image_Gallery_cont;
lv_obj_t* Dashboard;
lv_obj_t* Dashboard_section;
lv_obj_t* Dashboard_cont;
lv_obj_t* Home_Automation;
lv_obj_t* Home_Automation_section;
lv_obj_t* Home_Automation_cont;
lv_obj_t* Weather_History;
lv_obj_t* Weather_History_section;
lv_obj_t* Weather_History_cont;
lv_obj_t* tab;

lv_obj_t* menu;
bool sidebar_state = 1;

static void back_event_handler(lv_event_t* e);
int32_t img_ratio_calc(lv_obj_t* img,int32_t scr_width, int32_t scr_height);

#ifdef	RUNS_ON_WAYLAND
    static void music_stop_cb(lv_event_t * e);
#endif

/* Image */
LV_IMG_DECLARE(Dashboard_icon);
LV_IMG_DECLARE(Home_Automation_icon);
LV_IMG_DECLARE(Image_Gallery_icon);
LV_IMG_DECLARE(Weather_History_icon);

void create_menu()
{
    menu = lv_menu_create(lv_screen_active());

    lv_menu_set_mode_root_back_button(menu, LV_MENU_ROOT_BACK_BUTTON_ENABLED);
    lv_obj_add_event_cb(menu, back_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_size(menu, lv_pct(100), lv_pct(100));
    lv_obj_set_flex_flow(menu, LV_FLEX_FLOW_ROW_REVERSE);

    /* declare vars */
    lv_obj_t* cont;
    lv_obj_t* section;
    lv_obj_t* label;

    /* create sidebar */
    lv_obj_t* sidebar = lv_menu_page_create(menu, NULL);
    lv_menu_set_sidebar_page(menu, sidebar);
    lv_obj_set_align(menu, LV_ALIGN_TOP_RIGHT);
    lv_obj_set_align(sidebar, LV_ALIGN_TOP_RIGHT);
    lv_obj_set_style_bg_color(menu, lv_color_hex(0x2F419A), 0);
    lv_obj_move_background(menu);

    /* style */
    static lv_style_t tag_text_style;
    lv_style_init(&tag_text_style);
    lv_style_set_text_color(&tag_text_style, lv_color_hex(0xF9F8FF));

    /* create sidebar element for sidebar */
    section = lv_menu_section_create(sidebar);
    lv_obj_set_style_bg_color(section, lv_color_hex(0x2F419A), 0);

    /* set sidebar */
    tab = lv_obj_get_parent(sidebar);
    lv_obj_set_width(tab, 57);
    lv_obj_send_event(lv_obj_get_child(lv_obj_get_child(lv_menu_get_cur_sidebar_page(menu), 0), 0), LV_EVENT_CLICKED, NULL);

    /* create sub page for item Dashboard */
    Dashboard = lv_menu_page_create(menu, NULL);

    /* create sidebar element for Dashboard */
    Dashboard_section = lv_menu_section_create(sidebar);
    Dashboard_cont = lv_menu_cont_create(Dashboard_section);
    lv_obj_set_style_bg_color(Dashboard_section, lv_color_hex(0x2F419A), 0);

    lv_obj_t* Dashboard_tag_icon = lv_image_create(Dashboard_cont);
    lv_image_set_src(Dashboard_tag_icon, &Dashboard_icon);

    lv_obj_t* Dashboard_tag_text = lv_label_create(Dashboard_cont);
    lv_label_set_text(Dashboard_tag_text, "Dashboard");
    lv_obj_add_style(Dashboard_tag_text, &tag_text_style, 0);

    lv_menu_set_load_page_event(menu, Dashboard_cont, Dashboard);
    lv_obj_send_event(Dashboard_cont, LV_EVENT_CLICKED, NULL);

    /* Image_Gallery_menu */
    Image_Gallery = lv_menu_page_create(menu, NULL);

    /* create sidebar element for Image_Gallery */
    Image_Gallery_section = lv_menu_section_create(sidebar);
    Image_Gallery_cont = lv_menu_cont_create(Image_Gallery_section);
    lv_obj_set_style_bg_color(Image_Gallery_section, lv_color_hex(0x2F419A), 0);

    lv_obj_t* Image_Gallery_tag_icon = lv_image_create(Image_Gallery_cont);
    lv_image_set_src(Image_Gallery_tag_icon, &Image_Gallery_icon);

    lv_obj_t* Image_Gallery_tag_text = lv_label_create(Image_Gallery_cont);
    lv_obj_set_x(Image_Gallery_tag_text, 60);
    lv_label_set_text(Image_Gallery_tag_text, "Image Gallery");
    lv_obj_add_style(Image_Gallery_tag_text, &tag_text_style, 0);
    lv_menu_set_load_page_event(menu, Image_Gallery_cont, Image_Gallery);

    /* Home_Automation_menu */
    Home_Automation = lv_menu_page_create(menu, NULL);

    /* create sidebar element for Home_Automation */
    Home_Automation_section = lv_menu_section_create(sidebar);
    Home_Automation_cont = lv_menu_cont_create(Home_Automation_section);
    lv_obj_set_style_bg_color(Home_Automation_section, lv_color_hex(0x2F419A), 0);

    lv_obj_t* Home_Automation_tag_icon = lv_image_create(Home_Automation_cont);
    lv_image_set_src(Home_Automation_tag_icon, &Home_Automation_icon);

    lv_obj_t* Home_Automation_tag_text = lv_label_create(Home_Automation_cont);
    lv_label_set_text(Home_Automation_tag_text, "Home Automation");
    lv_obj_add_style(Home_Automation_tag_text, &tag_text_style, 0);

    lv_menu_set_load_page_event(menu, Home_Automation_cont, Home_Automation);

    /* Weather_History_menu */
    Weather_History = lv_menu_page_create(menu, NULL);

    /* create sidebar element for Weather_History */
    Weather_History_section = lv_menu_section_create(sidebar);
    Weather_History_cont = lv_menu_cont_create(Weather_History_section);

    lv_obj_set_style_bg_color(Weather_History_section, lv_color_hex(0x2F419A), 0);

    lv_obj_t* Weather_History_tag_icon = lv_image_create(Weather_History_cont);
    lv_image_set_src(Weather_History_tag_icon, &Weather_History_icon);

    lv_obj_t* Weather_History_tag_text = lv_label_create(Weather_History_cont);
    lv_label_set_text(Weather_History_tag_text, "Weather History");
    lv_obj_add_style(Weather_History_tag_text, &tag_text_style, 0);

    lv_menu_set_load_page_event(menu, Weather_History_cont, Weather_History);

    /* Version_text */
    static lv_style_t ver_obj_style;
    lv_style_init(&ver_obj_style);

    lv_obj_t* ver_obj = lv_obj_create(sidebar);

    lv_obj_update_layout(ver_obj);
    int y = lv_obj_get_y(ver_obj);
    int space_y = background_height - y - 50;
    lv_obj_set_size(ver_obj, 320, space_y);
    lv_obj_align(ver_obj, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_add_style(ver_obj, &ver_obj_style, 0);
    lv_obj_set_style_pad_all(ver_obj, 0, 0);
    lv_obj_set_style_border_width(ver_obj, 0, 0);
    lv_obj_set_style_outline_width(ver_obj, 0, 0);
    lv_obj_set_style_bg_color(ver_obj, lv_color_hex(0x2F419A), 0);

    lv_obj_t* Version_text = lv_label_create(ver_obj);
    lv_label_set_text(Version_text, "Ver.2.00");
    lv_obj_add_style(Version_text, &tag_text_style, 0);
    lv_obj_update_layout(ver_obj);
    lv_obj_align(Version_text, LV_ALIGN_BOTTOM_RIGHT, 0, 0);

    img_ratio_calc(lv_screen_active(), 1280,720);

#ifdef	RUNS_ON_WAYLAND
    lv_obj_add_event_cb(Dashboard_cont, music_stop_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(Image_Gallery_cont, music_stop_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(Home_Automation_cont, music_stop_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(Weather_History_cont, music_stop_cb, LV_EVENT_CLICKED, NULL);
#endif
}

static void back_event_handler(lv_event_t* e)
{
    /* sidebar_Open */
    if (sidebar_state == 0)
    {
        lv_obj_set_width(tab, 57);
        sidebar_state = 1;
    }
    /* sidebar_Close */
    else if (sidebar_state == 1)
    {
        lv_obj_set_width(tab, 320);
        sidebar_state = 0;
    }
}

int32_t img_ratio_calc(lv_obj_t* img,int32_t scr_width, int32_t scr_height)
{
    int32_t ratio;
    int32_t img_width;
    int32_t img_height;
    int32_t img_obj_width = lv_obj_get_width(img);
    int32_t img_obj_height = lv_obj_get_height(img);

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

#ifdef	RUNS_ON_WAYLAND
    static void music_stop_cb(lv_event_t * e)
    {
        gst_element_set_state (pipeline, GST_STATE_NULL);
        music_state = 0;
        lv_image_set_src(music_state_btn_icon, &music_btn_play_icon);
        lv_label_set_text(time_text, "00:00:00");
    }
#endif
