/* ******************************************************************* */
/*! \file
    \brief       Debug output functions for the driver callbacks. 
    \copyright   Wegscheider Hammerl Ingenieure Partnerschaft

*/
/* ******************************************************************* */

#include <stdarg.h>
#include <stdio.h>
#include "AppHW.h" 

#include "IsoDef.h"
#include "IsoMnNiuApi.h"   // only needed if _LAY4_ not defined
#include "IsoVtcApi.h"     // only needed if _LAY6_ not defined

#include "AppOutput.h"

#if defined(_MSC_VER )
#pragma warning(disable : 4996)
#endif // defined(_MSC_VER )

/* ******************************************************************* */

static const iso_char* NMUserFuncString(ISO_USERFUNC_e eIsoUserFunct);

/* ******************************************************************* */

#if defined(ISO_DEBUG_USE_EXTERN_FUNCTIONS) && defined(ISO_DEBUG_ENABLED)

// Print x parameter to application window ( used in application )
void iso_DebugPrint(const iso_char pacFormat[], ...)
{
   va_list args;
   va_start(args, pacFormat);
   hw_vDebugPrint(pacFormat, args);
   va_end(args);
}


// Print x parameter to output trace window ( driver intern states )
void iso_DebugTrace(const iso_char pacFormat[], ...)
{
   va_list args;
   va_start(args, pacFormat);
   hw_vDebugTrace(pacFormat, args);
   va_end(args);
}

#endif /* defined(ISO_DEBUG_USE_EXTERN_FUNCTIONS) && defined(ISO_DEBUG_ENABLED) */

/* ******************************************************************* */

void OutputNetworkEvents(const ISONETEVENT_T* psNmEvent, iso_s32  s32Time)
{
#ifdef ISO_DEBUG_ENABLED
   const iso_char    *pchRev, *pchEv;

   switch (psNmEvent->eMemberRefer)
   {
   case intern:    pchRev = "Intern"; break;
   case network:   pchRev = "Extern"; break;
   case thisMember:pchRev = "This  "; break;
   default:        pchRev = "Notdef"; break;
   }

   switch (psNmEvent->eNetEvent)
   {
   case Isonet_MemberActive:           pchEv = "Active  "; break;
   case Isonet_MemberAddressConflict:  pchEv = "Conflict"; break;
   case Isonet_MemberInactive:         pchEv = "Inactive"; break;
   case Isonet_MemberNewAddress:       pchEv = "New Addr"; break;
   case Isonet_MemberAddressViolation: pchEv = "AddrViol"; break;
#if defined(ISO_NM_MSG_MONITOR)
   case Isonet_MemberTimeout:          pchEv = "Timeout "; break;
   case Isonet_MemberResume:           pchEv = "Resume  "; break;
#endif /* #if defined(ISO_NM_MSG_MONITOR) */
   default:                            pchEv = "Notdef  "; break;
   }

#if 0
   /* simple output */
   iso_DebugPrint("NE: %-6s %-8s CF %2.2x (%4.4x)  Time: %8.4d \n",
      pchRev, pchEv, psNmEvent->u8SAMember, psNmEvent->s16Handle, s32Time);
#else
   {  /* extended output */
      const  iso_char   *pchFunc;
      ISO_CF_INFO_T     sCfInfo;

      (void)iso_BaseGetCfInfo(psNmEvent->s16Handle, &sCfInfo);   /* only single threaded ... */
      pchFunc = NMUserFuncString(sCfInfo.eIsoUserFunct);

      iso_DebugPrint("NE CH %1u: %-6s %-8s CF %2.2x (%4.4x) Time: %8.4d \n         NAME: %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x  %-10s (UFnc:%2.2d)\n",
         sCfInfo.u8CanIdx, pchRev, pchEv, psNmEvent->u8SAMember, psNmEvent->s16Handle, s32Time,
         sCfInfo.au8Name[0], sCfInfo.au8Name[1], sCfInfo.au8Name[2], sCfInfo.au8Name[3],
         sCfInfo.au8Name[4], sCfInfo.au8Name[5], sCfInfo.au8Name[6], sCfInfo.au8Name[7], pchFunc, sCfInfo.eIsoUserFunct);
   }
#endif

#endif /* ISO_DEBUG_ENABLED */
}

/* ******************************************************************* */

