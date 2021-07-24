/* ************************************************************************ */
/*!
   \file
   \brief       Helper functions for reading and writing settings to a file.

*/
/* ************************************************************************ */
#include <settings.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"


#if 1
#define vswprintf_s swprintf
#define vsprintf_s snprintf
#define _strtoui64 strtoull
#define vswprintf_s swprintf
#define vsprintf_s snprintf
#define sprintf_s snprintf
#define strcpy_s strcpy
#endif // 1

/* ************************************************************************ */

static const char TAG[] = "settings";



static class Settings 
{
private:
	nvs_handle_t my_handle;;
public :
    Settings()
    {
    	my_handle = 0;
    }
    void init(void)
    {
		// Initialize NVS
		esp_err_t err = nvs_flash_init();
		if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) 
		{
			// NVS partition was truncated and needs to be erased
			// Retry nvs_flash_init
			ESP_ERROR_CHECK (nvs_flash_erase());
			err = nvs_flash_init();
		}
		ESP_ERROR_CHECK(err);
		// Open
		printf("\n");
		printf("Opening Non-Volatile Storage (NVS) handle... ");
		esp_err_t result = nvs_open("storage", NVS_READWRITE, &my_handle);
		if (result != ESP_OK) {
			printf("Error (%s) opening NVS handle!\n", esp_err_to_name(result));
		} else {
			printf("Done\n");
		}
        return;
    }

    ~Settings()
    {
        // Close
    }


    int8_t getS8(const char section[], const char key[], const int8_t defaultValue)
    {
    	int8_t value;
    	esp_err_t error = nvs_get_i8(my_handle, key, &value);
        if (error != ESP_OK)
        {
        	value = defaultValue;
        	this->setS8(section, key, value);
        }
        ESP_LOGI(TAG, "setS8, section = %s, key = %s, value = %i", section, key, value);
    	return value;
    }

    int16_t getS16(const char section[], const char key[], const int16_t defaultValue)
    {
    	int16_t value;
    	esp_err_t error = nvs_get_i16(my_handle, key, &value);
        if (error != ESP_OK)
        {
        	value = defaultValue;
        	this->setS16(section, key, value);
        }
        ESP_LOGI(TAG, "getS16, section = %s, key = %s, value = %i", section, key, value);
    	return value;
    }

    int32_t getS32(const char section[], const char key[], const int32_t defaultValue)
    {
    	int32_t value;
    	esp_err_t error = nvs_get_i32(my_handle, key, &value);
        if (error != ESP_OK)
        {
        	value = defaultValue;
        	this->setS32(section, key, value);
        }
        ESP_LOGI(TAG, "getS32, section = %s, key = %s, value = %i", section, key, value);
    	return value;
    }

    int64_t getS64(const char section[], const char key[], const int64_t defaultValue)
    {
    	int64_t value;
    	esp_err_t error = nvs_get_i64(my_handle, key, &value);
        if (error != ESP_OK)
        {
        	value = defaultValue;
        	this->setS64(section, key, value);
        }
        ESP_LOGI(TAG, "getS64, section = %s, key = %s, value = %lli", section, key, value);
    	return value;
    }

    uint8_t getU8(const char section[], const char key[], const uint8_t defaultValue)
    {
    	uint8_t value;
    	esp_err_t error = nvs_get_u8(my_handle, key, &value);
        if (error != ESP_OK)
        {
        	value = defaultValue;
        	this->setU8(section, key, value);
        }
        ESP_LOGI(TAG, "getU8, section = %s, key = %s, value = %u", section, key, value);
    	return value;
    }

    uint16_t getU16(const char section[], const char key[], const uint16_t defaultValue)
    {
    	uint16_t value;
    	esp_err_t error = nvs_get_u16(my_handle, key, &value);
        if (error != ESP_OK)
        {
        	value = defaultValue;
        	this->setU16(section, key, value);
        }
        ESP_LOGI(TAG, "getU16, section = %s, key = %s, value = %u", section, key, value);
    	return value;
    }

    uint32_t getU32(const char section[], const char key[], const uint32_t defaultValue)
    {
    	uint32_t value;
    	esp_err_t error = nvs_get_u32(my_handle, key, &value);
        if (error != ESP_OK)
        {
        	value = defaultValue;
        	this->setU32(section, key, value);
        }
        ESP_LOGI(TAG, "getU32, section = %s, key = %s, value = %u", section, key, value);
    	return value;
    }

    uint64_t getU64(const char section[], const char key[], const uint64_t defaultValue)
    {
    	uint64_t value;
    	esp_err_t error = nvs_get_u64(my_handle, key, &value);
        if (error != ESP_OK)
        {
        	value = defaultValue;
        	this->setU64(section, key, value);
        }
        ESP_LOGI(TAG, "getU64, section = %s, key = %s, value = %llu", section, key, value);
    	return value;
    }

    uint64_t getX64(const char section[], const char key[], const uint64_t defaultValue)
    {
    	uint64_t value;
    	esp_err_t error = nvs_get_u64(my_handle, key, &value);
        if (error != ESP_OK)
        {
        	value = defaultValue;
        	this->setX64(section, key, value);
        }
        ESP_LOGI(TAG, "getX64, section = %s, key = %s, value = %llX", section, key, value);
    	return value;
    }

    size_t getString(const char section[], const char key[], const char defaultValue[], char captionOut[], size_t size)
    {

        esp_err_t error = nvs_get_str(my_handle, key, captionOut, &size);
        if (error != ESP_OK)
        {
            if (defaultValue == nullptr)
            {
                return (size_t)0U;
            }
        	this->setString(section, key, defaultValue);
        }
        ESP_LOGI(TAG, "getString, section = %s, key = %s, value = %s", section, key, captionOut);
        return strlen(captionOut);
    }


    void setS8(const char section[], const char key[], const int8_t value)
    {
        ESP_LOGI(TAG, "setS8, section = %s, key = %s, value = %i", section, key, value);
        nvs_set_i8(my_handle, key, value);
		printf("Committing updates in NVS ... ");
		esp_err_t err = nvs_commit(my_handle);
		ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
    }

    void setS16(const char section[], const char key[], const int16_t value)
    {
        ESP_LOGI(TAG, "setS16, section = %s, key = %s, value = %i", section, key, value);
        nvs_set_i16(my_handle, key, value);
		printf("Committing updates in NVS ... ");
		esp_err_t err = nvs_commit(my_handle);
		ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
    }

    void setS32(const char section[], const char key[], const int32_t value)
    {
        ESP_LOGI(TAG, "setS32, section = %s, key = %s, value = %i", section, key, value);
        nvs_set_i32(my_handle, key, value);
		printf("Committing updates in NVS ... ");
		esp_err_t err = nvs_commit(my_handle);
		ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
    }

    void setS64(const char section[], const char key[], const int64_t value)
    {
        ESP_LOGI(TAG, "setS64, section = %s, key = %s, value = %lli", section, key, value);
        nvs_set_i64(my_handle, key, value);
		printf("Committing updates in NVS ... ");
		esp_err_t err = nvs_commit(my_handle);
		ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
    }

    void setU8(const char section[], const char key[], const uint8_t value)
    {
        ESP_LOGI(TAG, "setU8, section = %s, key = %s, value = %u", section, key, value);
        nvs_set_u8(my_handle, key, value);
		printf("Committing updates in NVS ... ");
		esp_err_t err = nvs_commit(my_handle);
		ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
    }

    void setU16(const char section[], const char key[], const uint16_t value)
    {
        ESP_LOGI(TAG, "setU16, section = %s, key = %s, value = %u", section, key, value);
        nvs_set_u16(my_handle, key, value);
		printf("Committing updates in NVS ... ");
		esp_err_t err = nvs_commit(my_handle);
		ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
    }

    void setU32(const char section[], const char key[], const uint32_t value)
    {
        ESP_LOGI(TAG, "setU32, section = %s, key = %s, value = %u", section, key, value);
        nvs_set_u32(my_handle, key, value);
		printf("Committing updates in NVS ... ");
		esp_err_t err = nvs_commit(my_handle);
		ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
    }

    void setU64(const char section[], const char key[], const uint64_t value)
    {
        ESP_LOGI(TAG, "setU64, section = %s, key = %s, value = %llu", section, key, value);
        nvs_set_u64(my_handle, key, value);
		printf("Committing updates in NVS ... ");
		esp_err_t err = nvs_commit(my_handle);
		ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
    }

    void setX64(const char section[], const char key[], const uint64_t value)
    {
        ESP_LOGI(TAG, "setX64, section = %s, key = %s, value = %llX", section, key, value);
        nvs_set_u64(my_handle, key, value);
		printf("Committing updates in NVS ... ");
		esp_err_t err = nvs_commit(my_handle);
		ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
    }

    void setString(const char section[], const char key[], const char value[])
    {
        ESP_LOGI(TAG, "setString, section = %s, key = %s, value = %s", section, key, value);
        nvs_set_str(my_handle, key, value);
		printf("Committing updates in NVS ... ");
		esp_err_t err = nvs_commit(my_handle);
		ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
    }

    void eraseString(const char section[], const char key[])
    {
        ESP_LOGI(TAG, "erase_item, section = %s, key = %s", section, key);
        nvs_erase_key(my_handle, key);
		printf("Committing updates in NVS ... ");
		esp_err_t err = nvs_commit(my_handle);
		ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
    }


} s_settings;



