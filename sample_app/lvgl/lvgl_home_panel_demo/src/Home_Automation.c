#include  "include/Home_Panel_Demo.h"

lv_obj_t* arc;
lv_obj_t* Light1_sw;
lv_obj_t* Light1_icon;
lv_obj_t* WiFi_sw;
lv_obj_t* WiFi_icon;
lv_obj_t* Light2_sw;
lv_obj_t* Light2_icon;
lv_obj_t* TV_sw;
lv_obj_t* TV_icon;
lv_obj_t* Air_Conditioner_sw;
lv_obj_t* meter;
lv_obj_t* Air_Conditioner_meter;
lv_obj_t* Air_Conditioner_set_arc;
static lv_style_t Air_Conditioner_ON_style;
static lv_style_t Air_Conditioner_OFF_style;
lv_obj_t* Air_Conditioner_set_value_label;
lv_obj_t* Air_Conditioner_set_humidity_slider;
lv_obj_t* Air_Conditioner_set_humidity_value_label;
lv_obj_t* Air_Conditioner_set_wind_slider;
lv_obj_t* Air_Conditioner_set_wind_value_label;
lv_style_t Air_Conditioner_humidity_ON_style;
lv_style_t Air_Conditioner_slider_OFF_style;
lv_obj_t* Air_Conditioner_set_wind_slider;
lv_style_t Air_Conditioner_wind_ON_style;

bool Air_Conditioner_state = 0;
bool light1_state = 0;
bool WiFi_state = 0;
bool Light2_state = 0;
bool TV_state = 0;


static void Light1_event_handler(lv_event_t* e);
static void WiFi_event_handler(lv_event_t* e);
static void Light2_event_handler(lv_event_t* e);
static void TV_event_handler(lv_event_t* e);
static void Air_Conditioner_event_handler(lv_event_t* e);
static void value_changed_event_cb(lv_event_t* e);
static void Air_Conditioner_humidity_slider_handler(lv_event_t* e);
static void Air_Conditioner_wind_slider_handler(lv_event_t* e);


