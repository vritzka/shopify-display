#include "general.h"

static const char *TAG = "General";

char *currentScreen;

esp_err_t err;
nvs_handle_t storage_handle;

SemaphoreHandle_t xGuiSemaphore;

char somestring[36];

global_data_t my_app;

////////////////////////////////////////////////////////////
//////////////////////// SETTINGS PAGE /////////////////////
////////////////////////////////////////////////////////////

enum { LV_MENU_ITEM_BUILDER_VARIANT_1, LV_MENU_ITEM_BUILDER_VARIANT_2 };
typedef uint8_t lv_menu_builder_variant_t;

static void back_event_handler(lv_event_t *e);
lv_obj_t *root_page;
static lv_obj_t *create_text(lv_obj_t *parent, const char *icon,
                             const char *txt,
                             lv_menu_builder_variant_t builder_variant);

void create_settings_menu(void) {

  lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_t *menu = lv_menu_create(ui_Screen2);

  lv_color_t bg_color = lv_obj_get_style_bg_color(menu, 0);
  if (lv_color_brightness(bg_color) > 127) {
    lv_obj_set_style_bg_color(
        menu, lv_color_darken(lv_obj_get_style_bg_color(menu, 0), 10), 0);
  } else {
    lv_obj_set_style_bg_color(
        menu, lv_color_darken(lv_obj_get_style_bg_color(menu, 0), 50), 0);
  }
  lv_menu_set_mode_root_back_btn(menu, LV_MENU_ROOT_BACK_BTN_ENABLED);
  lv_obj_add_event_cb(menu, back_event_handler, LV_EVENT_CLICKED, menu);
  lv_obj_set_size(menu, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
  lv_obj_center(menu);

  lv_obj_t *cont;
  lv_obj_t *section;

  /*Create sub pages*/
  lv_obj_t *sub_gps_page = lv_menu_page_create(menu, NULL);
  lv_obj_set_style_pad_hor(
      sub_gps_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0),
      0);
  lv_menu_separator_create(sub_gps_page);
  section = lv_menu_section_create(sub_gps_page);
  lv_obj_set_parent(ui_Container1, section);

  lv_obj_t *sub_software_page = lv_menu_page_create(menu, NULL);
  lv_obj_set_style_pad_hor(
      sub_software_page,
      lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
  lv_menu_separator_create(sub_software_page);
  section = lv_menu_section_create(sub_software_page);
  lv_obj_set_parent(ui_Container2, section);

  lv_obj_t *sub_display_page = lv_menu_page_create(menu, NULL);
  lv_obj_set_style_pad_hor(
      sub_display_page,
      lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
  lv_menu_separator_create(sub_display_page);
  section = lv_menu_section_create(sub_display_page);
  lv_obj_set_parent(ui_Container3, section);

  /*Create a root page*/
  root_page = lv_menu_page_create(menu, "Settings");
  lv_obj_set_style_pad_hor(
      root_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0),
      0);
  section = lv_menu_section_create(root_page);
  cont = create_text(section, LV_SYMBOL_IMAGE, "Display",
                     LV_MENU_ITEM_BUILDER_VARIANT_1);
  lv_menu_set_load_page_event(menu, cont, sub_display_page);
  cont = create_text(section, LV_SYMBOL_WIFI, "Wifi",
                     LV_MENU_ITEM_BUILDER_VARIANT_1);
  lv_menu_set_load_page_event(menu, cont, sub_software_page);
  cont = create_text(section, LV_SYMBOL_SETTINGS, "Other",
                     LV_MENU_ITEM_BUILDER_VARIANT_1);
  lv_menu_set_load_page_event(menu, cont, sub_gps_page);

  lv_menu_set_sidebar_page(menu, root_page);

  lv_event_send(lv_obj_get_child(
                    lv_obj_get_child(lv_menu_get_cur_sidebar_page(menu), 0), 0),
                LV_EVENT_CLICKED, NULL);
}

static lv_obj_t *create_text(lv_obj_t *parent, const char *icon,
                             const char *txt,
                             lv_menu_builder_variant_t builder_variant) {
  lv_obj_t *obj = lv_menu_cont_create(parent);

  lv_obj_t *img = NULL;
  lv_obj_t *label = NULL;

  if (icon) {
    img = lv_img_create(obj);
    lv_img_set_src(img, icon);
  }

  if (txt) {
    label = lv_label_create(obj);
    lv_label_set_text(label, txt);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_flex_grow(label, 1);
  }

  if (builder_variant == LV_MENU_ITEM_BUILDER_VARIANT_2 && icon && txt) {
    lv_obj_add_flag(img, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    lv_obj_swap(img, label);
  }

  return obj;
}

static void back_event_handler(lv_event_t *e) {
  lv_obj_t *obj = lv_event_get_target(e);
  lv_obj_t *menu = lv_event_get_user_data(e);

  if (lv_menu_back_btn_is_root(menu, obj)) {
    //_ui_screen_change( &ui_Home_Screen, LV_SCR_LOAD_ANIM_NONE, 0, 0,
    //&ui_Home_Screen_screen_init);
  }
}

////////////////////////////////////////////////////////////
///////////////////////// WIFI /////////////////////////////
////////////////////////////////////////////////////////////

#define DEFAULT_SCAN_LIST_SIZE 8
/*
static void print_auth_mode(int authmode)
{
    switch (authmode) {
    case WIFI_AUTH_OPEN:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_OPEN");
        break;
    case WIFI_AUTH_OWE:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_OWE");
        break;
    case WIFI_AUTH_WEP:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WEP");
        break;
    case WIFI_AUTH_WPA_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA_PSK");
        break;
    case WIFI_AUTH_WPA2_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA2_PSK");
        break;
    case WIFI_AUTH_WPA_WPA2_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA_WPA2_PSK");
        break;
    case WIFI_AUTH_WPA2_ENTERPRISE:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA2_ENTERPRISE");
        break;
    case WIFI_AUTH_WPA3_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA3_PSK");
        break;
    case WIFI_AUTH_WPA2_WPA3_PSK:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA2_WPA3_PSK");
        break;
    default:
        ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_UNKNOWN");
        break;
    }
}

static void print_cipher_type(int pairwise_cipher, int group_cipher)
{
    switch (pairwise_cipher) {
    case WIFI_CIPHER_TYPE_NONE:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_NONE");
        break;
    case WIFI_CIPHER_TYPE_WEP40:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_WEP40");
        break;
    case WIFI_CIPHER_TYPE_WEP104:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_WEP104");
        break;
    case WIFI_CIPHER_TYPE_TKIP:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_TKIP");
        break;
    case WIFI_CIPHER_TYPE_CCMP:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_CCMP");
        break;
    case WIFI_CIPHER_TYPE_TKIP_CCMP:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_TKIP_CCMP");
        break;
    case WIFI_CIPHER_TYPE_AES_CMAC128:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_AES_CMAC128");
        break;
    case WIFI_CIPHER_TYPE_SMS4:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_SMS4");
        break;
    case WIFI_CIPHER_TYPE_GCMP:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_GCMP");
        break;
    case WIFI_CIPHER_TYPE_GCMP256:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_GCMP256");
        break;
    default:
        ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_UNKNOWN");
        break;
    }

switch (group_cipher) {
    case WIFI_CIPHER_TYPE_NONE:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_NONE");
        break;
    case WIFI_CIPHER_TYPE_WEP40:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_WEP40");
        break;
    case WIFI_CIPHER_TYPE_WEP104:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_WEP104");
        break;
    case WIFI_CIPHER_TYPE_TKIP:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_TKIP");
        break;
    case WIFI_CIPHER_TYPE_CCMP:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_CCMP");
        break;
    case WIFI_CIPHER_TYPE_TKIP_CCMP:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_TKIP_CCMP");
        break;
    case WIFI_CIPHER_TYPE_SMS4:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_SMS4");
        break;
    case WIFI_CIPHER_TYPE_GCMP:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_GCMP");
        break;
    case WIFI_CIPHER_TYPE_GCMP256:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_GCMP256");
        break;
    default:
        ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_UNKNOWN");
        break;
    }
}
*/
uint16_t number = DEFAULT_SCAN_LIST_SIZE;
wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];
uint16_t ap_count = 0;

static int s_retry_num = 0;
#define EXAMPLE_ESP_MAXIMUM_RETRY 5
static EventGroupHandle_t s_wifi_event_group;
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_OPEN
#define ESP_WIFI_SAE_MODE WPA3_SAE_PWE_HUNT_AND_PECK

static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data) {
  if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_SCAN_DONE) {

    memset(ap_info, 0, sizeof(ap_info));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, ap_info));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));

    for (int i = 0; (i < DEFAULT_SCAN_LIST_SIZE) && (i < ap_count); i++) {
      // ESP_LOGI(TAG, "SSID \t\t%s", ap_info[i].ssid);
      // ESP_LOGI(TAG, "RSSI \t\t%d", ap_info[i].rssi);
      sprintf(somestring, "%s", ap_info[i].ssid);
      lv_dropdown_add_option(ui_WifiDropdown, somestring, i);
      // print_auth_mode(ap_info[i].authmode);
      if (ap_info[i].authmode != WIFI_AUTH_WEP) {
        // print_cipher_type(ap_info[i].pairwise_cipher,
        // ap_info[i].group_cipher);
      }
      // ESP_LOGI(TAG, "Channel \t\t%d\n", ap_info[i].primary);
    }

    if (ap_count == 0) {
      lv_dropdown_add_option(ui_WifiDropdown, "No Wifi Networks found", 0);
    }
  }

  if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
    ESP_LOGI(TAG, "Wifi Connect");
    ESP_ERROR_CHECK_WITHOUT_ABORT(esp_wifi_connect());
  } else if (event_base == WIFI_EVENT &&
             event_id == WIFI_EVENT_STA_DISCONNECTED) {
    if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {
      esp_wifi_connect();
      s_retry_num++;
      ESP_LOGI(TAG, "retry to connect to the AP");

    } else {
      xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
    }
    ESP_LOGI(TAG, "connect to the AP fail");
    lv_label_set_text(ui_WifiStatusLabel, "connect fail");
  } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
    ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
    ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
    lv_label_set_text(ui_WifiStatusLabel, "connected");
    s_retry_num = 0;
    xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    wifi_scan();
  }
}

