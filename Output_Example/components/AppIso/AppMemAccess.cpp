/* ************************************************************************ */


/* ************************************************************************ */
#include "IsoDef.h"

#if defined(_LAY6_)

#include <iostream>
#include <sstream>
#include <string.h>
#include "Settings/settings.h"
#include "AppMemAccess.h"

#if defined(ESP_PLATFORM)
#include <sys/param.h>
#include "esp_err.h"
#include "esp_log.h"

const char *D_D_D_D_D_D_D_I64_X = "%d=%d,%d,%d,%d,%d,%d,%I64X";
const char *D_D_D_D_D_D_D_L_X 	= "%d=%d,%d,%d,%d,%d,%d,%lX";
const char *D_D_D_D_D_D_D_LL_X 	= "%d=%d,%d,%d,%d,%d,%d,%llX";


static const char *TAG = "AppMemAccess";

#endif // def ESP_PLATFORM

using namespace std;

#if defined(_MSC_VER )
#pragma warning(disable : 4996)
#endif // defined(_MSC_VER )
#if defined(linux) || defined(ESP_PLATFORM)
#define vswprintf_s swprintf
#define vsprintf_s snprintf
#define _strtoui64 strtoull
#define vswprintf_s swprintf
#define vsprintf_s snprintf
#define sprintf_s snprintf
#endif // defined(linux) || defined(ESP_PLATFORM)

#if defined(linux)
#define USE_L_FOR_64BIT
#elif defined(__MINGW_GCC_VERSION)
#define USE_LL_FOR_64BIT
#else // defined(linux), defined(__MINGW_GCC_VERSION)
#endif // defined(linux), defined(__MINGW_GCC_VERSION)
#if defined(ESP_PLATFORM)
   #define USE_LL_FOR_64BIT
#endif // def ESP_PLATFORM

static bool parseAuxEntry(char* entry, VT_AUXAPP_T* auxEntry);
static bool getKeyByID(iso_s16 wObjID_Fun, char* key, size_t size);
static bool getValue(const VT_AUXAPP_T& auxEntry, char* value, size_t size);

extern const int FIRST_AUX;
extern const int  LAST_AUX;
/* ****************   Auxiliary Assignments  *********************************** */

iso_s16 getAuxAssignment(const char auxSection[], VT_AUXAPP_T asAuxAss[])
{

#if defined(ESP_PLATFORM)
       ESP_LOGI(TAG, "getAuxAssignment");
#endif // def ESP_PLATFORM

	iso_s16 idxAux = 0U;
   for (iso_s16 idx = FIRST_AUX; idx <= LAST_AUX; idx++)
   {
	   char buffer[64];
       char key[16];
       getKeyByID(idx, key, sizeof(key));
#if defined(ESP_PLATFORM)
       ESP_LOGI(TAG, "getKeyByID %s ", key);
#endif // def ESP_PLATFORM
       size_t len = getString(auxSection, key, nullptr, buffer, sizeof(buffer));
       ESP_LOGI(TAG, "getString:  %s", buffer);
      VT_AUXAPP_T* auxEntry = &asAuxAss[idxAux];
      if(len > 16) //TODO! this is a magic Number now.
      {
      if (parseAuxEntry(buffer, auxEntry))
      {

          char value[64];

          getValue(*auxEntry, value, sizeof(value));
          iso_DebugPrint("getAuxAssignment: %d %s %s\n", idxAux, key, value);
          idxAux++;
		  }
      }
   }
   ESP_LOGI(TAG, "getAuxAssignment found:  %d", idxAux);
   return idxAux;
}

static bool parseAuxEntry(char* entry, VT_AUXAPP_T* auxEntry)
{
    int wObjID_Fun;
    int wObjID_Input;
    int eAuxType;
    int wManuCode;
    int wModelIdentCode;
    int qPrefAssign;
    int bFuncAttribute;
    uint64_t name;
    int parameterCount = sscanf(entry,
#if defined(USE_L_FOR_64BIT)
			D_D_D_D_D_D_D_L_X, &wObjID_Fun,
#elif defined(USE_LL_FOR_64BIT)
			D_D_D_D_D_D_D_LL_X, &wObjID_Fun,
#else // !defined(USE_L_FOR_64BIT)
			D_D_D_D_D_D_D_I64_X, &wObjID_Fun,
#endif //!defined(USE_L_FOR_64BIT)
        &wObjID_Input, &eAuxType, &wManuCode, &wModelIdentCode,
        &qPrefAssign, &bFuncAttribute, &name);
    if (parameterCount == 8)
    {
        auxEntry->wObjID_Fun = static_cast<iso_u16>(wObjID_Fun);              /* Object ID of auxiliary function */
        auxEntry->wObjID_Input = static_cast<iso_u16>(wObjID_Input);          /* Object ID of auxiliary input */
        auxEntry->eAuxType = static_cast<VTAUXTYP_e>(eAuxType);      /* Function/input type (without attribute bits)
                                                            - only because of downwards compatibility  */
        auxEntry->wManuCode = static_cast<iso_u16>(wManuCode);                /* Manufacturer Code of auxiliary input device */
        auxEntry->wModelIdentCode = static_cast<iso_u16>(wModelIdentCode);    /* Model identification code of aux input device */
        auxEntry->qPrefAssign = static_cast<iso_bool>(qPrefAssign);            /* This assignment shall used for preferred assignment */
        auxEntry->bFuncAttribute = static_cast<iso_u8>(bFuncAttribute);      /* Complete function attribute byte of auxiliary function */
        memcpy(&auxEntry->baAuxName[0], &name, 8);      /* ISO name of the auxiliary input device. The bytes must be set to 0xFF if not used. */
        return true;
    }

    return false;
}

