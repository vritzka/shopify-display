#include "api_request_task.h"

static const char *TAG = "sensorTask.c";

gptimer_handle_t requestTimerHandle = NULL;
static TaskHandle_t xRequestTaskHandle = NULL;
//static esp_err_t err;
SemaphoreHandle_t xSemaphore = NULL;


static bool IRAM_ATTR request_cb(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_data)
{
    BaseType_t high_task_awoken = pdFALSE;

    xSemaphoreGiveFromISR( xSemaphore, &high_task_awoken );
    // return whether we need to yield at the end of ISR
    return (high_task_awoken == pdTRUE);
}


// Task to be created.
void vCreateRequestTask( void * pvParameters )
{
	    
	xSemaphore = xSemaphoreCreateBinary();    
	    
    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1000000, // 1MHz, 1 tick=1us
    };
    ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &requestTimerHandle));
    
    gptimer_event_callbacks_t cbs = {
        .on_alarm = request_cb,
    };
    ESP_ERROR_CHECK(gptimer_register_event_callbacks(requestTimerHandle, &cbs, NULL));
    
    ESP_LOGI(TAG, "Enable request timer");
    ESP_ERROR_CHECK(gptimer_enable(requestTimerHandle));
    
    gptimer_alarm_config_t alarm_config1 = {
        .reload_count = 0,
        .alarm_count = 5000000, // period = 5s
        .flags.auto_reload_on_alarm = true,
    };
    ESP_ERROR_CHECK(gptimer_set_alarm_action(requestTimerHandle, &alarm_config1));
	
	vTaskDelay(1000 / portTICK_PERIOD_MS);	

	
	for( ;; )
	{
		if( xSemaphoreTake( xSemaphore, pdMS_TO_TICKS(6000) ) == pdTRUE ) {
			ESP_LOGI(TAG, "API call would run");
		} else {
			//ESP_LOGW(TAG, "Missed 1 count event or Timer stopped");
		}
			
	}
}

// Function that creates a task.
//How to allocate task memory from SPI https://esp32.com/viewtopic.php?t=20660
void vStartRequestTask( void )
{
  static uint8_t ucParameterToPass;
  xTaskCreatePinnedToCore( vCreateRequestTask, "SENSORTASK", 4096, &ucParameterToPass, 10, &xRequestTaskHandle, 1 );
  configASSERT( xRequestTaskHandle );
}


extern void vDeleteRequestTask( void )
{
  if( xRequestTaskHandle != NULL )
  {
     vTaskDelete( xRequestTaskHandle );
  }

}


