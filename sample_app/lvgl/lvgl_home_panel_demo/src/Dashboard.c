#include  "include/Home_Panel_Demo.h"

typedef struct {
	char* name;
    char* artist;
    char* img;
    char* path;
} music_data_t;

lv_obj_t* Image_Gallery_btn;

#ifdef	RUNS_ON_WAYLAND
    lv_obj_t* music_player;
    lv_obj_t* music_num_text;
    lv_obj_t* music_image;
    lv_obj_t* music_name;
    lv_obj_t* music_artist;
    lv_obj_t* loop_btn;
    lv_obj_t* loop_btn_icon;
    lv_obj_t* prev_btn;
    lv_obj_t* prev_btn_icon;
    lv_obj_t* music_state_btn;
    lv_obj_t* music_state_btn_icon;
    lv_obj_t* next_btn;
    lv_obj_t* next_btn_icon;
    lv_obj_t* replay_btn;
    lv_obj_t* replay_btn_icon;
    lv_obj_t* time_slider;
    lv_obj_t* time_text;
    lv_obj_t* end_time_text;
    lv_obj_t* volume_icon;
    lv_obj_t* volume_slider;
    lv_obj_t* volume_value_label;
    bool music_state = 0;
    bool loop_state = 0;
    bool music_end_state = 0;
    GstElement* pipeline;
    GstElement* audio;
    GMainLoop *loop;
    GstElement *src, *dec, *conv, *sink, *volume;
    double volume_value = 1.0;
    double music_time;
    gint64 music_pos; 
    gint64 music_len;
    struct tm tm;
    GstPad *audiopad;
    GstBus *bus;
    char music_num;
    music_data_t music_list[3] = {
        {"Downtown Boogie", "Bryan Teoh", "L:/usr/share/lvgl-home-panel-demo/images/Downtown Boogie.png", "/usr/share/lvgl-home-panel-demo/music/Downtown Boogie.mp3"},
        {"Martini Sunset", "Anonymous", "L:/usr/share/lvgl-home-panel-demo/images/Martini Sunset.png", "/usr/share/lvgl-home-panel-demo/music/Martini Sunset.mp3"},
        {"Trip Up North", "Bryan Teoh", "L:/usr/share/lvgl-home-panel-demo/images/Trip Up North.png", "/usr/share/lvgl-home-panel-demo/music/Trip Up North.mp3"}
    };
#endif

static void Image_Gallery_btn_cb(lv_event_t* e);
static void Home_Automation_btn_cb(lv_event_t* e);
static void Weather_History_btn_cb(lv_event_t* e);
#ifdef	RUNS_ON_WAYLAND
    static void music_state_event_click_cb(lv_event_t * e);
    static void prev_click_event_cb(lv_event_t * e);
    static void next_click_event_cb(lv_event_t * e);
    static void music_setup(char *music_pass);
    static void music_replay_btn_click_cb(lv_event_t * e);
    static void music_volume_event_cb(lv_event_t* e);
    static void cb_newpad (GstElement *decodebin, GstPad *pad, gpointer data);
    static void music_time_event_click_cb(lv_event_t * e);
    static void music_seek_cb(lv_event_t * e);
    static void music_loop_btn_click_cb(lv_event_t * e);
    void cb_print_position(void);
    LV_IMG_DECLARE(music_btn_loop_off_icon);
    LV_IMG_DECLARE(music_btn_loop_on_icon);
    LV_IMG_DECLARE(music_btn_next_icon);
    LV_IMG_DECLARE(music_btn_prev_icon);
    LV_IMG_DECLARE(music_btn_pause_icon);
    LV_IMG_DECLARE(music_btn_replay_icon);
    LV_IMG_DECLARE(music_volume_icon);
#endif
LV_IMG_DECLARE(Home_btn_icon);
LV_IMG_DECLARE(Image_btn_icon);
LV_IMG_DECLARE(Weather_btn_icon);

