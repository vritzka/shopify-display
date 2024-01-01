#ifndef _GUI_H
#define _GUI_H

// #include "general.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_rgb.h"
#include "esp_lcd_touch_gt911.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "lvgl.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "sdkconfig.h"
#include "ui.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <stdbool.h>
#include <stdlib.h>

#include "esp_freertos_hooks.h"
#include "esp_system.h"

extern esp_lcd_panel_handle_t panel_handle;
extern TaskHandle_t xGuiTaskHandle;
void guiTask(void *pvParameter);
void vStartGuiTask(void);
extern void vEndGuiTask(void);

void touch_read(lv_indev_drv_t *drv, lv_indev_data_t *data);

#endif
