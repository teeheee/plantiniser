#include <unity.h>
#include "config_items.h"
#include "config_base_item.h"

void test_string_item_checksum(void) 
{
   StringItem wlan_ssid = StringItem(10, "WLAN SSID");
   //TEST_ASSERT_FALSE(wlan_ssid.is_data_valid());
}

int main() 
{
    UNITY_BEGIN();
    UNITY_END();
    return 0;
}