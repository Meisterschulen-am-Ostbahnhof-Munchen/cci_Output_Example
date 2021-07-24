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
#include "AppHW.h"
#include "CanDriverEsp32.h"
#include "driver/twai.h"
#if defined(CONFIG_CAN2IP_MODE_ON)
   #include "can2ip_interface.h"
#endif /* defined(CONFIG_CAN2IP_MODE_ON) */
#include "esp_err.h"
#include "esp_log.h"

#define USE_APP_OUTPUT
#if defined(USE_APP_OUTPUT)
   #include "AppOutput.h"
#endif /* defined(USE_APP_OUTPUT) */

/* ************************************************************************ */

static void HW_CanMsgPrint(uint8_t canNode_u8, twai_message_t* twai_msg_ps, uint8_t isRX);

#define CANBUS_TAG      "CANBUS Master"
#define CAN2IP_TAG      "CAN2IP Master"
#define TX_GPIO_NUM             21
#define RX_GPIO_NUM             22

static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_250KBITS();
static const twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();
//static const twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)TX_GPIO_NUM, (gpio_num_t)RX_GPIO_NUM, CAN_MODE_NORMAL);
static const twai_general_config_t g_config = {.mode = TWAI_MODE_NORMAL,
                                              .tx_io = (gpio_num_t)TX_GPIO_NUM, .rx_io = (gpio_num_t)RX_GPIO_NUM,
                                              .clkout_io = (gpio_num_t)TWAI_IO_UNUSED, .bus_off_io = (gpio_num_t)TWAI_IO_UNUSED,
                                              .tx_queue_len = 150, .rx_queue_len = 1000,
                                              .alerts_enabled = TWAI_ALERT_NONE,
                                              .clkout_divider = 0,
											  .intr_flags = ESP_INTR_FLAG_LEVEL1};


/* ################### CAN Functions ################ */

#if !defined(CCI_CAN_API)  // the implementation is not required if CAN is out sourced into a DLL
void hw_CanInit(uint8_t maxCanNodes_u8)
{
    //Install CAN driver

#if(CONFIG_CAN_MODE_ON)
    ESP_ERROR_CHECK(twai_driver_install(&g_config, &t_config, &f_config));
    ESP_LOGI(CANBUS_TAG, "Driver installed");
#endif
#if(CONFIG_CAN2IP_MODE_ON)
    ESP_ERROR_CHECK(can2ip_driver_install(&g_config, &t_config, &f_config));
	ESP_LOGI(CAN2IP_TAG, "Driver installed");
#endif

#if(CONFIG_CAN_MODE_ON)
    ESP_ERROR_CHECK(twai_start());
    ESP_LOGI(CANBUS_TAG, "Driver started");
#endif
#if(CONFIG_CAN2IP_MODE_ON)
    ESP_ERROR_CHECK(can2ip_start());
	ESP_LOGI(CAN2IP_TAG, "Driver started");
#endif
}

void hw_CanClose(void)
{
#if(CONFIG_CAN_MODE_ON)
    //Uninstall CAN driver
    ESP_ERROR_CHECK(twai_stop());
    ESP_LOGI(CANBUS_TAG, "Driver stopped");
#endif

#if(CONFIG_CAN_MODE_ON)
    //Uninstall CAN driver
    ESP_ERROR_CHECK(twai_driver_uninstall());
    ESP_LOGI(CANBUS_TAG, "Driver uninstalled");
#endif
}