static const int32_t ecg_sample[] = {
    -2, 2, 0, -15, -39, -63, -71, -68, -67, -69, -84, -95, -104, -107, -108, -107, -107, -107, -107, -114, -118, -117,
    -112, -100, -89, -83, -71, -64, -58, -58, -62, -62, -58, -51, -46, -39, -27, -10, 4, 7, 1, -3, 0, 14, 24, 30, 25, 19,
    13, 7, 12, 15, 18, 21, 13, 6, 9, 8, 17, 19, 13, 11, 11, 11, 23, 30, 37, 34, 25, 14, 15, 19, 28, 31, 26, 23, 25, 31,
    39, 37, 37, 34, 30, 32, 22, 29, 31, 33, 37, 23, 13, 7, 2, 4, -2, 2, 11, 22, 33, 19, -1, -27, -55, -67, -72, -71, -63,
    -49, -18, 35, 113, 230, 369, 525, 651, 722, 730, 667, 563, 454, 357, 305, 288, 274, 255, 212, 173, 143, 117, 82, 39,
    -13, -53, -78, -91, -101, -113, -124, -131, -131, -131, -129, -128, -129, -125, -123, -123, -129, -139, -148, -153,
    -159, -166, -183, -205, -227, -243, -248, -246, -254, -280, -327, -381, -429, -473, -517, -556, -592, -612, -620,
    -620, -614, -604, -591, -574, -540, -497, -441, -389, -358, -336, -313, -284, -222, -167, -114, -70, -47, -28, -4, 12,
    38, 52, 58, 56, 56, 57, 68, 77, 86, 86, 80, 69, 67, 70, 82, 85, 89, 90, 89, 89, 88, 91, 96, 97, 91, 83, 78, 82, 88, 95,
    96, 105, 106, 110, 102, 100, 96, 98, 97, 101, 98, 99, 100, 107, 113, 119, 115, 110, 96, 85, 73, 64, 69, 76, 79,
    78, 75, 85, 100, 114, 113, 105, 96, 84, 74, 66, 60, 75, 85, 89, 83, 67, 61, 67, 73, 79, 74, 63, 57, 56, 58, 61, 55,
    48, 45, 46, 55, 62, 55, 49, 43, 50, 59, 63, 57, 40, 31, 23, 25, 27, 31, 35, 34, 30, 36, 34, 42, 38, 36, 40, 46, 50,
    47, 32, 30, 32, 52, 67, 73, 71, 63, 54, 53, 45, 41, 28, 13, 3, 1, 4, 4, -8, -23, -32, -31, -19, -5, 3, 9, 13, 19,
    24, 27, 29, 25, 22, 26, 32, 42, 51, 56, 60, 57, 55, 53, 53, 54, 59, 54, 49, 26, -3, -11, -20, -47, -100, -194, -236,
    -212, -123, 8, 103, 142, 147, 120, 105, 98, 93, 81, 61, 40, 26, 28, 30, 30, 27, 19, 17, 21, 20, 19, 19, 22, 36, 40,
    35, 20, 7, 1, 10, 18, 27, 22, 6, -4, -2, 3, 6, -2, -13, -14, -10, -2, 3, 2, -1, -5, -10, -19, -32, -42, -55, -60,
    -68, -77, -86, -101, -110, -117, -115, -104, -92, -84, -85, -84, -73, -65, -52, -50, -45, -35, -20, -3, 12, 20, 25,
    26, 28, 28, 30, 28, 25, 28, 33, 42, 42, 36, 23, 9, 0, 1, -4, 1, -4, -4, 1, 5, 9, 9, -3, -1, -18, -50, -108, -190,
    -272, -340, -408, -446, -537, -643, -777, -894, -920, -853, -697, -461, -251, -60, 58, 103, 129, 139, 155, 170, 173,
    178, 185, 190, 193, 200, 208, 215, 225, 224, 232, 234, 240, 240, 236, 229, 226, 224, 232, 233, 232, 224, 219, 219,
    223, 231, 226, 223, 219, 218, 223, 223, 223, 233, 245, 268, 286, 296, 295, 283, 271, 263, 252, 243, 226, 210, 197,
    186, 171, 152, 133, 117, 114, 110, 107, 96, 80, 63, 48, 40, 38, 34, 28, 15, 2, -7, -11, -14, -18, -29, -37, -44, -50,
    -58, -63, -61, -52, -50, -48, -61, -59, -58, -54, -47, -52, -62, -61, -64, -54, -52, -59, -69, -76, -76, -69, -67,
    -74, -78, -81, -80, -73, -65, -57, -53, -51, -47, -35, -27, -22, -22, -24, -21, -17, -13, -10, -11, -13, -20, -20,
    -12, -2, 7, -1, -12, -16, -13, -2, 2, -4, -5, -2, 9, 19, 19, 14, 11, 13, 19, 21, 20, 18, 19, 19, 19, 16, 15, 13, 14,
    9, 3, -5, -9, -5, -3, -2, -3, -3, 2, 8, 9, 9, 5, 6, 8, 8, 7, 4, 3, 4, 5, 3, 5, 5, 13, 13, 12, 10, 10, 15, 22, 17,
    14, 7, 10, 15, 16, 11, 12, 10, 13, 9, -2, -4, -2, 7, 16, 16, 17, 16, 7, -1, -16, -18, -16, -9, -4, -5, -10, -9, -8,
    -3, -4, -10, -19, -20, -16, -9, -9, -23, -40, -48, -43, -33, -19, -21, -26, -31, -33, -19, 0, 17, 24, 9, -17, -47,
    -63, -67, -59, -52, -51, -50, -49, -42, -26, -21, -15, -20, -23, -22, -19, -12, -8, 5, 18, 27, 32, 26, 25, 26, 22,
    23, 17, 14, 17, 21, 25, 2, -45, -121, -196, -226, -200, -118, -9, 73, 126, 131, 114, 87, 60, 42, 29, 26, 34, 35, 34,
    25, 12, 9, 7, 3, 2, -8, -11, 2, 23, 38, 41, 23, 9, 10, 13, 16, 8, -8, -17, -23, -26, -25, -21, -15, -10, -13, -13,
    -19, -22, -29, -40, -48, -48, -54, -55, -66, -82, -85, -90, -92, -98, -114, -119, -124, -129, -132, -146, -146, -138,
    -124, -99, -85, -72, -65, -65, -65, -66, -63, -64, -64, -58, -46, -26, -9, 2, 2, 4, 0, 1, 4, 3, 10, 11, 10, 2, -4,
    0, 10, 18, 20, 6, 2, -9, -7, -3, -3, -2, -7, -12, -5, 5, 24, 36, 31, 25, 6, 3, 7, 12, 17, 11, 0, -6, -9, -8, -7, -5,
    -6, -2, -2, -6, -2, 2, 14, 24, 22, 15, 8, 4, 6, 7, 12, 16, 25, 20, 7, -16, -41, -60, -67, -65, -54, -35, -11, 30,
    84, 175, 302, 455, 603, 707, 743, 714, 625, 519, 414, 337, 300, 281, 263, 239, 197, 163, 136, 109, 77, 34, -18, -50,
    -66, -74, -79, -92, -107, -117, -127, -129, -135, -139, -141, -155, -159, -167, -171, -169, -174, -175, -178, -191,
    -202, -223, -235, -243, -237, -240, -256, -298, -345, -393, -432, -475, -518, -565, -596, -619, -623, -623, -614,
    -599, -583, -559, -524, -477, -425, -383, -357, -331, -301, -252, -198, -143, -96, -57, -29, -8, 10, 31, 45, 60, 65,
    70, 74, 76, 79, 82, 79, 75, 62,
};

LV_IMG_DECLARE(Light_OFF_icon);
LV_IMG_DECLARE(Light_ON_icon);
LV_IMG_DECLARE(WiFi_OFF_icon);
LV_IMG_DECLARE(WiFi_ON_icon);
LV_IMG_DECLARE(TV_OFF_icon);
LV_IMG_DECLARE(TV_ON_icon);

