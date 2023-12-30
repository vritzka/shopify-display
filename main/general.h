#ifndef _GENERAL_H
#define _GENERAL_H


#include "lvgl.h"
#include "ui.h"
#include "esp_err.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_ota_ops.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "esp_event.h"



typedef struct {
	bool wifi_on;   
    bool wifi_connected;
} global_data_t;

extern global_data_t my_app;



void wifi_init(void);
void wifi_scan(void);
void wifi_connect(void);
void wifi_off(void);

void create_settings_menu(void);

void log_memory_info();


#endif
