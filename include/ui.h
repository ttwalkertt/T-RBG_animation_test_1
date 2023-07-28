// ui.h for the ui class
#include <lvgl.h>
#include <TRGBSuppport.h>


class UI {
    public:
        // Constructor
        UI();

        // Destructor
        ~UI();

        // Methods
        int init();
        int get_screen_width();
        int get_screen_height();

    private:
        static constexpr int DispBufSize = 480 * 16;
        static lv_color_t buf[DispBufSize];
        static lv_disp_draw_buf_t disp_buf;
        lv_obj_t * ui_S1Main;
        int screen_heigth = 0;
        int screen_width = 0;

       

};
