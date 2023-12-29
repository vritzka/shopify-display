// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Screen2_screen_init(void)
{
ui_Screen2 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Container1 = lv_obj_create(ui_Screen2);
lv_obj_remove_style_all(ui_Container1);
lv_obj_set_width( ui_Container1, 600);
lv_obj_set_height( ui_Container1, 460);
lv_obj_set_x( ui_Container1, 95 );
lv_obj_set_y( ui_Container1, 0 );
lv_obj_set_align( ui_Container1, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Container1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Slider1 = lv_slider_create(ui_Container1);
lv_obj_set_width( ui_Slider1, 400);
lv_obj_set_height( ui_Slider1, 20);
lv_obj_set_x( ui_Slider1, 0 );
lv_obj_set_y( ui_Slider1, -106 );
lv_obj_set_align( ui_Slider1, LV_ALIGN_CENTER );


ui_Container2 = lv_obj_create(ui_Screen2);
lv_obj_remove_style_all(ui_Container2);
lv_obj_set_width( ui_Container2, 540);
lv_obj_set_height( ui_Container2, 460);
lv_obj_set_x( ui_Container2, 0 );
lv_obj_set_y( ui_Container2, -1 );
lv_obj_set_align( ui_Container2, LV_ALIGN_RIGHT_MID );
lv_obj_clear_flag( ui_Container2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_WifiKeyboard = lv_keyboard_create(ui_Container2);
lv_obj_set_width( ui_WifiKeyboard, 540);
lv_obj_set_height( ui_WifiKeyboard, 250);
lv_obj_set_align( ui_WifiKeyboard, LV_ALIGN_BOTTOM_MID );

ui_WifiDropdown = lv_dropdown_create(ui_Container2);
lv_obj_set_width( ui_WifiDropdown, 150);
lv_obj_set_height( ui_WifiDropdown, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_WifiDropdown, -184 );
lv_obj_set_y( ui_WifiDropdown, -100 );
lv_obj_set_align( ui_WifiDropdown, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_WifiDropdown, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags



ui_WifiPassword = lv_textarea_create(ui_Container2);
lv_obj_set_width( ui_WifiPassword, 150);
lv_obj_set_height( ui_WifiPassword, LV_SIZE_CONTENT);   /// 70
lv_obj_set_x( ui_WifiPassword, 126 );
lv_obj_set_y( ui_WifiPassword, -100 );
lv_obj_set_align( ui_WifiPassword, LV_ALIGN_CENTER );
lv_textarea_set_text(ui_WifiPassword,"fjxzwrmw6xd2");
lv_textarea_set_one_line(ui_WifiPassword,true);



ui_WifiScanButton = lv_btn_create(ui_Container2);
lv_obj_set_width( ui_WifiScanButton, 50);
lv_obj_set_height( ui_WifiScanButton, 50);
lv_obj_set_x( ui_WifiScanButton, -65 );
lv_obj_set_y( ui_WifiScanButton, -97 );
lv_obj_set_align( ui_WifiScanButton, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_WifiScanButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_WifiScanButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label3 = lv_label_create(ui_Container2);
lv_obj_set_width( ui_Label3, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label3, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label3, -241 );
lv_obj_set_y( ui_Label3, -143 );
lv_obj_set_align( ui_Label3, LV_ALIGN_CENTER );

ui_Label4 = lv_label_create(ui_Container2);
lv_obj_set_width( ui_Label4, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label4, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label4, 74 );
lv_obj_set_y( ui_Label4, -141 );
lv_obj_set_align( ui_Label4, LV_ALIGN_CENTER );

ui_WifiStatusLabel = lv_label_create(ui_Container2);
lv_obj_set_width( ui_WifiStatusLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_WifiStatusLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_WifiStatusLabel, -65 );
lv_obj_set_y( ui_WifiStatusLabel, -44 );
lv_obj_set_align( ui_WifiStatusLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_WifiStatusLabel,"");

ui_Container3 = lv_obj_create(ui_Screen2);
lv_obj_remove_style_all(ui_Container3);
lv_obj_set_width( ui_Container3, 600);
lv_obj_set_height( ui_Container3, 460);
lv_obj_set_x( ui_Container3, 95 );
lv_obj_set_y( ui_Container3, 0 );
lv_obj_set_align( ui_Container3, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Container3, LV_OBJ_FLAG_HIDDEN );   /// Flags
lv_obj_clear_flag( ui_Container3, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

lv_keyboard_set_textarea(ui_WifiKeyboard,ui_WifiPassword);
lv_obj_add_event_cb(ui_WifiKeyboard, ui_event_WifiKeyboard, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_WifiScanButton, ui_event_WifiScanButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Screen2, ui_event_Screen2, LV_EVENT_ALL, NULL);

}