void OutputDataLink(ISO_TPREP_E eDataTransStatus, const ISO_TPINFO_T* psTpInfo)
{
   //if (qShowDataLinkMsg)
   {
#ifdef ISO_DEBUG_ENABLED
      const iso_char* cpchTpStatus;
      iso_s32  s32Time;

#if (!defined(ISO_CORE_MUTEX)) || defined(ISO_CORE_MUTEX_RECURSIVE)
      s32Time = iso_BaseGetTimeMs();
#else /* (!defined(ISO_CORE_MUTEX)) || defined(ISO_CORE_MUTEX_RECURSIVE) */
      s32Time = 0;
#endif /* (!defined(ISO_CORE_MUTEX)) || defined(ISO_CORE_MUTEX_RECURSIVE) */

      switch (eDataTransStatus)
      {
      case record_start:         cpchTpStatus = "RX start"; break;            /* An extern ECU has started a TP */
      case record_firstdata:     cpchTpStatus = "RX first data"; break;       /* An extern ECU has send the first data message (7 bytes, TP ...)  */
      case record_finish:        cpchTpStatus = "RX finish"; break;           /* An extern ECU has finished sending data (8 bytes, TP ...)  */
      case record_request:       cpchTpStatus = "record request"; break;      /* An extern ECU has sent an request - only Multi node API */
      case send_buffed:          cpchTpStatus = "TX buffered"; break;         /* An intern ECU has called IsoOpenTP successfully, data buffered */
      case send_start_OK:        cpchTpStatus = "TX start"; break;            /* An intern ECU has started a transport successfully */
      case send_packet_request:  cpchTpStatus = "TX packet request"; break;   /* The transport module is ready to send the next data packet ( 7 Bytes ) - Direct transfer only  */
      case send_finished:        cpchTpStatus = "TX finished"; break;         /* An intern ECU has finished a transport successfully */
      case datatrans_abort:      cpchTpStatus = "ABORT"; break;               /* A transport is aborted */
      default:                   cpchTpStatus = "n/a"; break;
      };

      /* iso_DebugPrint */
      iso_DebugTrace("PGN: %6.6x CF INT: %2.2x (%4.4x)  EXT: %2.2x (%4.4x)  %-14.17s Size: %8.1d  Time: %8.4d \n",
         psTpInfo->dwPGN, psTpInfo->u8SAIntern, psTpInfo->s16HndIntern, // review: using SA should not be required in base
         psTpInfo->u8SAPartner, psTpInfo->s16HndPartner, cpchTpStatus, psTpInfo->dwNumberofBytes, s32Time);
#endif /* ISO_DEBUG_ENABLED */
   }
}
/* ******************************************************************* */

#ifdef ISO_MODULE_CLIENTS /* VTC TCC FSC ... */
void OutputClientCfEvents(const ISOCFEVENT_T* psCfEvData, iso_s32 s32Time)
{
#ifdef ISO_DEBUG_ENABLED
   const  iso_char*  pchFunc;
   const  iso_char*  pchEv;
   ISO_CF_INFO_T     sCFDat;
   
   pchFunc = NMUserFuncString(psCfEvData->eIsoUserFunct);

   switch (psCfEvData->eCFEvent)
   {
   case IsoCF_Active:          pchEv = "CF Active ";  break;
   case IsoCF_Lost:            pchEv = "CF Lost   ";  break;
   case IsoCF_LCReceived:      pchEv = "LC Received"; break;
   default:                    pchEv = "Unknown   ";  break;
   }

   (void)iso_BaseGetCfInfo(psCfEvData->s16Handle, &sCFDat);

   iso_DebugPrint("CL - CF: %-10s Event: %-10s SA: %2.2x (%4.4x)  Time: %8.4d \n",
      pchFunc, pchEv, sCFDat.u8SourceAddress, psCfEvData->s16Handle, s32Time);

#endif /* ISO_DEBUG_ENABLED */
}
#endif /* ISO_MODULE_CLIENTS */

/* ******************************************************************* */

#ifdef _LAY6_

