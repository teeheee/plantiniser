#ifndef _CONFIG_H_
#define _CONFIG_H_

void config_init();
void config_manage();

bool config_has_stored_data();
const char* config_get_ssid();
const char* config_get_wifi_passkey();
const char* config_get_server_address();

#endif