#ifndef _GENERAL_H
#define _GENERAL_H

#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "lvgl.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "ui.h"

typedef struct {
  bool wifi_on;
  bool wifi_connected;
  uint8_t screen_brightness_slider_value
} global_data_t;

extern global_data_t my_app;

void wifi_init(void);
void wifi_scan(void);
void wifi_connect(void);
void wifi_off(void);

void create_settings_menu(void);

void log_memory_info();

#endif
