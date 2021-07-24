/*
 * SerialNumber.c
 *
 *  Created on: 29.09.2020
 *      Author: hoepffr
 */

#include <stdio.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include "SerialNumber.h"

static const char *TAG = "SerialNumber";

uint32_t  u32SeriNoGet(void)
{



    uint8_t b[6];
    esp_efuse_mac_get_default(b);

    b[0] = 0x00;
    b[1] = 0x00;
    b[2] = 0x00;
    b[3] = b[3] & 0x1f; //cut 24 bits to 21


    ESP_LOGI(TAG,"SHORT-MAC = ## " MACSTR " ##", MAC2STR(b));


	return b[3] << 16 | b[4] << 8 | b[5];

}

void Serial_Number_VariableGet(char * c_Serial_Number_Variable)
{
    uint8_t a[6];
    esp_efuse_mac_get_default(a);

    ESP_LOGI(TAG,"MAC = ## " MACSTR " ##", MAC2STR(a));

    //Returns e.g.
    //
    // 123456789+23456789+234567
    // ##MAC:24:6f:28:42:e9:50##
    // is a 28 character String.





    sprintf(&c_Serial_Number_Variable[0], "##MAC:%02x:%02x:%02x:%02x:%02x:%02x##",  (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]);


}


