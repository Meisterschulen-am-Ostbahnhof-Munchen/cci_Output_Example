/* ************************************************************************ */
/*! 
   \file
   \brief      Hardware simulation ( Windows PC CAN BUS implementation )
   \author     Wegscheider Peter
   \date       Created XX.02.15
   \copyright  Wegscheider Hammerl Ingenieure Partnerschaft
   \par        History:
   \par
   02.02.2015 - author P. Wegscheider
   - created
   \par
   22.08.2016 - author P. Wegscheider
   - modified
   \par
   01.12.2017 - author P. Wegscheider
   - Bug ID 8120:  Fixed declaration of HW_CanMsgPrint() and updated calls
*/
/* ************************************************************************ */

#include <stdio.h>
#include <string>

#include "AppHW.h"
#include "Settings/settings.h"

#if defined(_WIN32) && defined(linux)
#error _WIN32 and linux can not defined at the same time!!!
#endif 

#ifdef ESP_PLATFORM
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#endif  //ESP_PLATFORM

/* ************************************************************************ */
#if defined(_WIN32)

#include "WBZCANDriver.h"
#include <Windows.h>
#include <conio.h>   // for keyboard ...

#define USE_APP_OUTPUT
#if defined(USE_APP_OUTPUT)
   #include "AppOutput.h"
#endif /* defined(USE_APP_OUTPUT) */ 

/* ************************************************************************ */
using namespace WBZCANDRIVER;
using namespace std;

/* ************************************************************************ */


/* ************************************************************************ */

static CANDriver* pCANDriver = NULL;
static uint8_t m_MaxCanNodes_u8 = 0u;

/* ************************************************************************ */
#endif  /* defined(_WIN32) */
/* ************************************************************************ */

/* ************************************************************************ */
#if defined(linux)
#include <stdlib.h>     //used for clearing the screen
#include <time.h>       //used to get time for random number generator
#include <unistd.h>
// for terminal 
#include <sys/ioctl.h>
#include <termios.h>
// for ctrl-c
#include <signal.h>

static void signal_function(int sig);

#endif   /* defined(linux) */
/* ************************************************************************ */

/* ************************************************************************ */

static volatile uint8_t m_PowerSwitch_u8 = 0u;

/* ************************************************************************ */

void hw_Init(void)
{
#if defined(_WIN32)
   if (SetConsoleCtrlHandler(
      (PHANDLER_ROUTINE)ConsoleHandler, TRUE) == FALSE)
   {  // unable to install handler... 
      hw_DebugPrint("Unable to install console handler!\n");
   }
#endif //def _WIN32
   m_PowerSwitch_u8 = 1u;
}

void hw_Shutdown(void)
{
#if defined(_WIN32)
   if (pCANDriver)
   {
      pCANDriver->deInitialiseDriver();
      pCANDriver = 0;
   }
   m_MaxCanNodes_u8 = 0u;
#endif // def _WIN32
   m_PowerSwitch_u8 = 0u;
   hw_DebugPrint("Shutdown finished \n");
}

uint8_t hw_PowerSwitchIsOn(void)
{
   return m_PowerSwitch_u8;
}

void hw_DebugPrint(const char_t format[], ...)
{
   va_list args;
   va_start(args, format);
   vprintf(format, args);
   va_end(args);
}

void hw_vDebugPrint(const char_t format[], va_list args)
{
   vprintf(format, args);
}

void hw_DebugTrace(const char_t format[], ...)
{
#if !defined(_WIN32)
   va_list args;
   va_start(args, format);
   vprintf(format, args);
   va_end(args);
#else
   char strOut[500];
   va_list args;
   va_start(args, format);
#pragma warning(push)
#pragma warning(disable: 4996) // Deprecation
   vsprintf(strOut, format, args);
#pragma warning(pop)
   va_end(args);
   OutputDebugStringA(strOut);

#endif
}

void hw_vDebugTrace(const char_t format[], va_list args)
{
#ifndef _WIN32
   vprintf(format, args);
#else
   char strOut[500];
   #pragma warning(push)
   #pragma warning(disable: 4996) // Deprecation
   vsprintf(strOut, format, args);
   #pragma warning(pop)
   OutputDebugStringA(strOut);
#endif
}

void hw_LogError(const char_t format[], ...)
{
   va_list args;
   va_start(args, format);
   vprintf(format, args);
   va_end(args);
}

