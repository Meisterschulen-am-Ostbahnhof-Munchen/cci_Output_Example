/* ************************************************************************ */
/*!
   \file
   \brief      Sample main function
   \details    This file contains a simple ISOBUS ECU driver sample how to setup the library. \n
               This file is only used for generating the doxygen documentation.

   \author     Wegscheider Peter
   \date       Created 13.04.2015

   \copyright  Wegscheider Hammerl Ingenieure Partnerschaft

   \par  History:
   \par
   13.04.2015 - author P. Wegscheider
   - Created 
*/
/* ************************************************************************ */

#include "AppCommon/AppHW.h" 

#include "IsoDef.h"
#include "App_Base.h"


#include "AppCommon/AppOutput.h"
#include "App_VTClient.h"  /* needed only for DoKeyBoard() */
//#include "App_TCClient.h"  /* needed only for DoKeyBoard() */

#include "../Samples/AddOn/AppIso_Output.h"  /* relative to IsoLib */
#include "AppIso_Diagnostic.h"
#include "sdkconfig.h"

/* **************************  function declarations  ********************* */

/* **************************  function declarations  *********************** */




void AppHW_Init(void);
void AppIso_Init(void);
void AppIso_Cyclic(void);


static void PrintKeyBoard(void);
static void DoKeyBoard(void);



#if(CONFIG_CAN2IP_MODE_ON)
extern void app_main_tcp_server(void);
#endif


/* **************************  declare private functions ****************** */

/* Needed callback functions for the ISOBUS driver */
static void    CB_Watchdog(void);
static void    CB_ReportError(iso_u8 functionId_u8, iso_u8 locationId_u8, iso_s16 errorCode_s16, iso_s32 s32TimeMs);
static iso_s16 CB_CanSend(iso_u8 canNode_u8, iso_u32 canId_u32, const iso_u8 canData_au8[], iso_u8 canDataLength_u8);
static iso_s16 CB_GetSendMsgFiFoSize(iso_u8 u8CanNode, iso_u8 u8MsgPrio);
static iso_s32 CB_GetTimeMs(void);

/* CAN message receive and forward function */
static void Do_ReceiveCanMessages(void);

/* **************************  const data initialization ****************** */

/* **************************  module global data  ************************ */

iso_bool b__AppRuning = ISO_TRUE;