void OutputVtMessages(const ISOVT_MSG_STA_T* pIsoMsgSta, iso_s32 s32Time)
{
#ifdef ISO_DEBUG_ENABLED
   const iso_char *pchStatus;

   if (pIsoMsgSta->iErrorCode == E_NO_ERR)
      pchStatus = "OK   ";
   else if (pIsoMsgSta->iErrorCode == E_CANMSG_MISSED)
      pchStatus = "TIMEOUT";
   else
      pchStatus = "ERROR";

   switch (pIsoMsgSta->iVtFunction)
   {
   case softkey_activation:
      iso_DebugPrint("SOFTKEY ACTIVATION: 0x%4.4x   %5d   %10d   Time: %8.4d\n", pIsoMsgSta->wObjectID, pIsoMsgSta->bPara, pIsoMsgSta->lValue, s32Time);
      break;
   case auxiliary_assign_type_1:
      iso_DebugPrint("AUX TYP 1 ASSIGN:   0x%4.4x   %5d   Time: %8.4d\n", pIsoMsgSta->wObjectID, pIsoMsgSta->wPara1, s32Time);
      break;
   case auxiliary_assign_type_2:
   {
      iso_u8 u8I;
      iso_DebugPrint("AUX TYP 2 ASSIGN:   0x%4.4x   %5d   Time: %8.4d Aux Unit: ", pIsoMsgSta->wObjectID, pIsoMsgSta->wPara1, s32Time);
      for (u8I = 0u; u8I < 8u; u8I++) {
         iso_DebugPrint("%2.2X", pIsoMsgSta->pabVtData[u8I]);
      }
      iso_DebugPrint("\n");
   }
   break;
   case aux_input_status_type_1:
      iso_DebugPrint("AUX TYP 1 INPUT/FKT: 0x%4.4x   %10d   %s   Time: %8.4d\n", pIsoMsgSta->wObjectID, pIsoMsgSta->lValue, pchStatus, s32Time);
      break;
   case auxiliary_input_status_type_2:
      iso_DebugPrint("AUX TYP 2 INPUT/FKT: 0x%4.4x   %10d   %s   Time: %8.4d\n", pIsoMsgSta->wObjectID, pIsoMsgSta->lValue, pchStatus, s32Time);
      break;
   default:
   {
      const iso_char *pchCmd;
      pchCmd = VTSublistTextout((iso_u8)pIsoMsgSta->iVtFunction);
      if (pIsoMsgSta->iErrorCode != E_NO_ERR)
      {
         iso_DebugPrint("ERROR CommandResp:  %s   %10d   %s   Time: %8.4d\n", pchCmd, pIsoMsgSta->wPara1, pchStatus, s32Time);
      }
      else
      {
         // used for SRL tests ( 06_02 )
         //iso_DebugPrint("CommandResp:  %s   %10d   %s   Time: %8.4d\n", pchCmd, pIsoMsgSta->wPara1, pchStatus, s32Time);
      }
   }
   break;
   }
#endif /* Debug end */
}

#endif /* _LAY6_ */

/* ******************************************************************* */

#ifdef _LAY10_

void OutputTCCallback(ISO_TCLINK_T* psTcLink)
{
   if (psTcLink->ePDCmd == 0 || psTcLink->ePDCmd == 1)
   {
      iso_DebugTrace("TC ElemNr: %3x   DDI: %3x   Value: %d \n", psTcLink->wDevElementNumb, psTcLink->wDDI, psTcLink->lValueNew);
   }
   else if (psTcLink->ePDCmd == 2)
   {
      iso_DebugPrint("TC-Event: Response to change designator message  Value: %d\n", psTcLink->lValueNew);
   }
   else if (psTcLink->ePDCmd == 3)
   {
      iso_DebugPrint("TC-Event: Task Start/Stop Event Value: %d\n", psTcLink->lValueNew);
   }
   else if (psTcLink->ePDCmd == 4)
   {
      iso_DebugPrint("TC-Event: Size of DD            Value: %d\n", psTcLink->wDDObjID);
   }
   else if (psTcLink->ePDCmd == 5)
   {
      iso_DebugPrint("TC-Event: TC Version received   Value: %d\n", psTcLink->wDDObjID);
   }
}

#endif /* _LAY10_ */

/* ******************************************************************* */

/* ******************************************************************* */


