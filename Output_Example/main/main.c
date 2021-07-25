/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "AppHW.h"
#include "sdkconfig.h"

#include "IsoCommonDef.h"
#include "IsoCommonApi.h"
#include "settings.h"
#include "esp_err.h"
#include "spiffs_access.h"
extern int isobus_main(int_t argc, char_t* argv[]);
extern void init_GPIO(void);
void app_main(void)
{

	hw_DebugPrint("app_main \n");


	init_GPIO();

	/* Initialize file storage */
	ESP_ERROR_CHECK(init_spiffs());


	/* Initialize application */
	Settings_init();










	isobus_main(0, NULL);

}