void Settings_init(void)
{
	s_settings.init();
}

/* ************************************************************************ */

int8_t getS8(const char section[], const char key[], const int8_t defaultValue)
{
	return s_settings.getS8(section, key, defaultValue);
}

int16_t getS16(const char section[], const char key[], const int16_t defaultValue)
{
	return s_settings.getS16(section, key, defaultValue);
}

int32_t getS32(const char section[], const char key[], const int32_t defaultValue)
{
	return s_settings.getS32(section, key, defaultValue);
}

int64_t getS64(const char section[], const char key[], const int64_t defaultValue)
{
    return s_settings.getS64(section, key, defaultValue);
}

uint8_t getU8(const char section[], const char key[], const uint8_t defaultValue)
{
	return s_settings.getU8(section, key, defaultValue);
}

uint16_t getU16(const char section[], const char key[], const uint16_t defaultValue)
{
	return s_settings.getU16(section, key, defaultValue);
}

uint32_t getU32(const char section[], const char key[], const uint32_t defaultValue)
{
	return s_settings.getU32(section, key, defaultValue);
}

uint64_t getU64(const char section[], const char key[], const uint64_t defaultValue)
{
	return s_settings.getU64(section, key, defaultValue);
}

uint64_t getX64(const char section[], const char key[], const uint64_t defaultValue)
{
	return s_settings.getX64(section, key, defaultValue);
}