static const  iso_char* NMUserFuncString(ISO_USERFUNC_e eIsoUserFunct)
{
   const  iso_char   *pchFunc;

   switch (eIsoUserFunct)
   {  /* internal used CF/user function */
   case working_set_master:      pchFunc = "Working set master"; break;
   case task_controller:         pchFunc = "Task controller"; break;
   case virtual_terminal:        pchFunc = "Virtual Terminal"; break;
   case tractor_ecu:             pchFunc = "Tractor ECU"; break;
   case auxiliary:               pchFunc = "Auxiliary"; break;
   case sequenz_control_master:  pchFunc = "Sequenz control master"; break;

   case working_set_member:      pchFunc = "Working set member"; break;
   case steering_control:        pchFunc = "Steering control"; break;
   case off_vehicle_gateway:     pchFunc = "Off vehicle gateway"; break;
   case network_interconnection_unit:  pchFunc = "Network interconnection unit"; break;
   case unknown:                 pchFunc = " "; break;
   case file_server:             pchFunc = "File server"; break;

   case virtual_cf:              pchFunc = "Virtual CF"; break;
   case bridged_cf:              pchFunc = "Bridged CF"; break;

   case datalogger:              pchFunc = "Data logger"; break;
   case tim_server:              pchFunc = "TIM server"; break;
   case all_clients:             pchFunc = "all_clients"; break;
   case all_server:              pchFunc = "all_server"; break;
#if defined(ISO_NM_CF_PASSIVE)
   case cf_passive:              pchFunc = "Passive CF"; break;   /* Feature request ID 2919: Use NAME and SA without "active" network management */
#endif /* ISO_NM_CF_PASSIVE */
   case undefined:               pchFunc = "undefined"; break;
   default:                      pchFunc = " "; break;
   }

   return pchFunc;
}

/* ******************************************************************* */

const iso_char * VTSublistTextout(iso_u8 bByte1)
{
   const iso_char *strSubl;
   switch (bByte1)
   {
#ifdef _LAY6_
   case get_memory: strSubl = "VtGetMemory "; break;
   case get_number_softkey: strSubl = "VtGetNumbSK "; break;
   case get_textfonddata: strSubl = "VtGetTexFont"; break;
   case get_WM_data: strSubl = "VtGetWMData "; break;
   case get_supported_objects: strSubl = "VtGetSuppObj"; break;
   case get_hardware: strSubl = "VtGetHardware"; break;
   case store_version: strSubl = "VtStoreVersion"; break;
   case load_version: strSubl = "VtLoadVersion"; break;
   case get_version: strSubl = "VtGetVersions"; break;
   case delete_version: strSubl = "VtDeleteVersion"; break;
   case extended_get_version: strSubl = "Vt extended_get_version"; break;
   case extended_store_version: strSubl = "Vt extended_store_version"; break;
   case extended_load_version: strSubl = "Vt extended_load_version"; break;
   case extended_delete_version: strSubl = "Vt extended_delete_version"; break;
   case end_of_pool_transfer: strSubl = "VtEndOfPoolTrasfer"; break;
   case working_set_maintenance_msg: strSubl = "WsMain   "; break;
   case VT_status_message: strSubl = "VTStatus    "; break;

   case auxiliary_assign_type_2: strSubl = "VtAuxAssiRes"; break;
   case aux_input_maintenance: strSubl = "VtAuxInpMain"; break;
   case auxiliary_input_status_type_2: strSubl = "VtAuxInpStat"; break;
   case aux_input_status_enable: strSubl = "VtAuxInpEnab"; break;
   case preferred_assignment: strSubl = "VtAuxPrefAss"; break;

   case esc: strSubl = "VtEsc       "; break;
   case hide_show_object: strSubl = "VtChaHideSho"; break;
   case enable_disable_object: strSubl = "VtObjEnDisab"; break;
   case select_input_object: strSubl = "VtSelInpObj "; break;
   case control_audio_device: strSubl = "VtControlAud"; break;
   case set_audio_volume: strSubl = "VtSetAudioVo"; break;
   case change_child_location: strSubl = "VtChaChildLo"; break;
   case change_size: strSubl = "VtChaSize   "; break;
   case change_background_colour: strSubl = "VtChaBagrCol"; break;
   case change_numeric_value: strSubl = "VtChaNumeric"; break;
   case change_end_point: strSubl = "VtChaEndPoin"; break;
   case change_font_attributes: strSubl = "VtChaFontAtt"; break;
   case change_line_attributes: strSubl = "VtChaLineAtt"; break;
   case change_fill_attributes: strSubl = "VtChaFillAtt"; break;
   case change_activ_mask: strSubl = "VtChaActMask"; break;
   case change_softkey_mask: strSubl = "VtChaSKMask "; break;
   case change_attribute: strSubl = "VtChaAttri  "; break;
   case change_priority: strSubl = "VtChaPriorit"; break;
   case change_list_item: strSubl = "VtChaListIte"; break;
   case delete_object_pool: strSubl = "VtChaDelObjP"; break;
   case change_string_value: strSubl = "VtChaStringV"; break;
   case change_child_position: strSubl = "VtChaChildPo"; break;
   case get_attribute_value: strSubl = "VtGetAttri  "; break;
   case select_colour_map: strSubl = "VtSelColMap "; break;
#endif /* _LAY6_ */
   default: strSubl = "            "; break;
   }

   return strSubl;
}

