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
#include "driver/ledc.h"


typedef struct {
  bool wifi_on;
  bool wifi_connected;
  uint8_t screen_brightness_slider_value;
  uint16_t screen_brightness_duty;
} global_data_t;

extern global_data_t my_app;

#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_BACKLIGHT_TIMER              LEDC_TIMER_0
#define LEDC_BACKLIGHT_OUTPUT_IO          (45) // Define the output GPIO for Backlight
#define LEDC_BACKLIGHT_CHANNEL            LEDC_CHANNEL_0
#define LEDC_BACKLIGHT_DUTY_RES           LEDC_TIMER_7_BIT // Set duty resolution to 13 bits
#define LEDC_BACKLIGHT_FREQUENCY          (500) // Frequency in Hertz. 

void wifi_init(void);
void wifi_scan(void);
void wifi_connect(void);
void wifi_off(void);
void init_ledc(void);

void create_settings_menu(void);

void log_memory_info();

#endif
