#include "build/temp/_test_config.c"
#include "lib/config/config_base_item.h"
#include "lib/config/config_items.h"


void test_string_item_checksum(void)

{

   StringItem wlan_ssid = StringItem(10, "WLAN SSID");

   TEST_ASSERT_FALSE(wlan_ssid.is_data_valid());

}