/* ************************************************************************ */
/*! \brief Sample main function */
int isobus_main(int_t argc, char_t* argv[])
{
#if !defined(DISABLE_CMDLINE_PARSING)
   hw_SetConfiguration(argc, argv);
#endif 
   PrintKeyBoard();
   hw_DebugPrint("ISO Application starts \n");
   /* Initialize application */
   AppHW_Init();

#if defined(APP_TEST_CAN_DRIVER)
   {  /* Check CAN driver send function  */
      iso_u8  abData[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
      iso_s16 s16Ret = hw_CanSendMsg(ISO_CAN_VT, 0x18000000, abData, 8);
      if (s16Ret < 0)
      {
         #if defined(linux)
         hw_DebugPrint("CAN bus error - check socket CAN configuration \n");
         #else
         hw_DebugPrint("CAN bus error - check WHEPS_candriver.ini in build bin folder \n");
         #endif 
         while (hw_SimGetKbHit() == 0);
         hw_Shutdown();
         return 1;
      }
   }
#endif 

   /* Initialize ISOBUS library and samples */
   AppIso_Init();
#if(CONFIG_CAN2IP_MODE_ON)
	//this Server/Client Pair is for CAN2IP only !
	//do not start it when CAN2IP is off, this would write in a non initialized Queue.
   hw_DebugPrint("app_main_tcp_server");
	app_main_tcp_server();
	hw_DebugPrint("app_main_tcp_server DONE");
	hw_DebugPrint("app_main_tcp DONE");
#endif
   /* sample main loop */
   while (hw_PowerSwitchIsOn() && (b__AppRuning == ISO_TRUE))
   {
      /* run cyclic application function */
      AppIso_Cyclic();

      hw_SimDoSleep(ISO_NM_LOOPTIME);  // Simulate loop time "5ms"
      DoKeyBoard();
   }

   hw_Shutdown();

   return 0;
}

/* **************************  implementation - public functions  ********* */

/*! \brief Sample application initialization */
void AppHW_Init(void)
{  /* Initialize the hardware*/
   hw_Init();
   hw_CanInit(ISO_CAN_NODES);
}

/*! \brief Sample ISOBUS library initialization */
void AppIso_Init(void)
{
   iso_u8  u8I;
   iso_s16 s16Ret, s16FnRet;
   iso_u32 u32version;

   u32version = IsoDriverVersionRead();
   hw_DebugPrint("\nISOBUS library version: %d \n\n", u32version);

   /* Initialize the core ISOBUS driver library package */
   s16Ret = iso_CoreInit( CB_GetTimeMs, CB_Watchdog, CB_ReportError,
                          CB_CanSend, CB_GetSendMsgFiFoSize,
                          IsoCbBaseDataDistributor, IsoCbBaseNetworkDistributor, 0 );
   /* do next step for each CAN node */
   for (u8I = 0u; u8I < ISO_CAN_NODES; u8I++)
   {  /* set number of (E)TP messages for each cycle (V10: Replaced iso_DlTPRepeatSet() with iso_CoreTPRepeatSet()) */
      s16FnRet = iso_CoreTPRepeatSet(u8I, 5);
      s16Ret = (s16Ret == E_NO_ERR) ? s16FnRet : s16Ret;
   }

   /* Initialize the base ISOBUS driver library package */
#if defined(ISO_MODULE_CLIENTS)  /* same as #if defined(_LAY6_) || defined(_LAY10_) || defined(_LAY13_) || ... */
   s16FnRet = iso_BaseInit(CB_GetTimeMs, CB_Watchdog, CB_ReportError,
      IsoCbDataOfBasicDistributor, 0 );
#else  /* not defined(ISO_MODULE_CLIENTS) */
   s16FnRet = iso_BaseInit(CB_GetTimeMs, CB_Watchdog, CB_ReportError, 0, 0);
#endif /* not defined(ISO_MODULE_CLIENTS) */
   s16Ret = (s16Ret == E_NO_ERR) ? s16FnRet : s16Ret;
#if defined(ISO_MODULE_DIAG)
   iso_BaseDiagSetCbForResp(&processPart12PGN);
#endif /* defined(ISO_MODULE_DIAG) */

#if defined(ISO_MODULE_CLIENTS) /* same as #if defined(_LAY6_) || defined(_LAY10_) || defined(_LAY13_) || ... */
   /* Initialize the ISOBUS driver library clients modules (Hint: LAY14 only in combination with LAY6) */
   s16FnRet = IsoClientsInit(CB_GetTimeMs, CB_Watchdog, CB_ReportError);
   s16Ret = (s16Ret == E_NO_ERR) ? s16FnRet : s16Ret;
#endif /* ISO_MODULE_CLIENTS */

   /* Initialize ISOBUS implement sample */
   AppImpl_Ignition(ISO_TRUE, 0);
   
   if (s16Ret != E_NO_ERR)
   {
      hw_LogError("AppIso_Init error: %i \n", s16Ret);
   }
}

/* ************************************************************************ */
/*! \brief Sample: cyclic function */
void AppIso_Cyclic(void)
{
   /* Get the incoming CAN messages and forward them to the ISOBUS driver */
   Do_ReceiveCanMessages();

   /* Call the implement sample cyclic function */
   AppImpl_doProcess();

   /* Call the ISOBUS driver cyclic functions */
   iso_CoreCyclic();
   iso_BaseCyclic();
#if defined(ISO_MODULE_CLIENTS) /* same as #if defined(_LAY6_) || defined(_LAY10_) || defined(_LAY13_) || ... */
   (void) IsoClientsCyclicCall();
#endif /* defined(ISO_MODULE_CLIENTS) */
}


/* **************************  implementation - static functions  ********* */

/*! \brief ISOBUS driver dummy watchdog callback function */
static void CB_Watchdog(void)
{

}

/*! \brief ISOBUS driver sample error report callback function */
static void CB_ReportError(iso_u8 functionId_u8, iso_u8 locationId_u8, iso_s16 errorCode_s16, iso_s32 s32TimeMs)
{
   //hw_LogError("ISOBUS error: %i, location: %i, function: %i, time: %i \n", errorCode_s16, locationId_u8, functionId_u8, s32TimeMs);
   CbErrorOutp(functionId_u8, locationId_u8, errorCode_s16, s32TimeMs);
}

/*! \brief ISOBUS driver CAN message send callback function */
static iso_s16 CB_CanSend(iso_u8 canNode_u8, iso_u32 canId_u32, const iso_u8 canData_au8[], iso_u8 canDataLength_u8)
{
   return hw_CanSendMsg(canNode_u8, canId_u32, canData_au8, canDataLength_u8);
}

/*! \brief ISOBUS driver "Get CAN message FIFO size" callback function */
static iso_s16 CB_GetSendMsgFiFoSize(iso_u8 u8CanNode, iso_u8 u8MsgPrio)
{
    (void)u8CanNode;
    (void)u8MsgPrio;
    return hw_CanGetFreeSendMsgBufferSize(u8CanNode);
}

/* ************************************************************************ */

/*! \brief ISOBUS driver Timestamp callback function
   \details Must return the time in milliseconds. \n
   The return value must be greater or equal zero. \n
   An overflow is not allowed.... */
static iso_s32 CB_GetTimeMs(void)
{
   return (iso_s32)hw_GetTimeMs();
}

/*! \brief CAN message receive and forward function
   \details This sample function forwards the incoming CAN messages to the ISOBUS driver */
   /*! [Do_ReceiveCanMessages] */
static void Do_ReceiveCanMessages(void)
{
   uint8_t  canNode_u8;
   uint32_t canId_u32;
   uint8_t  canData_au8[8];
   uint8_t  canDataLength_u8;

   iso_bool msgFound;
   uint8_t  msgCount = 0u;

   do
   {
      msgFound = ISO_FALSE;

      for (canNode_u8 = 0u; canNode_u8 < ISO_CAN_NODES; canNode_u8++)
      {
         int16_t   ret_s16;
         ret_s16 = hw_CanReadMsg(canNode_u8, &canId_u32, canData_au8, &canDataLength_u8);

         if (ret_s16 > 0)
         {  /* call the ISOBUS library receive function */
            iso_CoreCanMsgRec(canNode_u8, canId_u32, canData_au8, canDataLength_u8);
            msgFound = ISO_TRUE;
            msgCount++;
         }
      } /* end for */
   } while ((msgFound == ISO_TRUE) && (msgCount <= 40u));
}
/*! [Do_ReceiveCanMessages] */

/* ************************************************************************ */

static void PrintKeyBoard(void)
{
   hw_DebugPrint("\nCommands:\n");
   hw_DebugPrint("1 - \n");
   hw_DebugPrint("2 - VT - Close VT client \n");
   hw_DebugPrint("3 - VT - Restart VT client\n");
   hw_DebugPrint("4 - VT - Delete stored pool\n");
   hw_DebugPrint("5 - VT - Pool reload\n");
   hw_DebugPrint("6 - VT - Move to another VT\n");
   hw_DebugPrint("7 - \n");
   hw_DebugPrint("8 - \n\n");
   hw_DebugPrint("h - Help \n");
   hw_DebugPrint("q - Quit\n\n");

}


static void DoKeyBoard(void)
{
   if (hw_SimGetKbHit() != 0)
   {
      int_t c = hw_SimGetCharEx(ISO_TRUE);
      switch (c)
      {
      case '1':
         hw_DebugPrint("1  \n");
         break;
      case '2':
         hw_DebugPrint("2  - Close VT client \n");
         VTC_CloseInstance();
         break;
      case '3':
         hw_DebugPrint("3 - Restart VT client \n");
         VTC_Restart();
         break;
#if defined(_LAY6_)
      case '4':
         hw_DebugPrint("4 - Delete stored pool \n");
         VTC_PoolDeleteVersion();
         break;
      case '5':
         hw_DebugPrint("5 - Start Pool reload \n");
         VTC_PoolReload();
         break;
      case '6':
         hw_DebugPrint("6 - Move to another VT\n");
         VTC_NextVTButtonPressed();
         break;

#endif /* defined(_LAY6_) */
#if defined(_LAY10_)
      case '7':
         hw_DebugPrint("7 - \n");
         break;
      case '8': 
         hw_DebugPrint("8 - \n"); 
         break;
#endif /* defined(_LAY10_) */
      case 'h':
         PrintKeyBoard();
         break;
      case 'q':
         hw_DebugPrint("quit \n");
         b__AppRuning = ISO_FALSE;
         break;
      default: break;
      }
   }
}


/* ************************************************************************ */