/* ******************************************************************* */

const iso_char * TCSublistTextout(iso_u8 bByte1)
{
   const iso_char *strSubl;
   switch (bByte1 & 0xF)
   {
   case 0:
   case 1:
      switch (bByte1)
      {
      case     0: strSubl = "TcVersionRequest"; break;
      case     1: strSubl = "TcRequestStrutureLabel"; break;
      case  0x10: strSubl = "TcVersion"; break;
      case  0x11: strSubl = "TcStructureLabel"; break;
      case  0x21: strSubl = "TcRequestLocalisationLabel"; break;
      case  0x31: strSubl = "TcLocalisationLabel"; break;
      case  0x41: strSubl = "TcRequestObjectPoolTransfer"; break;
      case  0x51: strSubl = "TcRequestObjectPoolTransResp"; break;
      case  0x61: strSubl = "TcObjectPoolTransfer"; break;
      case  0x71: strSubl = "TcObjectPoolTransferResp"; break;
      case  0x81: strSubl = "TcObjectPoolActivate"; break;
      case  0x91: strSubl = "TcObjectPoolActivateResp"; break;
      default:    strSubl = "            "; break;
      }
      break;
   case   2: strSubl = "TcRequestValueCmd "; break;
   case   3: strSubl = "TcValueCmd"; break;
   case   4: strSubl = "TcMPdTimeInterval"; break;
   case   5: strSubl = "TcMPdDistanceInterval"; break;
   case   6: strSubl = "TcMPdMinThreshold"; break;
   case   7: strSubl = "TcMPdMaxThreshold"; break;
   case   8: strSubl = "TcMPdChangeThreshold"; break;
   case   9: strSubl = "TcMPdPeerControlAssignment"; break;
   case 0xA: strSubl = "TcValueCmdwithAck"; break;
   case 0xD: strSubl = "TcPDNACK"; break;
   case 0xE: strSubl = "TCStatus"; break;
   case 0xF: strSubl = "TcClientTask"; break;
   default:  strSubl = "?????"; break;
   }
   return strSubl;
}

/* ******************************************************************* */

const iso_char * TPSublistTextout(iso_u8 bByte1, iso_u8 bByte2)
{  /* First data packet output: Hint this is not correct in all cases */
   const iso_char *strSubl;
   if (bByte1 == 0x1)
   {
      switch (bByte2)
      {
      case get_version_response: strSubl = "VtGetVersRes"; break;
      case objectpool_transfer_msg: strSubl = "VtPoolData  "; break;
      case change_string_value: strSubl = "VtChaStringV"; break;
      case auxiliary_assign_type_2: strSubl = "AuxAssignmen"; break;
      case preferred_assignment: strSubl = "AuxPrefAssig"; break;
      case 1: strSubl = "ScDVersRes  "; break;
      case 3: strSubl = "ScDTransfer "; break;
      default: strSubl = "            "; break;
      }
   }
   else
   {
      strSubl = "            ";
   }
   return strSubl;
}

/* ******************************************************************* */

const iso_char* ACLSublistTextout(iso_u32 u32CanID, const ISO_CF_NAME_T* au8Name)
{
   static iso_char strSubl[100];
   ISONAMEFIELD_T sNameField;

   iso_NmSetNameField(au8Name, &sNameField);
   sprintf(strSubl, "ACL %.2x: S/G=%.1x/%.1x DC/DI=%.3d/%.2d F/I/E=%.3d/%.2d/%.1d MC=%.4d SNr=%.7d",
      (uint8_t)(u32CanID & 0x000000FFUL),
      sNameField.bSelfConf, sNameField.bIndGroup,
      sNameField.bDevClass, sNameField.bDevClassInst,
      sNameField.bFunction, sNameField.bFunctionInst, sNameField.bEcuInstance,
      sNameField.wManufCode, sNameField.dwIdentNumb);
   return strSubl;
}