int16_t hw_CanSendMsg(uint8_t canNode_u8, uint32_t canId_u32, const uint8_t canData_au8[], uint8_t canDataLength_u8)
{
   twai_message_t twai_msg_send;
   int16_t  ret_16 = 0;
   int iLoop = 0;

   twai_msg_send.identifier = canId_u32;
   twai_msg_send.data_length_code = canDataLength_u8;
   twai_msg_send.flags = TWAI_MSG_FLAG_EXTD; /* extended */

   for (iLoop = 0; (iLoop < 8) && (iLoop < canDataLength_u8); iLoop++)
	   twai_msg_send.data[iLoop] = canData_au8[iLoop];


   esp_err_t ok_can    = ESP_OK;
   esp_err_t ok_can2ip = ESP_OK;

#if(CONFIG_CAN_MODE_ON)
   ok_can 		= twai_transmit(&twai_msg_send, 0);
#endif
#if(CONFIG_CAN2IP_MODE_ON)
   ok_can2ip	= can2ip_transmit(&twai_msg_send, 0);
#endif

   //ESP_LOGI(CANBUS_TAG, "can transmit");
       HW_CanMsgPrint(canNode_u8, &twai_msg_send, 0u);

#if(CONFIG_CAN_MODE_ON)
   if (ok_can != ESP_OK)
   {
      ESP_LOGE(CANBUS_TAG, "Tx error: %x %x Error: %i - %s", twai_msg_send.identifier, twai_msg_send.data[0], ok_can, esp_err_to_name(ok_can));
   }
#endif
#if(CONFIG_CAN2IP_MODE_ON)
   if (ok_can2ip != ESP_OK)
   {
      ESP_LOGE(CAN2IP_TAG, "Tx error: %x %x Error: %i - %s", twai_msg_send.identifier, twai_msg_send.data[0], ok_can2ip, esp_err_to_name(ok_can2ip));
   }
#endif


   if (ok_can != ESP_OK && ok_can2ip != ESP_OK)
   {
      ret_16 = -6; /* E_OVERFLOW */
      hw_DebugPrint("Tx error: %x %x \n", twai_msg_send.identifier, twai_msg_send.data[0]);
   }
   return ret_16;
}

int16_t hw_CanReadMsg(uint8_t canNode_u8, uint32_t *canId_pu32, uint8_t canData_pau8[], uint8_t *canDataLength_pu8)
{
   twai_message_t twai_msg_read;
   esp_err_t err = ESP_FAIL;

#if(CONFIG_CAN_MODE_ON)
	err = twai_receive(&twai_msg_read, 0);
   if (err == ESP_OK)
   {
      if (twai_msg_read.identifier != 0xCCCCCCCCuL)
      {
#if(CONFIG_CAN_BRIDGE_ON)
    	  can2ip_transmit(&twai_msg_read, 0);
#endif
         HW_CanMsgPrint(canNode_u8, &twai_msg_read, 1u);
         *canId_pu32 = twai_msg_read.identifier;
         *canDataLength_pu8 = twai_msg_read.data_length_code;
         for (uint8_t i_u8 = 0u; i_u8 < twai_msg_read.data_length_code; i_u8++)
         {
            canData_pau8[i_u8] = twai_msg_read.data[i_u8];
         }
         //ESP_LOGI(CANBUS_TAG, "can receive OK from PHYSICAL CAN");
         return 1;
      }
   }
#endif


#if(CONFIG_CAN2IP_MODE_ON)
   err = can2ip_receive(&twai_msg_read, 0);

  if (err == ESP_OK)
  {

     if (twai_msg_read.identifier != 0xCCCCCCCCuL)
     {
#if(CONFIG_CAN_BRIDGE_ON)
  	   twai_transmit(&twai_msg_read, 0);
#endif
        HW_CanMsgPrint(canNode_u8, &twai_msg_read, 1u);
        *canId_pu32 = twai_msg_read.identifier;
        *canDataLength_pu8 = twai_msg_read.data_length_code;
        for (uint8_t i_u8 = 0u; i_u8 < twai_msg_read.data_length_code; i_u8++)
        {
           canData_pau8[i_u8] = twai_msg_read.data[i_u8];
        }
        //ESP_LOGI(CAN2IP_TAG, "can receive OK from GATEWAY CAN");
        return 1;
     }
  }
#endif
   //ESP_LOGI(CANBUS_TAG, "can receive ERROR");
   return 0;
}

