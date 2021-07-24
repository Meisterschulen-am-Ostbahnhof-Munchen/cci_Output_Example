/* ************************************************************************ */
/*! \file
   \brief      Hardware simulation interface
   \author     Wegscheider Peter
   \date       Created XX.02.15
   \copyright  Wegscheider Hammerl Ingenieure Partnerschaft
   \par        History:
   \par
   02.02.2015 - author P. Wegscheider
   - created
   \par
   08.12.2016 - author P. Wegscheider
   - updated

*/
/* ************************************************************************ */
#ifndef DEF_APP_HW_H
#define DEF_APP_HW_H
/* ************************************************************************ */

#include "IsoCommonDef.h"   // required for CCI_CAN_API

#ifndef _lint
#if defined(_MSC_VER) && (_MSC_VER<1900)
// <stdint.h> is not available in e.g. visual studio C++ 2008
typedef signed char        int8_t;
typedef short              int16_t;
typedef long               int32_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned long      uint32_t;
#else // defined(_MSC_VER) && (_MSC_VER<1900)
#include <stdint.h>
#endif // defined(_MSC_VER) && (_MSC_VER<1900)
#include <stdarg.h>
#else
typedef signed char        int8_t;
typedef short              int16_t;
typedef long               int32_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned long      uint32_t;

typedef char* va_list;
#endif

/* ************************************************************************ */

typedef char char_t;
typedef int  int_t;

/* ************************************************************************ */
#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************ */

#if !defined(DISABLE_CMDLINE_PARSING)
   void     hw_SetConfiguration(int_t argc, char_t* argv[]);
#endif /* !defined(DISABLE_CMDLINE_PARSING) */
   void     hw_Init(void);
   void     hw_Shutdown(void);
   uint8_t  hw_PowerSwitchIsOn(void);

   void     hw_DebugPrint(const char_t format[], ...); /*lint !e960 */
   void     hw_DebugTrace(const char_t format[], ...); /*lint !e960 */
   void     hw_LogError(const char_t format[], ...);   /*lint !e960 */

   void     hw_vDebugPrint(const char_t format[], va_list args); 
   void     hw_vDebugTrace(const char_t format[], va_list args); 

   int32_t  hw_GetTimeMs(void);

#if !defined(CCI_CAN_API)   // the declaration is not required if CAN is out sourced into a DLL
   void     hw_CanInit(uint8_t maxCanNodes_u8);
   void     hw_CanClose(void);
   int16_t  hw_CanSendMsg(uint8_t canNode_u8, uint32_t canId_u32, const uint8_t canData_au8[], uint8_t canDataLength_u8);
   int16_t  hw_CanReadMsg(uint8_t canNode_u8, uint32_t *canId_pu32, uint8_t canData_pau8[], uint8_t *canDataLength_pu8);
   int16_t  hw_CanGetFreeSendMsgBufferSize(uint8_t canNode_u8);
#endif // !defined(CCI_CAN_API) 

   void     hw_SimDoSleep(uint32_t milliseconds);
   int_t    hw_SimGetKbHit(void);
   int_t    hw_SimGetCharEx(uint8_t noEcho);

/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* DEF_APP_HW_H */
/* ************************************************************************ */