void setAuxAssignment(const char section[], VT_AUXAPP_T asAuxAss[], iso_s16 iNumberOfAssigns)
{

	char key[16];
   // erase complete section
   for (int8_t idx = FIRST_AUX; idx <= LAST_AUX; idx++)
   {
       getKeyByID(idx, key, sizeof(key));
       eraseString(section, key);
   }


   char buffer[64];

   // write aux entries
   for (int8_t idx = 0; idx < iNumberOfAssigns; idx++)
   {
      VT_AUXAPP_T* auxEntry = &asAuxAss[idx];
      getKeyByID((iso_s16)auxEntry->wObjID_Fun, key, sizeof(key));
      uint64_t name = 0;
      memcpy(&name, &auxEntry->baAuxName[0], 8);            /* ISO name of the auxiliary input device. The bytes must be set to 0xFF if not used. */
#if defined(USE_L_FOR_64BIT)
	  sprintf_s(buffer, sizeof(buffer), D_D_D_D_D_D_D_L_X,
#elif defined(USE_LL_FOR_64BIT)
	  sprintf_s(buffer, sizeof(buffer), D_D_D_D_D_D_D_LL_X,
#else // !defined(USE_L_FOR_64BIT)
	  sprintf_s(buffer, sizeof(buffer), D_D_D_D_D_D_D_I64_X,
#endif //!defined(USE_L_FOR_64BIT)
      auxEntry->wObjID_Fun, auxEntry->wObjID_Input, auxEntry->eAuxType, auxEntry->wManuCode, auxEntry->wModelIdentCode,
         auxEntry->qPrefAssign, auxEntry->bFuncAttribute, name);
      setString(section, key, buffer);
   }
}

void updateAuxAssignment(const char auxSection[], VT_AUXAPP_T* sAuxAss)
{
    if (sAuxAss->wObjID_Input != 0xFFFF)
    {
        char key[16];
        char value[64];
        getKeyByID((iso_s16)sAuxAss->wObjID_Fun, key, sizeof(key));
        getValue(*sAuxAss, value, sizeof(value));
        iso_DebugPrint("updateAuxAssignment add: %s %s\n", key, value);
        setString(auxSection, key, value);
    }
    else
    {
        iso_s16 auxCfHandle = IsoCl_GetCfHandleToName(ISO_CAN_VT, &sAuxAss->baAuxName);
        iso_u16 wModelIdentCode = 0;
        if (IsoReadAuxInputDevModIdentCode(auxCfHandle, &wModelIdentCode) == E_NO_ERR)
        {
            sAuxAss->wModelIdentCode = wModelIdentCode;
        }

        char key[16];
        getKeyByID((iso_s16)sAuxAss->wObjID_Fun, key, sizeof(key));
        iso_DebugPrint("updateAuxAssignment remove: %s\n", key);
        eraseString(auxSection, key);
    }
}

static bool getKeyByID(iso_s16 wObjID_Fun, char* key, size_t size)
{
    sprintf_s(key, size, "AUX-%d", wObjID_Fun);
    return true;
}

static bool getValue(const VT_AUXAPP_T& auxEntry, char* value, size_t size)
{
    uint64_t name = 0;
    memcpy(&name, &auxEntry.baAuxName[0], 8);            /* ISO name of the auxiliary input device. The bytes must be set to 0xFF if not used. */
#if defined(USE_L_FOR_64BIT)
	sprintf_s(value, size, D_D_D_D_D_D_D_L_X,
#elif defined(USE_LL_FOR_64BIT)
	sprintf_s(value, size, D_D_D_D_D_D_D_LL_X,
#else // !defined(USE_L_FOR_64BIT)
	sprintf_s(value, size, D_D_D_D_D_D_D_I64_X,
#endif // !defined(USE_L_FOR_64BIT)
        auxEntry.wObjID_Fun, auxEntry.wObjID_Input, auxEntry.eAuxType, auxEntry.wManuCode, auxEntry.wModelIdentCode,
    auxEntry.qPrefAssign, auxEntry.bFuncAttribute, name);
    return true;
}

/* ************************************************************************ */
#endif /* defined(_LAY6_) */
/* ************************************************************************ */
