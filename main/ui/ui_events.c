#include "api_request_task.h"
#include "esp_log.h"
#include "general.h"
#include "otaTask.h"
#include "ui.h"

static const char *TAG = "ui_events.c";

void init_app(lv_event_t *e) {
  my_app.screen_brightness_slider_value = 80;
  create_settings_menu();
  ESP_LOGI(TAG, "Starting API Request Timer");
  ESP_ERROR_CHECK(gptimer_start(requestTimerHandle));
  wifi_init();
  // wifi_connect();
  lv_obj_set_style_bg_img_src(ui_WifiScanButton, LV_SYMBOL_REFRESH, 0);
}

void wifi_scan_button_cb(lv_event_t *e) { wifi_scan(); }

void save_slider(lv_event_t *e) {
  uint32_t value = lv_slider_get_value(ui_Bar1);

  ESP_LOGI(TAG, "Slidervalue = %lu", value);
}

void WifiKeyboardReady(lv_event_t *e) {
  // if(!my_app.wifi_on)
  wifi_connect();
}

void software_upgrade_button(lv_event_t *e) { vStartOtaTask(); }
