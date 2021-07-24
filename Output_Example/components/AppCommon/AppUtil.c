#include "AppUtil.h"

uint16_t bufferGetU16(uint8_t data[])
{
   uint16_t u16Val;   // make linux gcc for c++ happy
   u16Val = (uint16_t)((uint16_t)data[1] << 8);
   u16Val = (uint16_t)(u16Val | (uint16_t)data[0]);
   return u16Val;    // ORG (iso_u16)((iso_u16)data[1] << 8) | (iso_u16)data[0];
}