int32_t hw_GetTimeMs(void)
{
   static int32_t s_timeTickOffset = -100000; // -100000 fails getting started with driver V11.2.2

#ifdef _WIN32
   iso_s32 timeInMilliseconds = (pCANDriver) ? 
                                (int32_t)pCANDriver->getTimeStamp() : 
                                (iso_s32)GetTickCount(); // time elapsed in ms since system start (up to ~50 days); https://msdn.microsoft.com/de-de/library/windows/desktop/ms724408(v=vs.85).aspx
#else //_WIN32
    struct timespec tv; //RAII complicated or impossible
    clock_gettime(CLOCK_MONOTONIC, &tv);
    iso_s32 timeInMilliseconds = static_cast<iso_s32>(((tv.tv_sec) * 1000) + ((tv.tv_nsec) / 1000000));
#endif //def _WIN32

    static int32_t s_timeTickStart = timeInMilliseconds;

    timeInMilliseconds = (timeInMilliseconds - s_timeTickStart) + s_timeTickOffset;

#if !defined(CCI_USE_ISO_TIME)
    return timeInMilliseconds;
#else // !defined(CCI_USE_ISO_TIME)
    return timeInMilliseconds << 10;
#endif // !defined(CCI_USE_ISO_TIME)
}


/* ################### CAN Functions ################ */

#if !defined(CCI_CAN_API) && defined(_WIN32)  // the implementation is not required if CAN is out sourced into a DLL
void hw_CanInit(uint8_t maxCanNodes_u8)
{
   uint8_t i_u8;
   char_t  file_ac[100];
   m_MaxCanNodes_u8 = maxCanNodes_u8;

   pCANDriver = getCANDriverInstance();
   //pCANDriver->setStdOutStreams(&std::cerr, &std::cout); // not the can log, &std::clog );
   getString("CanConfig", "file", "WHEPS_candriver.ini", file_ac, 100UL);
   pCANDriver->initialiseDriver(file_ac);

   for (i_u8 = 1u; i_u8 <= m_MaxCanNodes_u8; i_u8++)
   {
      if (!pCANDriver->connect(i_u8))
      {
#ifdef _WIN32
         ::MessageBoxA(NULL, "Error: \"CAN init failed!\"", "Error!", MB_ICONERROR);
#endif // _WIN32
         hw_DebugPrint("CAN init failed\n");
      }
      else
      {
         hw_DebugPrint("isConnected(%d/%d)", i_u8, pCANDriver->isConnected(i_u8));
      }
   }
}

void hw_CanClose(void)
{
   uint8_t i_u8;

   if (pCANDriver == 0)
   {
      return;
   }

   for (i_u8 = 1u; i_u8 <= m_MaxCanNodes_u8; i_u8++)
   {
      if (pCANDriver->isConnected(i_u8))
      {
         pCANDriver->disconnect(i_u8);
      }
   }
}

int16_t hw_CanSendMsg(uint8_t canNode_u8, uint32_t canId_u32, const uint8_t canData_au8[], uint8_t canDataLength_u8)
{
   CANMsg_t can_msg_send;
   int16_t  ret_16 = 0;
   int iLoop = 0;
   int  channelID;

   if (pCANDriver == 0)
   {
      return -9;  /* E_COM -> Bus off*/
   }

   can_msg_send.ID = canId_u32;
   can_msg_send.DLC = canDataLength_u8;
   can_msg_send.MsgType = 1u; /* extended */

   for (iLoop = 0; (iLoop < 8) && (iLoop < canDataLength_u8); iLoop++)
      can_msg_send.Data[iLoop] = canData_au8[iLoop];

   channelID = 1 + canNode_u8;

   if (pCANDriver->sendMessage(channelID, can_msg_send))
   {
       HW_CanMsgPrint(canNode_u8, &can_msg_send, 0u);
   }
   else
   {
      ret_16 = -6; /* E_OVERFLOW */
      hw_DebugPrint("Tx error: %x %x \n", can_msg_send.ID, can_msg_send.Data[0]);
   }
   return ret_16;
}

int16_t hw_CanReadMsg(uint8_t canNode_u8, uint32_t *canId_pu32, uint8_t canData_pau8[], uint8_t *canDataLength_pu8)
{
   CANMsg_t can_msg_read;
   int      channelID;

   if (pCANDriver == 0)
   {
      return 0;
   }

   channelID = 1 + canNode_u8;
   if (pCANDriver->readMessage(channelID, can_msg_read) == true)
   {
      if (can_msg_read.ID != 0xCCCCCCCCuL)
      {
         HW_CanMsgPrint(canNode_u8, &can_msg_read, 1u);
         *canId_pu32 = can_msg_read.ID;
         *canDataLength_pu8 = can_msg_read.DLC;
         for (uint8_t i_u8 = 0u; i_u8 < can_msg_read.DLC; i_u8++)
         {
            canData_pau8[i_u8] = can_msg_read.Data[i_u8];
         }
         return 1;
      }
   }
   return 0;
}

