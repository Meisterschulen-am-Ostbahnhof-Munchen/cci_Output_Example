/* ************************************************************************ */
/*!
   \file
   \brief       Debug output functions for the driver callbacks. 
   \copyright   Wegscheider Hammerl Ingenieure Partnerschaft

*/
/* ************************************************************************ */
#ifndef DEF_APPOUTPUT_H
    #define DEF_APPOUTPUT_H

#include "IsoDef.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */

/* **************************  defines  *********************************** */

/* **************************  typedef  *********************************** */

/* **************************  function declarations  ********************* */

   void OutputNetworkEvents(const ISONETEVENT_T* psNmEvent, iso_s32  s32Time);
   void OutputDataLink(ISO_TPREP_E eDataTransStatus, const ISO_TPINFO_T* psTpInfo);
#ifdef ISO_MODULE_CLIENTS /* VTC TCC FSC ... */
   void OutputClientCfEvents(const ISOCFEVENT_T* psCfEvData, iso_s32 s32Time);
#endif /* ISO_MODULE_CLIENTS */
#ifdef _LAY6_
   void OutputVtMessages(const ISOVT_MSG_STA_T* pIsoMsgSta, iso_s32 s32Time);
#endif /* _LAY6_ */
#ifdef _LAY10_
   void OutputTCCallback(ISO_TCLINK_T* psTcLink);
#endif /* _LAY10_ */

   /* For CAN output */
   const iso_char* VTSublistTextout(iso_u8 bByte1);
   const iso_char* TCSublistTextout(iso_u8 bByte1);
   const iso_char* TPSublistTextout(iso_u8 bByte1, iso_u8 bByte2);  // TP data packet
   const iso_char* ACLSublistTextout(iso_u32 u32CanID, const ISO_CF_NAME_T* au8Name);
   const iso_char* TPCMSublistTextOut(iso_u32 u32CanID, iso_u8 au8Data[]);
   const iso_char* ACKSublistTextOut(iso_u32 u32CanID, iso_u8 au8Data[]);

/* ************************************************************************ */

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* DEF_APPOUTPUT_H */
/* ************************************************************************ */