esp_netif_t *sta_netif;
esp_event_handler_instance_t instance_any_id;
esp_event_handler_instance_t instance_got_ip;
static EventGroupHandle_t s_wifi_event_group;
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1

void wifi_init(void) {
  my_app.wifi_on = 1;
  s_wifi_event_group = xEventGroupCreate();

  ESP_ERROR_CHECK(esp_netif_init());

  sta_netif = esp_netif_create_default_wifi_sta();

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&cfg));

  ESP_ERROR_CHECK(esp_event_handler_instance_register(
      WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL,
      &instance_any_id));
  ESP_ERROR_CHECK(esp_event_handler_instance_register(
      IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL,
      &instance_got_ip));

  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK(esp_wifi_start());
}

void wifi_scan(void) {
  if (my_app.wifi_on != 1)
    wifi_init();

  lv_dropdown_clear_options(ui_WifiDropdown);
  esp_wifi_scan_start(NULL, false);
}

void wifi_connect(void) {

  log_memory_info();

  const char *pw = lv_textarea_get_text(ui_WifiPassword);
  char ssid[128];
  lv_dropdown_get_selected_str(ui_WifiDropdown, ssid, sizeof(ssid));

  wifi_config_t wifi_config = {};
  strcpy((char *)wifi_config.sta.ssid, ssid);
  strcpy((char *)wifi_config.sta.password, pw);
  /* Authmode threshold resets to WPA2 as default if password matches WPA2
   * standards (pasword len => 8). If you want to connect the device to
   * deprecated WEP/WPA networks, Please set the threshold value to
   * WIFI_AUTH_WEP/WIFI_AUTH_WPA_PSK and set the password with length and format
   * matching to WIFI_AUTH_WEP/WIFI_AUTH_WPA_PSK standards.
   */
  wifi_config.sta.threshold.authmode = ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD;
  wifi_config.sta.sae_pwe_h2e = WPA3_SAE_PWE_BOTH;
  // wifi_config.sta.sae_pwe_h2e = EXAMPLE_H2E_IDENTIFIER;

  ESP_LOGI(TAG, "wifi_init_sta finished.");

  ESP_ERROR_CHECK(esp_wifi_stop());
  ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
  ESP_ERROR_CHECK(esp_wifi_start());

  /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or
   * connection failed for the maximum number of re-tries (WIFI_FAIL_BIT). The
   * bits are set by wifi_event_handler() (see above) */
  EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                         WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                         pdFALSE, pdFALSE, portMAX_DELAY);

  /* xEventGroupWaitBits() returns the bits before the call returned, hence we
   * can test which event actually happened. */
  if (bits & WIFI_CONNECTED_BIT) {
    ESP_LOGI(TAG, "connected to ap SSID:%s password:%s", "SSID", "PASS");
    my_app.wifi_connected = 1;
    // vStartOtaTask();
  } else if (bits & WIFI_FAIL_BIT) {
    ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s", "SSID", "PASS");
    my_app.wifi_connected = 0;
  } else {
    ESP_LOGE(TAG, "UNEXPECTED EVENT");
    my_app.wifi_connected = 0;
  }
}

void wifi_off(void) {
  my_app.wifi_on = 0;
  esp_netif_destroy_default_wifi(sta_netif);
  esp_wifi_disconnect();
  esp_wifi_stop();
  esp_wifi_deinit();
  lv_dropdown_clear_options(ui_WifiDropdown);

  ESP_ERROR_CHECK(esp_event_handler_instance_unregister(
      WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler));
  ESP_ERROR_CHECK(esp_event_handler_instance_unregister(
      IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler));
}

////////////////////////////////////////////////////////////
/////////////////////// HELPERS ////////////////////////////
////////////////////////////////////////////////////////////

void log_memory_info() {
  ESP_LOGI(TAG, "TOTAL: %d", heap_caps_get_total_size(MALLOC_CAP_INTERNAL));
  ESP_LOGI(TAG, "FREE: %d", heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
  ESP_LOGI(TAG, "LARGEST BLOCK: %d",
           heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL));
}
