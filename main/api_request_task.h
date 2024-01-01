#include "driver/gptimer.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "general.h"
#include "lvgl.h"
#include "ui.h"
#include <stdio.h>

extern gptimer_handle_t requestTimerHandle;
void vCreateRequestTask(void *pvParameters);
void vStartRequestTask(void);
void vDeleteRequestTask(void);