size_t getString(const char section[], const char key[], const char defaultValue[], char caption[], size_t size)
{
	return s_settings.getString(section, key, defaultValue, caption, size);
}

void setS8(const char section[], const char key[], const int8_t value)
{
	return s_settings.setS8(section, key, value);
}

void setS16(const char section[], const char key[], const int16_t value)
{
	return s_settings.setS16(section, key, value);
}

void setS32(const char section[], const char key[], const int32_t value)
{
	return s_settings.setS32(section, key, value);
}

void setS64(const char section[], const char key[], const int64_t value)
{
	return s_settings.setS64(section, key, value);
}

void setU8(const char section[], const char key[], const uint8_t value)
{
	s_settings.setU8(section, key, value);
}

void setU16(const char section[], const char key[], const uint16_t value)
{
	s_settings.setU16(section, key, value);
}

void setU32(const char section[], const char key[], const uint32_t value)
{
	s_settings.setU32(section, key, value);
}

void setU64(const char section[], const char key[], const uint64_t value)
{
	s_settings.setU64(section, key, value);
}

void setX64(const char section[], const char key[], const uint64_t value)
{
	s_settings.setX64(section, key, value);
}

void setString(const char section[], const char key[], const char value[])
{
	s_settings.setString(section, key, value);
}
void eraseString(const char section[], const char key[])
{
	s_settings.eraseString(section, key);
}



/* ************************************************************************ */