/* ******************************************************************* */

const iso_char* TPCMSublistTextOut(iso_u32 u32CanID, iso_u8 au8Data[])
{
   static char strSubl[200];
   const char *pstrFormat;
   iso_u8  u8SA, u8Err = 0u;
   iso_u32 u32PGNofDT, u32P1 = 0UL, u32P2 = 0UL, u32P3 = 0UL;

   u8SA = (iso_u8)(u32CanID & 0x000000FFuL);
   u32PGNofDT = (((iso_u32)au8Data[5]) | ((iso_u32)au8Data[6] << 8) | ((iso_u32)au8Data[7] << 16));

   switch (au8Data[0])
   {
   case 0x10u: // TP_CM_RTS
   case 0x20u: // TP_CM_BAM
      pstrFormat = (au8Data[0] == 0x10u)
         ? "TP_CM_RTS SA=%.2x PGN=%.6x size=%.4d packets total=%.3d CTS_Max=%.3d"
         : "TP_CM_BAM SA=%.2x PGN=%.6x size=%.4d packets total=%.3d";
      u32P1 = (iso_u32)au8Data[1] | ((iso_u32)au8Data[2] << 8u); // number of data bytes
      u32P2 = au8Data[3]; //total number packets
      u32P3 = au8Data[4]; //max number packets to one CTS
      if ((u32P2 < 2u)
         || (u32P1 >(iso_u32)(u32P2 * 7UL))
         || (u32P1 <= ((iso_u32)((iso_u32)u32P2 - 1UL) * 7UL)))
      {  /* parameter error (packets != size)*/
         u8Err = 13u; //IsoTpOtherError
      }
      break;
   case 0x11u: // TP_CM_CTS
      pstrFormat = "TP_CM_CTS SA=%.2x PGN=%.6x packets send=%.3d next=%.3d";
      u32P1 = au8Data[1]; //number of packets that can be send
      u32P2 = au8Data[2]; //next packet number
      if (u32P1 == 0UL) { u8Err = 0xEEu; /* WAIT */ }
      break;
   case 0x13u: // TP_CM_EOMA
      u32P1 = (iso_u32)au8Data[1] | ((iso_u32)au8Data[2] << 8u); // number of data bytes received
      u32P2 = au8Data[3]; //total number packets
      pstrFormat = "TP_CM_EOMA SA=%.2x PGN=%.6x received=%.4d packets=%.3d";
      break;
   case 0x14u: // ETP_CM_RTS
      u32P1 = ((iso_u32)au8Data[1]) | ((iso_u32)au8Data[2] << 8u)
         | ((iso_u32)au8Data[3] << 16u) | ((iso_u32)au8Data[4] << 24u); // number of data bytes
      pstrFormat = "ETP_CM_RTS SA=%.2x PGN=%.6x size=%.4d";
      break;
   case 0x15u: // ETP_CM_CTS
      u32P1 = au8Data[1]; //number of packets to send
      u32P2 = (((iso_u32)au8Data[2]) | ((iso_u32)au8Data[3] << 8) | ((iso_u32)au8Data[4] << 16)); // next data packet
      if (u32P1 == 0UL) { u8Err = 0xEEu; /* WAIT */ }
      pstrFormat = "ETP_CM_CTS %.2x PGN=%.6x packets send=%.3d next=%.4d";
      break;
   case 0x16u: // ETP_CM_DPO
      u32P1 = au8Data[1]; //number of packets to which the to apply the offset
      u32P2 = (((iso_u32)au8Data[2]) | ((iso_u32)au8Data[3] << 8) | ((iso_u32)au8Data[4] << 16)); // data packet offset
      pstrFormat = "ETP_CM_DPO SA=%.2x PGN=%.6x packets send=%.3d offset=%.4d";
      break;
   case 0x17u: // ETP_CM_EOMA
      u32P1 = ((iso_u32)au8Data[1]) | ((iso_u32)au8Data[2] << 8u)
         | ((iso_u32)au8Data[3] << 16u) | ((iso_u32)au8Data[4] << 24u); // number of data bytes received
      pstrFormat = "ETP_CM_EOMA SA=%.2x PGN=%.6x  received=%.4d";
      break;

   case 0xFFu: // (E)TP Abort
      u8Err = au8Data[1]; // Abort reason
      if ((u32CanID & 0x00FF0000uL) == 0x00EC0000uL)
      {
         pstrFormat = "TP_CM_ABORT SA=%.2x PGN=%.6x";
      }
      else
      {
         pstrFormat = "ETP_CM_ABORT SA=%.2x PGN=%.6x";
      }
      break;
   default:
      u32P1 = au8Data[0];
      pstrFormat = "(E)TP ERROR SA=%.2x PGN=%.6x unknown command byte 0x%.2x";
      break;
   }

   {
      int fnRet;
      fnRet = sprintf(strSubl, pstrFormat, u8SA, u32PGNofDT, u32P1, u32P2, u32P3);

      switch (u8Err)
      {
      case 0u:
         pstrFormat = " ";
         break;
      case 1u:
         pstrFormat = " - ERROR (0x%.2x): cannot support another connection";
         break;
      case 2u:
         pstrFormat = " - ERROR (0x%.2x): currently no free system resources";
         break;
      case 3u:
         pstrFormat = " - ERROR (0x%.2x): timeout occurred";
         break;
      case 4u:
         pstrFormat = " - ERROR (0x%.2x): CTS messages received when data transfer is in progress";
         break;
      case 5u:
         pstrFormat = " - ERROR (0x%.2x): Maximum retransmit request limit reached";
         break;
      case 6u:
         pstrFormat = " - ERROR (0x%.2x): Unexpected data transfer packet";
         break;
      case 7u:
         pstrFormat = " - ERROR (0x%.2x): Bad sequence number";
         break;
      case 8u:
         pstrFormat = " - ERROR (0x%.2x): Duplicate sequence number";
         break;
      case 9u:
         pstrFormat = " - ERROR (0x%.2x): Unexpected EDPO packet";
         break;
      case 10u:
         pstrFormat = " - ERROR (0x%.2x): Unexpected EDPO PGN";
         break;
      case 11u:
         pstrFormat = " - ERROR (0x%.2x): EDPO number of packets is greater than CTS";
         break;
      case 12u:
         pstrFormat = " - ERROR (0x%.2x): Bad EDPO offset ";
         break;
      case 13u:
         pstrFormat = " - ERROR (0x%.2x): Any other error";
         break;
      case  0xEEu: /* (E)CTS WAIT */
         pstrFormat = " - do WAIT ";
          break;
      default:
         pstrFormat = " - ERROR (0x%.2x)";
         break;
      }

      fnRet = sprintf(&strSubl[fnRet], pstrFormat, u8Err);
   }

   return strSubl;
}