int16_t hw_CanGetFreeSendMsgBufferSize(uint8_t canNode_u8) {

	uint32_t a = 0;
	uint32_t b = 0;

#if(CONFIG_CAN_MODE_ON)
	twai_status_info_t twaistatus_info;
	twai_get_status_info(&twaistatus_info);
	a = g_config.tx_queue_len - twaistatus_info.msgs_to_tx;
#endif
#if(CONFIG_CAN2IP_MODE_ON)
	twai_status_info_t ipstatus_info;
	can2ip_get_status_info(&ipstatus_info);
	b = g_config.tx_queue_len - ipstatus_info.msgs_to_tx;
#endif
	return a + b;
}

static void HW_CanMsgPrint(uint8_t canNode_u8, twai_message_t* twai_msg_ps, uint8_t isRX)
{
   return; //disable CANPrint.
   const char_t *pcMsgTxt;
   const char_t *pcRxTx;
   /* printf hw_DebugPrint hw_DebugTrace */
   #define CAN_PRINT hw_DebugTrace

   pcRxTx = (isRX > 0u) ? "Rx" : "Tx";
   CAN_PRINT("%2u %2s %8x %1u ", canNode_u8, pcRxTx, twai_msg_ps->identifier, twai_msg_ps->data_length_code);

#if defined(USE_APP_OUTPUT)
   {  // Get PGN and extra text if available
      uint32_t u32PGN;
      u32PGN = (twai_msg_ps->identifier & 0x03FFFF00uL) >> 8u;
      if ((u32PGN & 0x00FF00uL) < PGN_PDU2_240_X)
      {  /* PDU 1 -> remove DA */
         u32PGN &= 0x03FF00uL;
      }

      switch (u32PGN)
      {
         case PGN_VTtoECU        : 
         case PGN_ECUtoVT        : pcMsgTxt = VTSublistTextout(twai_msg_ps->data[0] ); break;
         //case PGN_SCC_TO_SCM     : 
         //case PGN_SCM_TO_SCC     : pcMsgTxt = SCSublistTextout(twai_msg_ps->Data[0] ); break;
         case PGN_PROCESS_DATA   : pcMsgTxt = TCSublistTextout(twai_msg_ps->data[0] ); break;
         case PGN_TP_DT          : pcMsgTxt = TPSublistTextout(twai_msg_ps->data[0], twai_msg_ps->data[1] ); break;
         //case PGN_FSC_TO_FS      : pcMsgTxt = FSCSublistTextout( PGN_FSC_TO_FS, twai_msg_ps->Data );   break;
         //case PGN_FS_TO_FSC      : pcMsgTxt = FSCSublistTextout( PGN_FS_TO_FSC, twai_msg_ps->Data );   break;
         case PGN_ADDRESS_CLAIMED: pcMsgTxt = ACLSublistTextout(twai_msg_ps->identifier, &(twai_msg_ps->data) ); break;
         case PGN_TP_CM          :
         case PGN_ETP_CM         : pcMsgTxt = TPCMSublistTextOut(twai_msg_ps->identifier, twai_msg_ps->data); break;
         case PGN_N_ACK          : pcMsgTxt = ACKSublistTextOut(twai_msg_ps->identifier, twai_msg_ps->data); break;
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

   if (twai_msg_ps->data_length_code == 0)
   {
      CAN_PRINT("  %s\n", pcMsgTxt);
   }
   if (twai_msg_ps->data_length_code == 3)
   {
      CAN_PRINT("%2.2x %2.2x %2.2x  %s\n", twai_msg_ps->data[0], twai_msg_ps->data[1], twai_msg_ps->data[2], pcMsgTxt);
   }
   else
   {
      CAN_PRINT("%2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x  %s\n",
         twai_msg_ps->data[0], twai_msg_ps->data[1], twai_msg_ps->data[2], twai_msg_ps->data[3],
         twai_msg_ps->data[4], twai_msg_ps->data[5], twai_msg_ps->data[6], twai_msg_ps->data[7], pcMsgTxt);
   }
}
#endif // !defined(CCI_CAN_API)