int16_t  hw_CanGetFreeSendMsgBufferSize(uint8_t canNode_u8)
{  /* we return always 20 free buffer entries.... */
   return 20;
}

static void HW_CanMsgPrint(uint8_t canNode_u8, CANMsg_t* can_msg_ps, uint8_t isRX)
{
   const char_t *pcMsgTxt;
   const char_t *pcRxTx;
   /* printf hw_DebugPrint hw_DebugTrace */
   #define CAN_PRINT hw_DebugTrace

   pcRxTx = (isRX > 0u) ? "Rx" : "Tx";
   CAN_PRINT("%2u %12d %2s %8x %1u ", canNode_u8, can_msg_ps->TimeStamp, pcRxTx, can_msg_ps->ID, can_msg_ps->DLC);

#if defined(USE_APP_OUTPUT)
   {  // Get PGN and extra text if available
      uint32_t u32PGN;
      u32PGN = (can_msg_ps->ID & 0x03FFFF00uL) >> 8u;
      if ((u32PGN & 0x00FF00uL) < PGN_PDU2_240_X)
      {  /* PDU 1 -> remove DA */
         u32PGN &= 0x03FF00uL;
      }

      switch (u32PGN)
      {
         case PGN_VTtoECU        : 
         case PGN_ECUtoVT        : pcMsgTxt = VTSublistTextout(can_msg_ps->Data[0] ); break;
         //case PGN_SCC_TO_SCM     : 
         //case PGN_SCM_TO_SCC     : pcMsgTxt = SCSublistTextout(can_msg_ps->Data[0] ); break;
         case PGN_PROCESS_DATA   : pcMsgTxt = TCSublistTextout(can_msg_ps->Data[0] ); break;
         case PGN_TP_DT          : pcMsgTxt = TPSublistTextout(can_msg_ps->Data[0], can_msg_ps->Data[1] ); break;
         //case PGN_FSC_TO_FS      : pcMsgTxt = FSCSublistTextout( PGN_FSC_TO_FS, can_msg_ps->Data );   break;
         //case PGN_FS_TO_FSC      : pcMsgTxt = FSCSublistTextout( PGN_FS_TO_FSC, can_msg_ps->Data );   break;
         case PGN_ADDRESS_CLAIMED: pcMsgTxt = ACLSublistTextout(can_msg_ps->ID, &(can_msg_ps->Data) ); break;
         case PGN_TP_CM          :
         case PGN_ETP_CM         : pcMsgTxt = TPCMSublistTextOut(can_msg_ps->ID, can_msg_ps->Data); break;
         case PGN_N_ACK          : pcMsgTxt = ACKSublistTextOut(can_msg_ps->ID, can_msg_ps->Data); break;
         case PGN_WORKING_SET_MEMBER: pcMsgTxt = "Working set member ";   break;
         case PGN_WORKING_SET_MASTER: pcMsgTxt = "Working set master ";   break;
         case PGN_LANGUAGE_COMMAND  : pcMsgTxt = "Language command ";     break;
         case PGN_ACTIVE_DIAG_TROUBLE_CODES: pcMsgTxt = "DM1 ";      break;
         default                    : pcMsgTxt = " ";                break;
      }

   }
#else 
   pcMsgTxt = " ";
#endif /* defined(USE_APP_OUTPUT) */ 

   if (can_msg_ps->DLC == 0)
   {
      CAN_PRINT("  %s\n", pcMsgTxt);
   }
   if (can_msg_ps->DLC == 3)
   {
      CAN_PRINT("%2.2x %2.2x %2.2x  %s\n", can_msg_ps->Data[0], can_msg_ps->Data[1], can_msg_ps->Data[2], pcMsgTxt);
   }
   else
   {
      CAN_PRINT("%2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x  %s\n",
         can_msg_ps->Data[0], can_msg_ps->Data[1], can_msg_ps->Data[2], can_msg_ps->Data[3],
         can_msg_ps->Data[4], can_msg_ps->Data[5], can_msg_ps->Data[6], can_msg_ps->Data[7], pcMsgTxt);
   }
}
#endif // !defined(CCI_CAN_API) 

/* ************************************************************************ */
/* ************************************************************************ */
void hw_SimDoSleep(uint32_t milliseconds)
{
#if defined(_WIN32)
   Sleep(milliseconds);
#endif 
#if defined(linux)
   usleep(milliseconds * 1000);
#endif 
#ifdef ESP_PLATFORM
   vTaskDelay(milliseconds / portTICK_PERIOD_MS); // 200HZ FreeRTOS Taskrate need for 5ms Sleep.
#endif // def ESP_PLATFORM
}