/* ******************************************************************* */

const iso_char* ACKSublistTextOut(iso_u32 u32CanID, iso_u8 au8Data[])
{
   static iso_char strSubl[100];
   const iso_char *pstrCmd, *pstrTxt = " ";
   iso_u8  u8SA, u8DA, u8P1, u8P2;
   iso_u32 u32PGNofDT;

   u8SA = (iso_u8)(u32CanID & 0x000000FFuL);
   u8DA = (iso_u8)(u32CanID >> 8);
   u32PGNofDT = (((iso_u32)au8Data[5]) | ((iso_u32)au8Data[6] << 8) | ((iso_u32)au8Data[7] << 16));
   u8P1 = au8Data[1]; // Group function 
   u8P2 = au8Data[4]; // SA of requester

   switch (au8Data[0])
   {
   case 0x0u: // ACK
      pstrCmd = "ACK";
      break;
   case 0x1u: // NACK
      pstrCmd = "NACK";
      break;
   case 0x2u: // Access Denied
      pstrCmd = "Access Denied";
      break;
   case 0x3u: // Cannot Respond
      pstrCmd = "Cannot Respond";
      break;
   default:
      pstrCmd = "ACK ERROR";
      pstrTxt = "unknown control byte";
      break;
   }

   if ((au8Data[0] > 0u) && (u8DA >= 0xFEu))
   {
      pstrTxt = " - ERROR global response"; // or to FE is not allowed NACKs
   }


   sprintf(strSubl, "%s PGN=%.6x GFV=%.2x SA=%.2x Requester=%.2x %s", pstrCmd, u32PGNofDT, u8P1, u8SA, u8P2, pstrTxt);

   return strSubl;
}

/* ******************************************************************* */
