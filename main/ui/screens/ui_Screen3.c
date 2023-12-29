// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Screen3_screen_init(void)
{
ui_Screen3 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen3, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Bar1 = lv_bar_create(ui_Screen3);
lv_bar_set_value(ui_Bar1,25,LV_ANIM_OFF);
lv_bar_set_start_value(ui_Bar1, 0, LV_ANIM_OFF);
lv_obj_set_width( ui_Bar1, 400);
lv_obj_set_height( ui_Bar1, 20);
lv_obj_set_align( ui_Bar1, LV_ALIGN_CENTER );

ui_Button1 = lv_btn_create(ui_Screen3);
lv_obj_set_width( ui_Button1, 100);
lv_obj_set_height( ui_Button1, 50);
lv_obj_set_x( ui_Button1, 0 );
lv_obj_set_y( ui_Button1, 83 );
lv_obj_set_align( ui_Button1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Button1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label5 = lv_label_create(ui_Button1);
lv_obj_set_width( ui_Label5, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label5, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label5, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label5,"Save");

lv_obj_add_event_cb(ui_Button1, ui_event_Button1, LV_EVENT_ALL, NULL);

}