void create_Dashboard(void)
{
    //Create_Dashboard_background
    lv_obj_t *Dashboard_background = lv_obj_create(Dashboard);
    lv_obj_set_size(Dashboard_background, background_width, background_height);
    lv_obj_align(Dashboard_background, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_style_pad_all(Dashboard_background, 0, 0);
    lv_obj_set_style_border_width(Dashboard_background, 0, 0);
    lv_obj_set_style_outline_width(Dashboard_background, 0, 0);

    header_background = lv_obj_create(Dashboard_background);
    lv_obj_set_size(header_background, background_width, 79);
    lv_obj_set_style_bg_color(header_background, lv_color_hex(0xE3E1FF), 0);

    header_logo = lv_img_create(header_background);
    lv_img_set_src(header_logo, "L:/usr/share/lvgl-home-panel-demo/images/renesas_logomark_blue.png");
    lv_obj_update_layout(header_logo);
    logo_ratio = img_ratio_calc(header_logo, 237, 30);
    lv_img_set_zoom(header_logo, logo_ratio);
    lv_obj_center(header_logo);

    //Create_Image_Gallery_btn
    Image_Gallery_btn = lv_btn_create(Dashboard_background);
    lv_obj_set_size(Image_Gallery_btn, 437, 463);
    lv_obj_set_pos(Image_Gallery_btn, 712, 180);
    lv_obj_set_style_bg_color(Image_Gallery_btn, lv_color_hex(0x8F92F6), 0);
    lv_obj_set_style_pad_all(Image_Gallery_btn, 0, 0);
    lv_obj_set_style_border_width(Image_Gallery_btn, 0, 0);
    lv_obj_set_style_outline_width(Image_Gallery_btn, 0, 0);
    lv_obj_t* Image_Gallery_btn_text = lv_label_create(Image_Gallery_btn);
    lv_obj_align(Image_Gallery_btn_text, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_label_set_text(Image_Gallery_btn_text, "Image Gallery");
    lv_obj_set_style_bg_color(Image_Gallery_btn_text, lv_color_hex(0xDDDDDD), 0);
    lv_obj_add_event_cb(Image_Gallery_btn, Image_Gallery_btn_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t* Image_Gallery_btn_icon = lv_img_create(Image_Gallery_btn);
    lv_obj_center(Image_Gallery_btn_icon);
    lv_img_set_src(Image_Gallery_btn_icon, &Image_btn_icon);

    //Home_Automation_btn
    lv_obj_t* Home_Automation_btn = lv_btn_create(Dashboard_background);
    lv_obj_set_size(Home_Automation_btn, 438, 463);
    lv_obj_set_pos(Home_Automation_btn, 1166, 180);
    lv_obj_set_style_bg_color(Home_Automation_btn, lv_color_hex(0x8F92F6), 0);
    lv_obj_set_style_pad_all(Home_Automation_btn, 0, 0);
    lv_obj_set_style_border_width(Home_Automation_btn, 0, 0);
    lv_obj_set_style_outline_width(Home_Automation_btn, 0, 0);

    lv_obj_t* Home_Automation_btn_text = lv_label_create(Home_Automation_btn);
    lv_obj_align(Home_Automation_btn_text, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_label_set_text(Home_Automation_btn_text, "Home Automation");
    lv_obj_set_style_bg_color(Home_Automation_btn_text, lv_color_hex(0xDDDDDD), 0);
    lv_obj_add_event_cb(Home_Automation_btn, Home_Automation_btn_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t* Home_Automation_btn_icon = lv_img_create(Home_Automation_btn);
    lv_img_set_src(Home_Automation_btn_icon, &Home_btn_icon);
    lv_obj_center(Home_Automation_btn_icon);

    //Weather_History_btn
    lv_obj_t* Weather_History_btn = lv_btn_create(Dashboard_background);
    lv_obj_set_size(Weather_History_btn, 551, 319);
    lv_obj_set_pos(Weather_History_btn, 712, 660);
    lv_obj_set_style_bg_color(Weather_History_btn, lv_color_hex(0xE9ECEF), 0);
    lv_obj_set_style_pad_all(Weather_History_btn, 0, 0);
    lv_obj_set_style_border_width(Weather_History_btn, 0, 0);
    lv_obj_set_style_outline_width(Weather_History_btn, 0, 0);
    lv_obj_add_event_cb(Weather_History_btn, Weather_History_btn_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t* Weather_History_btn_icon = lv_img_create(Weather_History_btn);
    lv_obj_center(Weather_History_btn_icon);
    lv_img_set_src(Weather_History_btn_icon, &Weather_btn_icon);

#ifdef	RUNS_ON_WAYLAND
    //music_palyer
    music_player = lv_obj_create(Dashboard_background);
    lv_obj_set_size(music_player, 438, 799);
    lv_obj_set_pos(music_player, 257, 180);
    lv_obj_set_style_bg_color(music_player, lv_color_hex(0xCED4DA), 0);
    lv_obj_set_style_pad_all(music_player, 0, 0);
    lv_obj_set_style_border_width(music_player, 0, 0);
    lv_obj_set_style_outline_width(music_player, 0, 0); 
    

    music_num_text = lv_label_create(music_player);
    lv_obj_align(music_num_text, LV_ALIGN_CENTER, 0, -296);
    lv_obj_set_style_bg_color(music_num_text, lv_color_hex(0x213547), 0);
    lv_label_set_text(music_num_text, "playing 1 of 3");

    music_image = lv_img_create(music_player);
    lv_obj_update_layout(music_image);
    lv_obj_align(music_image, LV_ALIGN_CENTER, 0, -180);
    lv_img_set_src(music_image, music_list[0].img);

    music_name = lv_label_create(music_player);
    lv_obj_align(music_name, LV_ALIGN_CENTER, 0, -40);
    lv_obj_set_style_bg_color(music_name, lv_color_hex(0x213547), 0);
    lv_label_set_text(music_name, music_list[0].name);

    music_artist = lv_label_create(music_player);
    lv_obj_center(music_artist);
    lv_obj_set_style_bg_color(music_artist, lv_color_hex(0x213547), 0);
    lv_label_set_text(music_artist, music_list[0].artist);

    loop_btn = lv_btn_create(music_player);
    lv_obj_set_pos(loop_btn, 68, 596);
    lv_obj_set_style_bg_color(loop_btn, lv_color_hex(0xCED4DA), 0);
    lv_obj_set_style_pad_all(loop_btn, 0, 0);
    lv_obj_set_style_border_width(loop_btn, 0, 0);
    lv_obj_set_style_outline_width(loop_btn, 0, 0);
    lv_obj_add_event_cb(loop_btn, music_loop_btn_click_cb, LV_EVENT_CLICKED, NULL);

    loop_btn_icon = lv_img_create(loop_btn);
    lv_img_set_src(loop_btn_icon, &music_btn_loop_off_icon);

    prev_btn = lv_btn_create(music_player);
    lv_obj_set_pos(prev_btn, 134, 596);
    lv_obj_set_style_bg_color(prev_btn, lv_color_hex(0xCED4DA), 0);
    lv_obj_set_style_pad_all(prev_btn, 0, 0);
    lv_obj_set_style_border_width(prev_btn, 0, 0);
    lv_obj_set_style_outline_width(prev_btn, 0, 0);
    lv_obj_set_style_border_width(prev_btn, 0, 0);
    lv_obj_add_event_cb(prev_btn, prev_click_event_cb, LV_EVENT_CLICKED, NULL);

    prev_btn_icon = lv_img_create(prev_btn);
    lv_img_set_src(prev_btn_icon, &music_btn_prev_icon);

    music_state_btn = lv_btn_create(music_player);
    lv_obj_set_pos(music_state_btn,192, 596);
    lv_obj_set_style_bg_color(music_state_btn, lv_color_hex(0xCED4DA), 0);
    lv_obj_set_style_pad_all(music_state_btn, 0, 0);
    lv_obj_set_style_border_width(music_state_btn, 0, 0);
    lv_obj_set_style_outline_width(music_state_btn, 0, 0);
    lv_obj_add_event_cb(music_state_btn, music_state_event_click_cb, LV_EVENT_CLICKED, NULL);

    music_state_btn_icon = lv_img_create(music_state_btn);
    lv_img_set_src(music_state_btn_icon, &music_btn_play_icon);

    next_btn = lv_btn_create(music_player);
    lv_obj_set_pos(next_btn, 250, 596);
    lv_obj_set_style_bg_color(next_btn, lv_color_hex(0xCED4DA), 0);
    lv_obj_set_style_pad_all(next_btn, 0, 0);
    lv_obj_set_style_border_width(next_btn, 0, 0);
    lv_obj_set_style_outline_width(next_btn, 0, 0);
    lv_obj_add_event_cb(next_btn, next_click_event_cb, LV_EVENT_CLICKED, NULL);

    next_btn_icon = lv_img_create(next_btn);
    lv_img_set_src(next_btn_icon, &music_btn_next_icon);

    replay_btn = lv_btn_create(music_player);
    lv_obj_set_pos(replay_btn, 316, 596);
    lv_obj_set_style_bg_color(replay_btn, lv_color_hex(0xCED4DA), 0);
    lv_obj_set_style_pad_all(replay_btn, 0, 0);
    lv_obj_set_style_border_width(replay_btn, 0, 0);
    lv_obj_set_style_outline_width(replay_btn, 0, 0);
    lv_obj_add_event_cb(replay_btn, music_replay_btn_click_cb, LV_EVENT_CLICKED, NULL);

    replay_btn_icon = lv_img_create(replay_btn);
    lv_img_set_src(replay_btn_icon, &music_btn_replay_icon);

    time_slider = lv_slider_create(music_player);
    lv_obj_set_width(time_slider, 231);
    lv_obj_set_height(time_slider, 6);
    lv_obj_set_pos(time_slider, 103, 476);
    lv_obj_add_event_cb(time_slider, music_seek_cb, LV_EVENT_VALUE_CHANGED, NULL);

    time_text = lv_label_create(music_player);
    lv_obj_set_pos(time_text, 28, 472);
    lv_label_set_text(time_text, "00:00:00");

    end_time_text = lv_label_create(music_player);
    lv_obj_set_pos(end_time_text, 349, 472);
    lv_label_set_text(end_time_text, "00:00:00");

    volume_icon = lv_img_create(music_player);
    lv_obj_set_pos(volume_icon, 31, 522);
    lv_img_set_src(volume_icon, &music_volume_icon);

    volume_slider = lv_slider_create(music_player);
    lv_obj_set_width(volume_slider, 295);
    lv_obj_set_height(volume_slider, 6);
    lv_obj_set_pos(volume_slider, 71, 533);
    lv_slider_set_range(volume_slider, 0, 20);
    lv_slider_set_value(volume_slider, 10, 0);
    lv_obj_add_event_cb(volume_slider, music_volume_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    volume_value_label =lv_label_create(music_player);
    lv_obj_set_pos(volume_value_label, 376, 529);
    lv_label_set_text(volume_value_label, "50");

    music_num = 0;
    music_setup(music_list[music_num].path);
#endif
}

static void Image_Gallery_btn_cb(lv_event_t* e)
{
    lv_event_send(Image_Gallery_cont, LV_EVENT_CLICKED, NULL);
}

static void Home_Automation_btn_cb(lv_event_t* e)
{
    lv_event_send(Home_Automation_cont, LV_EVENT_CLICKED, NULL);
}

static void Weather_History_btn_cb(lv_event_t* e)
{
    lv_event_send(Weather_History_cont, LV_EVENT_CLICKED, NULL);
}

#ifdef	RUNS_ON_WAYLAND
    static void prev_click_event_cb(lv_event_t * e)
    {

        if(music_num == 0) 
        {
            music_num = 2;
        }
        else
        {
            music_num--;
        }
        gst_element_set_state (pipeline, GST_STATE_NULL);
        music_setup(music_list[music_num].path);
        gst_element_set_state (pipeline, GST_STATE_PLAYING);
        lv_img_set_src(music_state_btn_icon, &music_btn_pause_icon);
        lv_label_set_text_fmt(music_num_text, "playing %d of 3", music_num + 1);
        lv_img_set_src(music_image, music_list[music_num].img);
        lv_label_set_text(music_name, music_list[music_num].name);
        lv_label_set_text(music_artist, music_list[music_num].artist);
        music_state = 1;  
    }

    static void next_click_event_cb(lv_event_t * e)
    {
        if(music_num < 2)
        {
            music_num++;
        }
        else
        {
            music_num = 0;
        }
        gst_element_set_state (pipeline, GST_STATE_NULL);
        music_setup(music_list[music_num].path);
        gst_element_set_state (pipeline, GST_STATE_PLAYING);
        lv_img_set_src(music_state_btn_icon, &music_btn_pause_icon);
        lv_label_set_text_fmt(music_num_text, "playing %d of 3", music_num + 1);
        lv_img_set_src(music_image, music_list[music_num].img);
        lv_label_set_text(music_name, music_list[music_num].name);
        lv_label_set_text(music_artist, music_list[music_num].artist);
        music_state = 1;
    }

    static void music_setup(char *music_pass)
    {

        //init GStreamer
        gst_init (NULL, NULL);
        loop = g_main_loop_new (NULL, FALSE);

        //setup
        pipeline = gst_pipeline_new ("pipeline");

        bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
        gst_object_unref (bus);

        src = gst_element_factory_make ("filesrc", "source");
        g_object_set (G_OBJECT (src), "location", music_pass, NULL);
        dec = gst_element_factory_make ("decodebin", "decoder");
        g_signal_connect (dec, "pad-added", G_CALLBACK (cb_newpad), NULL);
        gst_bin_add_many (GST_BIN (pipeline), src, dec, NULL);

        //create audio output
        audio = gst_bin_new ("audiobin");
        conv = gst_element_factory_make ("audioconvert", "aconv");
        audiopad = gst_element_get_static_pad (conv, "sink");
        sink = gst_element_factory_make ("alsasink", "sink");
        volume = gst_element_factory_make("volume", "volume");
        g_object_set(G_OBJECT(volume), "volume", 1.0, NULL);
        gst_bin_add_many (GST_BIN (audio), conv, volume, sink, NULL);
        gst_element_link (conv, volume);
        gst_element_link (volume, sink);
        gst_element_link_many(src, dec, conv, volume, sink, NULL);  
        gst_element_add_pad (audio,
        gst_ghost_pad_new ("sink", audiopad));
        gst_object_unref (audiopad);
        gst_bin_add (GST_BIN (pipeline), audio);

        //run
        gst_element_set_state (pipeline, GST_STATE_PAUSED);
    }

    static void cb_newpad (GstElement *decodebin, GstPad *pad, gpointer data)
    {
        GstCaps *caps;
        GstStructure *str;
        GstPad *audiopad;

        //only link once
        audiopad = gst_element_get_static_pad (audio, "sink");
        if (GST_PAD_IS_LINKED (audiopad)) 
        {
            g_object_unref (audiopad);
            return;
        }

        //check media type
        caps = gst_pad_query_caps (pad, NULL);
        str = gst_caps_get_structure (caps, 0);
        if (!g_strrstr (gst_structure_get_name (str), "audio"))
        {
            gst_caps_unref (caps);
            gst_object_unref (audiopad);
            return;
        }
        gst_caps_unref (caps);

        //link'n'play
        gst_pad_link (pad, audiopad);

        g_object_unref (audiopad);
    }

    static void music_state_event_click_cb(lv_event_t * e)
    {
        if(music_state == 0) //music_stop
        {
            lv_img_set_src(music_state_btn_icon, &music_btn_pause_icon);
            gst_element_set_state (pipeline, GST_STATE_PLAYING);
            music_state = 1;
        }
        else if(music_state == 1) //music_play
        {
            lv_img_set_src(music_state_btn_icon, &music_btn_play_icon);
            gst_element_set_state (pipeline, GST_STATE_PAUSED);
            music_state = 0;
            g_object_set(G_OBJECT(volume), "volume", volume_value, NULL);
        }
    }

    static void music_replay_btn_click_cb(lv_event_t * e)
    {
        gst_element_seek_simple(pipeline, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH , 0 * GST_SECOND); 
    }

    static void music_loop_btn_click_cb(lv_event_t * e)
    {
        if(loop_state == 0) //loop_disable
        {
            lv_img_set_src(loop_btn_icon, &music_btn_loop_on_icon);
            loop_state = 1;
        }
        else if(loop_state == 1) //loop_enable
        {
            lv_img_set_src(loop_btn_icon, &music_btn_loop_off_icon);
            loop_state = 0;
        }
    }

    static void music_volume_event_cb(lv_event_t* e)
    {
        lv_obj_t* obj = lv_event_get_target(e);
        char volume_set_value = 50;
        double volume_slider_value = 1;    

        volume_slider_value = lv_slider_get_value(obj);
        volume_value = volume_slider_value / 10; 
        g_object_set(G_OBJECT(volume), "volume", volume_value, NULL);
        lv_label_set_text_fmt(volume_value_label, "%d", (int)volume_slider_value * 5);
    }

    static void music_seek_cb(lv_event_t * e)
    {
        gint64 select_pos;
        gint64 select_pos_time;
        select_pos = lv_slider_get_value(time_slider);
        select_pos_time = (double)music_len * ((double)select_pos / 100); 
        gst_element_seek_simple(pipeline, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH , select_pos_time * GST_NSECOND);
    }

    void cb_print_position(void)
    {
        if (gst_element_query_position (pipeline, GST_FORMAT_TIME, &music_pos)
        && gst_element_query_duration (pipeline, GST_FORMAT_TIME, &music_len))
        {
            music_time =  ((double)music_pos / (double)music_len)*100 +0.1;
            lv_slider_set_value(time_slider, (int)music_time, 0);
            lv_label_set_text_fmt(time_text, "%" GST_TIME_FORMAT "\n", GST_TIME_ARGS(music_pos));
            lv_label_set_text_fmt(end_time_text, "%" GST_TIME_FORMAT "\n", GST_TIME_ARGS(music_len));

            if(loop_state == 1 && music_time >= 100)
            {
                if(music_num == 2)
                {
                    music_num = 0;
                    gst_element_set_state (pipeline, GST_STATE_NULL);
                    music_setup(music_list[music_num].path);
                    gst_element_set_state (pipeline, GST_STATE_PLAYING);
                    lv_img_set_src(music_state_btn_icon, &music_btn_pause_icon);
                    lv_label_set_text_fmt(music_num_text, "playing %d of 3", music_num + 1);
                    lv_img_set_src(music_image, music_list[music_num].img);
                    lv_label_set_text(music_name, music_list[music_num].name);
                    lv_label_set_text(music_artist, music_list[music_num].artist);
                    music_state = 1;
                }
                else
                {
                    music_num++;
                    gst_element_set_state (pipeline, GST_STATE_NULL);
                    music_setup(music_list[music_num].path);
                    gst_element_set_state (pipeline, GST_STATE_PLAYING);
                    lv_img_set_src(music_state_btn_icon, &music_btn_pause_icon);
                    lv_label_set_text_fmt(music_num_text, "playing %d of 3", music_num + 1);
                    lv_img_set_src(music_image, music_list[music_num].img);
                    lv_label_set_text(music_name, music_list[music_num].name);
                    lv_label_set_text(music_artist, music_list[music_num].artist);
                }
            }
        }
    }
#endif