/* ************************************************************************ */
int_t hw_SimGetKbHit(void)
{
#if defined(_WIN32)
   return _kbhit();
#else 
    return 0;
#endif 
}


/* ************************************************************************ */
int_t hw_SimGetCharEx(uint8_t noEcho)
{
#if defined(_WIN32)
   int_t ch = (noEcho == 1u) ? _getch() : _getche();
   if (ch == 0) 
   {  // empty... read next...
      ch = (noEcho == 1u) ? _getch() : _getche();
   }
   return ch;
#else // _WIN32
    return 0;
#endif // def _WIN32
}

/* ************************************************************************ */
#if !defined(DISABLE_CMDLINE_PARSING)
void hw_SetConfiguration(int_t argc, char_t* argv[])
{
   int_t  i;

   for (i = 0; i < argc; i++)
   {
      if ((std::string(argv[i]) == "-h") || (std::string(argv[i]) == "-help"))
      {
         hw_DebugPrint("%s \n", argv[0]);
         hw_DebugPrint("-h -help \n");
         hw_DebugPrint("-iop objectpoolfile \n");
         hw_DebugPrint("-lbl poollabel \n");
         hw_DebugPrint("-ini ./settings.ini \n");
#if defined(linux)
         hw_DebugPrint("-canid 0 vcanX \n");
#else
         hw_DebugPrint("-canini WHEPS_candriver.ini \n");
#endif /* defined(linux) */
      }
      else if (std::string(argv[i]) == "-ini")
      {
         if (argc > (i + 1))
         {
            initSettings(argv[i + 1]);
         }
      }
   }

#if defined(linux)
   createSection("SocketCan");
#endif // linux
   createSection("ObjectPool");

   for (i = 0; i < argc; i++)
   {
      if (std::string(argv[i]) == "-iop")
      {
         if (argc > (i + 1))
         {
            setString("ObjectPool", "file", argv[i + 1]);
         }
      }
      else if (std::string(argv[i]) == "-lbl")
      {
         if (argc > (i + 1))
         {
            setString("ObjectPool", "label", argv[i + 1]);
         }
      }
      else if (std::string(argv[i]) == "-canid")
      {
         if (argc > (i + 2))
         {
            std::string key("idx");
            key += argv[i + 1];
            setString("SocketCan", key.c_str(), argv[i + 2]);
         }
      }
      else if (std::string(argv[i]) == "-canini")
      {
         if (argc > (i + 1))
         {
            setString("CanConfig", "file", argv[i + 1]);
         }
      }
   }

#if defined(linux)
   {  /* create default CAN entry */
      char_t canSockName[10];
      getString("SocketCan", "idx0", "can0", &canSockName[0], 10u);
   }
#endif // linux

   //settings.Save();
}
#endif /* !defined(DISABLE_CMDLINE_PARSING) */

/* ************************************************************************ */
/* Windows specific */
/* ************************************************************************ */
#if defined(_WIN32)


/* ************************************************************************ */
static BOOL WINAPI ConsoleHandler(DWORD CEvent)
{
   BOOL DoClose_q = TRUE;

   switch (CEvent)
   {
   case CTRL_C_EVENT:
      hw_DebugPrint("CTRL+C received! \n");
      break;
   case CTRL_BREAK_EVENT:
      hw_DebugPrint("CTRL+BREAK received! \n");
      break;
   case CTRL_CLOSE_EVENT:
      hw_DebugPrint("Program being closed! \n");
      hw_Shutdown(); // call shutdown...
      break;
   case CTRL_LOGOFF_EVENT:
      hw_DebugPrint("User is logging off! \n");
      break;
   case CTRL_SHUTDOWN_EVENT:
      hw_DebugPrint("User is logging off! \n");
      break;
   default:
      DoClose_q = false;
      break;
   }

   if (DoClose_q == TRUE)
   {  /* reset powerswitch */
      m_PowerSwitch_u8 = 0u;
   }

   return TRUE;
}

#endif   /* defined(_WIN32) */

/* ************************************************************************ */
/* Linux specific */
/* ************************************************************************ */
#if defined(linux)


/* ************************************************************************ */
static void signal_function(int sig)
{  // can be called asynchronously
   m_PowerSwitch_u8 = 0u;
   hw_DebugPrint("Ctrl-C Signal triggered! \n");
}

#endif   /* defined(linux) */
/* ************************************************************************ */
