#include "ui.h"

lv_color_t UI::buf[UI::DispBufSize];
lv_disp_draw_buf_t UI::disp_buf;


// animation callback. Since it's static it can't access instance variables
static void color_anim_cb(void * var, int32_t v) {
     lv_obj_t* obj = (lv_obj_t*)var;
    lv_obj_set_style_bg_color(obj, lv_color_hsv_to_rgb(v, 100, 100), 0);
    // Change size
    int min_size = 20;
    int max_size = 480;
    int size = min_size + ((max_size - min_size) * v) / 360;
    size = 240 + 200 * (v-180)/180;
    lv_obj_set_size(obj, size, size);
}


UI::UI()
{
    screen_heigth = 0;
    screen_width = 0;
}

UI::~UI()
{
    Serial.println("UI destructor");
}




int UI::init(){
    int stat = 0;
    ui_S1Main = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_S1Main, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    screen_heigth = lv_disp_get_hor_res(NULL);
    screen_width = lv_disp_get_ver_res(NULL);
    Serial.printf("Screen: %d x %d\n", screen_heigth, screen_width);
    lv_obj_set_size(ui_S1Main, screen_width, screen_heigth);
    lv_obj_set_pos(ui_S1Main, 0, 0);
    lv_obj_set_style_bg_color(ui_S1Main, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(ui_S1Main, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(ui_S1Main, 0, 0);
    lv_obj_set_style_border_opa(ui_S1Main, 0, 0);
    Serial.printf("ui_S1Main: %d x %d\n", lv_obj_get_width(ui_S1Main), lv_obj_get_height(ui_S1Main));
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DispBufSize);

    /*Create a timer to periodically call the lv_timer_handler*/
    lv_timer_create([](lv_timer_t * timer) {
        lv_timer_handler();
    }, 5, NULL);

        /*Create an object (circle)*/
    lv_obj_t * obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj, 100, 100);
    lv_obj_center(obj);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(obj, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(obj, lv_color_black(), 0);

        /*Create an animation to change the color of the object*/
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) color_anim_cb);
    lv_anim_set_values(&a, 0, 360);
    lv_anim_set_time(&a, 30000);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);

    return stat;
}
int UI::get_screen_height(){
    return screen_heigth;
}
int UI::get_screen_width(){
    return screen_width;
}