void create_Home_Automation(void)
{
    lv_style_init(&Air_Conditioner_ON_style);
    lv_style_set_arc_color(&Air_Conditioner_ON_style, lv_color_hex(0xFFFFFF));

    lv_style_init(&Air_Conditioner_OFF_style);
    lv_style_set_arc_color(&Air_Conditioner_OFF_style, lv_color_hex(0xA9A9A9));

    /* Home_Automation_background */
    lv_obj_t* Home_Automation_background = lv_obj_create(Home_Automation);
    lv_obj_set_size(Home_Automation_background, background_width, background_height);
    lv_obj_align(Home_Automation_background, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_style_pad_all(Home_Automation_background, 0, 0);
    lv_obj_set_style_border_width(Home_Automation_background, 0, 0);
    lv_obj_set_style_outline_width(Home_Automation_background, 0, 0);

    header_background = lv_obj_create(Home_Automation_background);
    lv_obj_set_size(header_background, background_width, 79);
    lv_obj_set_style_bg_color(header_background, lv_color_hex(0xE3E1FF), 0);

    header_logo = lv_image_create(header_background);
    lv_image_set_src(header_logo, "L:/usr/share/lvgl-home-panel-demo/images/renesas_logomark_blue.png");
    lv_image_set_scale(header_logo, logo_ratio);
    lv_obj_center(header_logo);

    static lv_style_t Home_Automation_text_style;
    lv_style_init(&Home_Automation_text_style);
    lv_style_set_text_color(&Home_Automation_text_style, lv_color_hex(0xDDDDDD));

    static lv_style_t arc_value_style;
    lv_style_init(&arc_value_style);
    lv_style_set_text_color(&arc_value_style, lv_color_hex(0xCCCCCC));

    static lv_style_t sw_state_text_style;
    lv_style_init(&sw_state_text_style);
    lv_style_set_text_color(&sw_state_text_style, lv_color_hex(0xFFFFFF));

    static lv_style_t Air_Conditioner_set_value_style;
    lv_style_init(&Air_Conditioner_set_value_style);
    lv_style_set_text_color(&Air_Conditioner_set_value_style, lv_color_hex(0xFFFFFF));

    /* Room_Temperature_panel */
    lv_obj_t* Room_Temperature_panel = lv_obj_create(Home_Automation_background);
    lv_obj_set_size(Room_Temperature_panel, 263, 274);
    lv_obj_set_pos(Room_Temperature_panel, 250, 165);
    lv_obj_set_style_bg_color(Room_Temperature_panel, lv_color_hex(0x868E96), 0);
    lv_obj_set_style_pad_all(Room_Temperature_panel, 0, 0);
    lv_obj_set_style_border_width(Room_Temperature_panel, 0, 0);
    lv_obj_set_style_outline_width(Room_Temperature_panel, 0, 0);

    lv_obj_t* Room_Temperature_panel_text = lv_label_create(Room_Temperature_panel);
    lv_obj_align(Room_Temperature_panel_text, LV_ALIGN_TOP_MID, 0, 0);
    lv_label_set_text(Room_Temperature_panel_text, "Room Temperature");
    lv_obj_add_style(Room_Temperature_panel_text, &Home_Automation_text_style, 0);

    lv_obj_t* Room_Temperature_arc = lv_arc_create(Room_Temperature_panel);
    lv_obj_center(Room_Temperature_arc);
    lv_obj_set_style_arc_color(Room_Temperature_arc, lv_color_hex(0x2F419A),LV_PART_INDICATOR);
    lv_arc_set_value(Room_Temperature_arc, 50);
    lv_arc_set_rotation(Room_Temperature_arc, 270);
    lv_arc_set_bg_angles(Room_Temperature_arc, 0, 360);
    lv_obj_remove_style(Room_Temperature_arc, NULL, LV_PART_KNOB);
    lv_obj_remove_flag(Room_Temperature_arc, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t* Room_Temperature_value = lv_label_create(Room_Temperature_panel);
    lv_obj_center(Room_Temperature_value);
    lv_label_set_text(Room_Temperature_value, "25°");
    lv_obj_add_style(Room_Temperature_value, &arc_value_style, 0);

    /* Power_Consumption_panel */
    lv_obj_t* Power_Consumption_panel = lv_obj_create(Home_Automation_background);
    lv_obj_set_size(Power_Consumption_panel, 263, 274);
    lv_obj_set_pos(Power_Consumption_panel, 250, 456);
    lv_obj_set_style_bg_color(Power_Consumption_panel, lv_color_hex(0x868E96), 0);
    lv_obj_set_style_pad_all(Power_Consumption_panel, 0, 0);
    lv_obj_set_style_border_width(Power_Consumption_panel, 0, 0);
    lv_obj_set_style_outline_width(Power_Consumption_panel, 0, 0);

    lv_obj_t* Power_Consumption_panel_text = lv_label_create(Power_Consumption_panel);
    lv_obj_align(Power_Consumption_panel_text, LV_ALIGN_TOP_MID, 0, 0);
    lv_label_set_text(Power_Consumption_panel_text, "Power Consumption");
    lv_obj_add_style(Power_Consumption_panel_text, &Home_Automation_text_style, 0);

    lv_obj_t* Power_Consumption_arc = lv_arc_create(Power_Consumption_panel);
    lv_obj_center(Power_Consumption_arc);
    lv_obj_set_style_arc_color(Power_Consumption_arc, lv_color_hex(0xE03131),LV_PART_INDICATOR);
    lv_arc_set_value(Power_Consumption_arc, 70);
    lv_arc_set_rotation(Power_Consumption_arc, 270);
    lv_arc_set_bg_angles(Power_Consumption_arc, 0, 360);
    lv_obj_remove_style(Power_Consumption_arc, NULL, LV_PART_KNOB);
    lv_obj_remove_flag(Power_Consumption_arc, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t* Power_Consumption_value = lv_label_create(Power_Consumption_panel);
    lv_obj_center(Power_Consumption_value);
    lv_label_set_text(Power_Consumption_value, "700kWh");
    lv_obj_add_style(Power_Consumption_value, &arc_value_style, 0);

    /* Light1_panel */
    lv_obj_t* Light1_panel = lv_obj_create(Home_Automation_background);
    lv_obj_set_size(Light1_panel, 263, 274);
    lv_obj_set_pos(Light1_panel, 531, 165);
    lv_obj_set_style_bg_color(Light1_panel, lv_color_hex(0x868E96), 0);
    lv_obj_set_style_pad_all(Light1_panel, 0, 0);
    lv_obj_set_style_border_width(Light1_panel, 0, 0);
    lv_obj_set_style_outline_width(Light1_panel, 0, 0);

    lv_obj_t* Light1_panel_text = lv_label_create(Light1_panel);
    lv_obj_align(Light1_panel_text, LV_ALIGN_TOP_MID, 0, 0);
    lv_label_set_text(Light1_panel_text, "Light 1");
    lv_obj_add_style(Light1_panel_text, &Home_Automation_text_style, 0);

    Light1_icon = lv_image_create(Light1_panel);
    lv_image_set_src(Light1_icon, &Light_OFF_icon);
    lv_obj_center(Light1_icon);

    Light1_sw = lv_switch_create(Light1_panel);
    lv_obj_align(Light1_sw, LV_ALIGN_BOTTOM_MID,0, -27);
    lv_obj_add_event_cb(Light1_sw, Light1_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(Light1_sw, lv_color_hex(0x80F342), LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_t* Light1_sw_text_OFF = lv_label_create(Light1_panel);
    lv_obj_set_pos(Light1_sw_text_OFF, 51, 221);
    lv_label_set_text(Light1_sw_text_OFF, "OFF");
    lv_obj_add_style(Light1_sw_text_OFF, &sw_state_text_style, 0);

    lv_obj_t* Light1_sw_text_ON = lv_label_create(Light1_panel);
    lv_obj_set_pos(Light1_sw_text_ON, 177, 221);
    lv_label_set_text(Light1_sw_text_ON, "ON");
    lv_obj_add_style(Light1_sw_text_ON, &sw_state_text_style, 0);

    /* WiFi_panel */
    lv_obj_t* WiFi_panel = lv_obj_create(Home_Automation_background);
    lv_obj_set_size(WiFi_panel, 263, 274);
    lv_obj_set_pos(WiFi_panel, 531, 456);
    lv_obj_set_style_bg_color(WiFi_panel, lv_color_hex(0x868E96), 0);
    lv_obj_set_style_pad_all(WiFi_panel, 0, 0);
    lv_obj_set_style_border_width(WiFi_panel, 0, 0);
    lv_obj_set_style_outline_width(WiFi_panel, 0, 0);

    lv_obj_t* WiFi_panel_text = lv_label_create(WiFi_panel);
    lv_obj_align(WiFi_panel_text, LV_ALIGN_TOP_MID, 0, 0);
    lv_label_set_text(WiFi_panel_text, "WiFi");
    lv_obj_add_style(WiFi_panel_text, &Home_Automation_text_style, 0);

    WiFi_icon = lv_image_create(WiFi_panel);
    lv_image_set_src(WiFi_icon, &WiFi_OFF_icon);
    lv_obj_center(WiFi_icon);

    WiFi_sw = lv_switch_create(WiFi_panel);
    lv_obj_add_event_cb(WiFi_sw, WiFi_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_align(WiFi_sw, LV_ALIGN_BOTTOM_MID, 0, -27);
    lv_obj_set_style_bg_color(WiFi_sw, lv_color_hex(0x80F342), LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_t* WiFi_sw_text_OFF = lv_label_create(WiFi_panel);
    lv_obj_set_pos(WiFi_sw_text_OFF, 51, 221);
    lv_label_set_text(WiFi_sw_text_OFF, "OFF");
    lv_obj_add_style(WiFi_sw_text_OFF, &sw_state_text_style, 0);

    lv_obj_t* WiFi_sw_text_ON = lv_label_create(WiFi_panel);
    lv_obj_set_pos(WiFi_sw_text_ON, 177, 221);
    lv_label_set_text(WiFi_sw_text_ON, "ON");
    lv_obj_add_style(WiFi_sw_text_ON, &sw_state_text_style, 0);

    /* Light2_panel */
    lv_obj_t* Light2_panel = lv_obj_create(Home_Automation_background);
    lv_obj_set_size(Light2_panel, 263, 274);
    lv_obj_set_pos(Light2_panel, 811, 165);
    lv_obj_set_style_bg_color(Light2_panel, lv_color_hex(0x868E96), 0);
    lv_obj_set_style_pad_all(Light2_panel, 0, 0);
    lv_obj_set_style_border_width(Light2_panel, 0, 0);
    lv_obj_set_style_outline_width(Light2_panel, 0, 0);

    lv_obj_t* Light2_panel_text = lv_label_create(Light2_panel);
    lv_obj_align(Light2_panel_text, LV_ALIGN_TOP_MID, 0, 0);
    lv_label_set_text(Light2_panel_text, "Light 2");
    lv_obj_add_style(Light2_panel_text, &Home_Automation_text_style, 0);

    Light2_icon = lv_image_create(Light2_panel);
    lv_image_set_src(Light2_icon, &Light_OFF_icon);
    lv_obj_center(Light2_icon);

    Light2_sw = lv_switch_create(Light2_panel);
    lv_obj_add_event_cb(Light2_sw, Light2_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_align(Light2_sw, LV_ALIGN_BOTTOM_MID, 0, -27);
    lv_obj_set_style_bg_color(Light2_sw, lv_color_hex(0x80F342), LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_t* Light2_sw_text_OFF = lv_label_create(Light2_panel);
    lv_obj_set_pos(Light2_sw_text_OFF, 51, 221);
    lv_label_set_text(Light2_sw_text_OFF, "OFF");
    lv_obj_add_style(Light2_sw_text_OFF, &sw_state_text_style, 0);

    lv_obj_t* Light2_sw_text_ON = lv_label_create(Light2_panel);
    lv_obj_set_pos(Light2_sw_text_ON, 177, 221);
    lv_label_set_text(Light2_sw_text_ON, "ON");
    lv_obj_add_style(Light2_sw_text_ON, &sw_state_text_style, 0);

    /* TV_panel */
    lv_obj_t* TV_panel = lv_obj_create(Home_Automation_background);
    lv_obj_set_size(TV_panel, 263, 274);
    lv_obj_set_pos(TV_panel, 811, 456);
    lv_obj_set_style_bg_color(TV_panel, lv_color_hex(0x868E96), 0);
    lv_obj_set_style_pad_all(TV_panel, 0, 0);
    lv_obj_set_style_border_width(TV_panel, 0, 0);
    lv_obj_set_style_outline_width(TV_panel, 0, 0);

    lv_obj_t* TV_panel_text = lv_label_create(TV_panel);
    lv_obj_align(TV_panel_text, LV_ALIGN_TOP_MID, 0, 0);
    lv_label_set_text(TV_panel_text, "TV");
    lv_obj_add_style(TV_panel_text, &Home_Automation_text_style, 0);

    TV_icon = lv_image_create(TV_panel);
    lv_image_set_src(TV_icon, &TV_OFF_icon);
    lv_obj_center(TV_icon);

    TV_sw = lv_switch_create(TV_panel);
    lv_obj_add_event_cb(TV_sw, TV_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_align(TV_sw, LV_ALIGN_BOTTOM_MID, 0, -27);
    lv_obj_set_style_bg_color(TV_sw, lv_color_hex(0x80F342), LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_t* TV_sw_text_OFF = lv_label_create(TV_panel);
    lv_obj_set_pos(TV_sw_text_OFF, 51, 221);
    lv_label_set_text(TV_sw_text_OFF, "OFF");
    lv_obj_add_style(TV_sw_text_OFF, &sw_state_text_style, 0);

    lv_obj_t* TV_sw_text_ON = lv_label_create(TV_panel);
    lv_obj_set_pos(TV_sw_text_ON, 177, 221);
    lv_label_set_text(TV_sw_text_ON, "ON");
    lv_obj_add_style(TV_sw_text_ON, &sw_state_text_style, 0);

    /* Air_Conditioner_panel */
    lv_obj_t* Air_Conditioner_panel = lv_obj_create(Home_Automation_background);
    lv_obj_set_size(Air_Conditioner_panel, 519, 829);
    lv_obj_set_pos(Air_Conditioner_panel, 1092, 165);
    lv_obj_set_style_bg_color(Air_Conditioner_panel, lv_color_hex(0x686868), 0);
    lv_obj_set_style_pad_all(Air_Conditioner_panel, 0, 0);
    lv_obj_set_style_border_width(Air_Conditioner_panel, 0, 0);
    lv_obj_set_style_outline_width(Air_Conditioner_panel, 0, 0);

    lv_obj_t* Air_Conditioner_text = lv_label_create(Air_Conditioner_panel);
    lv_obj_set_pos(Air_Conditioner_text, 41, 55);
    lv_label_set_text(Air_Conditioner_text, "Air Conditioner");
    lv_obj_add_style(Air_Conditioner_text, &Home_Automation_text_style, 0);

    Air_Conditioner_sw = lv_switch_create(Air_Conditioner_panel);
    lv_obj_add_event_cb(Air_Conditioner_sw, Air_Conditioner_event_handler, LV_EVENT_CLICKED, Air_Conditioner_meter);
    lv_obj_set_pos(Air_Conditioner_sw, 347, 44);
    lv_obj_set_style_bg_color(Air_Conditioner_sw, lv_color_hex(0x80F342), LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_t* Air_Conditioner_sw_text_OFF = lv_label_create(Air_Conditioner_panel);
    lv_obj_set_pos(Air_Conditioner_sw_text_OFF, 282, 54);
    lv_label_set_text(Air_Conditioner_sw_text_OFF, "OFF");
    lv_obj_add_style(Air_Conditioner_sw_text_OFF, &sw_state_text_style, 0);

    lv_obj_t* Air_Conditioner_sw_text_ON = lv_label_create(Air_Conditioner_panel);
    lv_obj_set_pos(Air_Conditioner_sw_text_ON, 437, 54);
    lv_label_set_text(Air_Conditioner_sw_text_ON, "ON");
    lv_obj_add_style(Air_Conditioner_sw_text_ON, &sw_state_text_style, 0);

    Air_Conditioner_meter = lv_scale_create(Air_Conditioner_panel);
    lv_scale_set_angle_range(Air_Conditioner_meter, 180);
    lv_scale_set_rotation(Air_Conditioner_meter, 180);
    lv_obj_set_size(Air_Conditioner_meter, 450, 450);
    lv_scale_set_label_show(Air_Conditioner_meter, true);
    lv_scale_set_mode(Air_Conditioner_meter, LV_SCALE_MODE_ROUND_INNER);
    lv_obj_center(Air_Conditioner_meter);
    lv_scale_set_total_tick_count(Air_Conditioner_meter, 16);
    lv_scale_set_major_tick_every(Air_Conditioner_meter, 5);
    lv_obj_set_style_length(Air_Conditioner_meter, 10, LV_PART_ITEMS);
    lv_obj_set_style_length(Air_Conditioner_meter, 15, LV_PART_INDICATOR);
    lv_scale_set_range(Air_Conditioner_meter, 15, 30);
    static const char * custom_labels[] = {"15", "20", "25", "30", NULL};
    lv_scale_set_text_src(Air_Conditioner_meter, custom_labels);

    static lv_style_t Air_Conditioner_meter_style;
    lv_style_init(&Air_Conditioner_meter_style);
    lv_style_set_line_width(&Air_Conditioner_meter_style, 3);
    lv_style_set_line_color(&Air_Conditioner_meter_style, lv_color_black());
    lv_obj_add_style(Air_Conditioner_meter, &Air_Conditioner_meter_style, LV_PART_INDICATOR);
    lv_obj_add_style(Air_Conditioner_meter, &Air_Conditioner_meter_style, LV_PART_ITEMS);

    /* Add a three arc indicator */
    Air_Conditioner_set_arc = lv_arc_create(Air_Conditioner_panel);
    lv_obj_set_size(Air_Conditioner_set_arc, 460, 460);
    lv_obj_center(Air_Conditioner_set_arc);
    lv_obj_set_style_bg_color(Air_Conditioner_set_arc, lv_color_hex(0x555555), LV_PART_KNOB);
    lv_arc_set_range(Air_Conditioner_set_arc, 15, 30);
    lv_arc_set_bg_angles(Air_Conditioner_set_arc, 0, 180);
    lv_arc_set_rotation(Air_Conditioner_set_arc, 180);
    lv_obj_add_event_cb(Air_Conditioner_set_arc, value_changed_event_cb, LV_EVENT_VALUE_CHANGED, 0);
    lv_obj_add_style(Air_Conditioner_set_arc, &Air_Conditioner_OFF_style, 0);
    lv_obj_remove_state(Air_Conditioner_set_arc, LV_STATE_DEFAULT);
    lv_obj_add_state(Air_Conditioner_set_arc, LV_STATE_DISABLED);

    lv_obj_t* Air_Conditioner_set_value_background = lv_obj_create(Air_Conditioner_panel);
    lv_obj_set_size(Air_Conditioner_set_value_background, 230, 230);
    lv_obj_center(Air_Conditioner_set_value_background);
    lv_obj_set_style_bg_color(Air_Conditioner_set_value_background, lv_color_hex(0x3E3E3E), 0);
    lv_obj_set_style_radius(Air_Conditioner_set_value_background, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_border_width(Air_Conditioner_set_value_background, 0, 0);

    Air_Conditioner_set_value_label = lv_label_create(Air_Conditioner_set_value_background);
    lv_label_set_text(Air_Conditioner_set_value_label, "15.0°");
    lv_obj_center(Air_Conditioner_set_value_label);
    lv_obj_add_style(Air_Conditioner_set_value_label, &Home_Automation_text_style, 0);

    lv_style_init(&Air_Conditioner_humidity_ON_style);
    lv_style_set_bg_opa(&Air_Conditioner_humidity_ON_style, LV_OPA_COVER);
    lv_style_set_bg_color(&Air_Conditioner_humidity_ON_style, lv_color_hex(0x575CAE));
    lv_style_set_bg_grad_color(&Air_Conditioner_humidity_ON_style, lv_color_hex(0x5AC4B1));
    lv_style_set_bg_grad_dir(&Air_Conditioner_humidity_ON_style, LV_GRAD_DIR_HOR);

    lv_style_init(&Air_Conditioner_slider_OFF_style);
    lv_style_set_bg_color(&Air_Conditioner_slider_OFF_style, lv_color_hex(0xA9A9A9));

    lv_style_init(&Air_Conditioner_wind_ON_style);
    lv_style_set_bg_opa(&Air_Conditioner_wind_ON_style, LV_OPA_COVER);
    lv_style_set_bg_color(&Air_Conditioner_wind_ON_style, lv_color_hex(0x068A42));
    lv_style_set_bg_grad_color(&Air_Conditioner_wind_ON_style, lv_color_hex(0x9EF033));
    lv_style_set_bg_grad_dir(&Air_Conditioner_wind_ON_style, LV_GRAD_DIR_HOR);

    Air_Conditioner_set_humidity_slider = lv_slider_create(Air_Conditioner_panel);
    lv_obj_set_size(Air_Conditioner_set_humidity_slider, 129, 29);
    lv_obj_set_pos(Air_Conditioner_set_humidity_slider, 67, 760);
    lv_obj_add_style(Air_Conditioner_set_humidity_slider, &Air_Conditioner_slider_OFF_style, 0);
    lv_obj_set_style_bg_color(Air_Conditioner_set_humidity_slider, lv_color_hex(0x555555), LV_PART_KNOB);
    lv_obj_add_event_cb(Air_Conditioner_set_humidity_slider, Air_Conditioner_humidity_slider_handler, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_t* Air_Conditioner_set_humidity_value_background = lv_obj_create(Air_Conditioner_panel);
    lv_obj_set_size(Air_Conditioner_set_humidity_value_background, 34, 30);
    lv_obj_set_pos(Air_Conditioner_set_humidity_value_background, 209, 760);
    lv_obj_set_style_bg_color(Air_Conditioner_set_humidity_value_background, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_radius(Air_Conditioner_set_humidity_value_background, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_border_width(Air_Conditioner_set_humidity_value_background, 0, 0);
    lv_obj_remove_flag(Air_Conditioner_set_humidity_value_background, LV_OBJ_FLAG_SCROLLABLE);

    Air_Conditioner_set_humidity_value_label = lv_label_create(Air_Conditioner_set_humidity_value_background);
    lv_label_set_text(Air_Conditioner_set_humidity_value_label, "0%");
    lv_obj_center(Air_Conditioner_set_humidity_value_label);

    Air_Conditioner_set_wind_slider = lv_slider_create(Air_Conditioner_panel);
    lv_obj_set_size(Air_Conditioner_set_wind_slider, 129, 29);
    lv_obj_set_pos(Air_Conditioner_set_wind_slider, 276, 760);
    lv_obj_add_style(Air_Conditioner_set_wind_slider, &Air_Conditioner_slider_OFF_style, 0);
    lv_obj_set_style_bg_color(Air_Conditioner_set_wind_slider, lv_color_hex(0x555555), LV_PART_KNOB);
    lv_obj_add_event_cb(Air_Conditioner_set_wind_slider, Air_Conditioner_wind_slider_handler, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_t* Air_Conditioner_set_wind_value_background = lv_obj_create(Air_Conditioner_panel);
    lv_obj_set_size(Air_Conditioner_set_wind_value_background, 34, 30);
    lv_obj_set_pos(Air_Conditioner_set_wind_value_background, 419, 760);
    lv_obj_set_style_bg_color(Air_Conditioner_set_wind_value_background, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_radius(Air_Conditioner_set_wind_value_background, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_border_width(Air_Conditioner_set_wind_value_background, 0, 0);
    lv_obj_remove_flag(Air_Conditioner_set_wind_value_background, LV_OBJ_FLAG_SCROLLABLE);

    Air_Conditioner_set_wind_value_label = lv_label_create(Air_Conditioner_set_wind_value_background);
    lv_label_set_text(Air_Conditioner_set_wind_value_label, "0");
    lv_obj_center(Air_Conditioner_set_wind_value_label);

    lv_obj_t *Home_Automation_chart = lv_chart_create(Home_Automation_background);
    lv_obj_set_pos(Home_Automation_chart, 250, 747);
    lv_obj_set_size(Home_Automation_chart, 822, 240);
    lv_obj_set_scroll_snap_x(Home_Automation_chart, LV_SCROLL_SNAP_CENTER);
    lv_chart_set_range(Home_Automation_chart, LV_CHART_AXIS_PRIMARY_Y, -1000, 1000);

    /* Do not display points on the data */
    lv_obj_set_style_size(Home_Automation_chart, 0, 0, LV_PART_INDICATOR);

    ser = lv_chart_add_series(Home_Automation_chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);

    pcnt = sizeof(ecg_sample) / sizeof(ecg_sample[0]);
    lv_chart_set_point_count(Home_Automation_chart, pcnt);
    lv_chart_set_ext_y_array(Home_Automation_chart, ser, (int32_t*)ecg_sample);

}

static void Light1_event_handler(lv_event_t* e)
{
    /* Light1_OFF */
    if(light1_state == 0)
    {
        lv_image_set_src(Light1_icon, &Light_ON_icon);
        light1_state = 1;
    } 
    /* Light1_ON */
    else if(light1_state == 1)
    {
        lv_image_set_src(Light1_icon, &Light_OFF_icon);
        light1_state = 0;
    }
}

static void WiFi_event_handler(lv_event_t* e)
{
    /* WiFi_OFF */
    if(WiFi_state == 0)
    {
        lv_image_set_src(WiFi_icon, &WiFi_ON_icon);
        WiFi_state = 1;
    } 
    /* Wifi_ON */
    else if(WiFi_state == 1)
    {
        lv_image_set_src(WiFi_icon, &WiFi_OFF_icon);
        WiFi_state = 0;
    }
}

static void Light2_event_handler(lv_event_t* e)
{
    /* Light2_OFF */
    if(Light2_state == 0)
    {
        lv_image_set_src(Light2_icon, &Light_ON_icon);
        Light2_state = 1;
    } 
    /* Light2_ON */
    else if(Light2_state == 1)
    {
        lv_image_set_src(Light2_icon, &Light_OFF_icon);
        Light2_state = 0;
    }
}

static void TV_event_handler(lv_event_t* e)
{
    /* TV_OFF */
    if(TV_state == 0)
    {
        lv_image_set_src(TV_icon, &TV_ON_icon);
        TV_state = 1;
    } 
    /* TV_ON */
    else if(TV_state == 1)
    {
        lv_image_set_src(TV_icon, &TV_OFF_icon);
        TV_state = 0;
    }
}

static void Air_Conditioner_event_handler(lv_event_t* e)
{
    /* Air_Conditioner_OFF */
    if (Air_Conditioner_state == 0)
    {
        lv_obj_set_style_bg_color(Air_Conditioner_set_arc, lv_color_hex(0xFFFFFF), LV_PART_KNOB);
        lv_obj_set_style_arc_color(Air_Conditioner_set_arc, lv_color_hex(0xFFC500), LV_PART_INDICATOR);
        Air_Conditioner_state = 1;
        lv_obj_remove_style(Air_Conditioner_set_arc, &Air_Conditioner_OFF_style, 0);
        lv_obj_add_style(Air_Conditioner_set_arc, &Air_Conditioner_ON_style, 0);
        lv_obj_add_state(Air_Conditioner_set_arc, LV_STATE_DEFAULT);
        lv_obj_remove_state(Air_Conditioner_set_arc, LV_STATE_DISABLED);

        lv_obj_set_style_bg_color(Air_Conditioner_set_humidity_slider, lv_color_hex(0xFFFFFF), LV_PART_KNOB);
        lv_obj_set_style_bg_color(Air_Conditioner_set_humidity_slider, lv_color_hex(0x575CAE),LV_PART_INDICATOR);
        lv_obj_remove_style(Air_Conditioner_set_humidity_slider, &Air_Conditioner_OFF_style, LV_PART_INDICATOR);
        lv_obj_add_style(Air_Conditioner_set_humidity_slider, &Air_Conditioner_humidity_ON_style, LV_PART_INDICATOR);
        lv_obj_add_state(Air_Conditioner_set_humidity_slider, LV_STATE_DEFAULT);
        lv_obj_remove_state(Air_Conditioner_set_humidity_slider, LV_STATE_DISABLED);
        
        lv_obj_set_style_bg_color(Air_Conditioner_set_wind_slider, lv_color_hex(0xFFFFFF), LV_PART_KNOB);
        lv_obj_set_style_bg_color(Air_Conditioner_set_wind_slider, lv_color_hex(0x068A42),LV_PART_INDICATOR);
        lv_obj_remove_style(Air_Conditioner_set_wind_slider, &Air_Conditioner_OFF_style, LV_PART_INDICATOR);
        lv_obj_add_style(Air_Conditioner_set_wind_slider, &Air_Conditioner_humidity_ON_style, LV_PART_INDICATOR);
        lv_obj_add_state(Air_Conditioner_set_wind_slider, LV_STATE_DEFAULT);
        lv_obj_remove_state(Air_Conditioner_set_wind_slider, LV_STATE_DISABLED);
    }
    /* Air_Conditioner_ON */
    else if (Air_Conditioner_state == 1)
    {
        lv_obj_set_style_bg_color(Air_Conditioner_set_arc, lv_color_hex(0x555555), LV_PART_KNOB);
        lv_obj_set_style_arc_color(Air_Conditioner_set_arc, lv_color_hex(0xA9A9A9),LV_PART_INDICATOR);
        Air_Conditioner_state = 0;
        lv_obj_remove_style(Air_Conditioner_set_arc, &Air_Conditioner_ON_style, 0);
        lv_obj_remove_style(Air_Conditioner_set_arc, &Air_Conditioner_ON_style, LV_PART_INDICATOR);
        lv_obj_add_style(Air_Conditioner_set_arc, &Air_Conditioner_OFF_style, 0);
        lv_obj_remove_state(Air_Conditioner_set_arc, LV_STATE_DEFAULT);
        lv_obj_add_state(Air_Conditioner_set_arc, LV_STATE_DISABLED);

        lv_obj_set_style_bg_color(Air_Conditioner_set_humidity_slider, lv_color_hex(0x555555), LV_PART_KNOB);
        lv_obj_set_style_bg_color(Air_Conditioner_set_humidity_slider, lv_color_hex(0xA9A9A9), LV_PART_INDICATOR);
        lv_obj_remove_style(Air_Conditioner_set_humidity_slider, &Air_Conditioner_humidity_ON_style, LV_PART_INDICATOR);
        lv_obj_add_style(Air_Conditioner_set_humidity_slider, &Air_Conditioner_OFF_style, LV_PART_INDICATOR);
        lv_obj_add_style(Air_Conditioner_set_humidity_slider, &Air_Conditioner_OFF_style, 0);
        lv_obj_remove_state(Air_Conditioner_set_humidity_slider, LV_STATE_DEFAULT);
        lv_obj_add_state(Air_Conditioner_set_humidity_slider, LV_STATE_DISABLED);

        lv_obj_set_style_bg_color(Air_Conditioner_set_wind_slider, lv_color_hex(0x555555), LV_PART_KNOB);
        lv_obj_set_style_bg_color(Air_Conditioner_set_wind_slider, lv_color_hex(0xA9A9A9), LV_PART_INDICATOR);
        lv_obj_remove_style(Air_Conditioner_set_wind_slider, &Air_Conditioner_humidity_ON_style, LV_PART_INDICATOR);
        lv_obj_add_style(Air_Conditioner_set_wind_slider, &Air_Conditioner_OFF_style, LV_PART_INDICATOR);
        lv_obj_add_style(Air_Conditioner_set_wind_slider, &Air_Conditioner_OFF_style, 0);
        lv_obj_remove_state(Air_Conditioner_set_wind_slider, LV_STATE_DEFAULT);
        lv_obj_add_state(Air_Conditioner_set_wind_slider, LV_STATE_DISABLED);
    } 
}

static void value_changed_event_cb(lv_event_t* e)
{
    lv_label_set_text_fmt(Air_Conditioner_set_value_label, "%d.0°", lv_arc_get_value(Air_Conditioner_set_arc));
}

static void Air_Conditioner_humidity_slider_handler(lv_event_t* e)
{
    lv_label_set_text_fmt(Air_Conditioner_set_humidity_value_label, "%d%%", (int)lv_slider_get_value(Air_Conditioner_set_humidity_slider));
}

static void Air_Conditioner_wind_slider_handler(lv_event_t* e)
{
    lv_label_set_text_fmt(Air_Conditioner_set_wind_value_label, "%d", (int)lv_slider_get_value(Air_Conditioner_set_wind_slider));
}