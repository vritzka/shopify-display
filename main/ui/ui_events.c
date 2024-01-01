#include "api_request_task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"
#include "general.h"
#include "otaTask.h"
#include "ui.h"

static const char *TAG = "ui_events.c";
static esp_err_t err;
static nvs_handle_t storage_handle;

void init_app(lv_event_t *e) {

  err = nvs_open("storage", NVS_READWRITE, &storage_handle);

  void init_ledc(void);

  my_app.screen_brightness_slider_value = 80;

  // general settings screen
  err = nvs_get_u8(storage_handle, "screen_brightns",
                   &my_app.screen_brightness_slider_value);
  ESP_LOGI(TAG, "loaded Brightness %d", my_app.screen_brightness_slider_value);

  // lv_label_set_text_fmt(ui_ScreenBrightnessLabel, "%d%%",
  // my_app.screen_brightness_slider_value);
  lv_slider_set_value(ui_ScreenBrightnessSlider,
                      my_app.screen_brightness_slider_value, LV_ANIM_OFF);
  my_app.screen_brightness_duty =
      (128 - 1) * ((float)my_app.screen_brightness_slider_value / 100);
  ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_BACKLIGHT_CHANNEL,
                                my_app.screen_brightness_duty));
  ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_BACKLIGHT_CHANNEL));

  create_settings_menu();
  ESP_LOGI(TAG, "Starting API Request Timer");
  ESP_ERROR_CHECK(gptimer_start(requestTimerHandle));
  wifi_init();
  lv_obj_set_style_bg_img_src(ui_WifiScanButton, LV_SYMBOL_REFRESH, 0);

  nvs_close(storage_handle);
}

void wifi_scan_button_cb(lv_event_t *e) { wifi_scan(); }

void WifiKeyboardReady(lv_event_t *e) {
  // if(!my_app.wifi_on)
  wifi_connect();
}

void software_upgrade_button(lv_event_t *e) { vStartOtaTask(); }

/////////////////////////////////////
///////////// Settings Screen ///////
/////////////////////////////////////

void screen_brightness_slider(lv_event_t *e) {
  lv_obj_t *target = lv_event_get_target(e);
  my_app.screen_brightness_slider_value = lv_slider_get_value(target);

  my_app.screen_brightness_duty =
      (128 - 1) * ((float)my_app.screen_brightness_slider_value / 100);

  ESP_LOGI(TAG, "Brightness %d", my_app.screen_brightness_duty);

  ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_BACKLIGHT_CHANNEL,
                                my_app.screen_brightness_duty));
  ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_BACKLIGHT_CHANNEL));
}

void save_settings_screen(lv_event_t *e) {
  err = nvs_open("storage", NVS_READWRITE, &storage_handle);
  if (err != ESP_OK) {
    printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
  } else {
    ESP_LOGI(TAG, "saved Brightness %d", my_app.screen_brightness_slider_value);
    err = nvs_set_u8(storage_handle, "screen_brightns",
                     my_app.screen_brightness_slider_value);

    // Close
    err = nvs_commit(storage_handle);
    nvs_close(storage_handle);
  }
}
