/* ************************************************************************ */
/*!
   \file           

   \brief      VT Client application  

   \author     Erwin Hammerl
   \date       Created 17.09.2007 
   \copyright  Wegscheider Hammerl Ingenieure Partnerschaft

   \par HISTORY:

*/

/* **************************  includes ********************************** */


#include "IsoDef.h"
#include "Common/IsoUtil.h"

#ifdef _LAY6_  /* compile only if VT client is enabled */

#include "Settings/settings.h"
#include "AppMemAccess.h"
#include "AppCommon/AppOutput.h"

#include "App_VTClient.h"
#include "VIEngine.h"
#include "App_VTClientLev2.h"

#include "MyProject1.iop.h"
#include "MyProject1.c.h"


#if defined(CCI_USE_POOLBUFFER)

#endif /* defined(CCI_USE_POOLBUFFER) */
#include "AppPool/AppPool.h"

#if defined(_LAY6_) && defined(ISO_VTC_GRAPHIC_AUX)
#include "../Samples/VtcWithAuxPoolUpload/GAux.h"
#endif // defined(_LAY6_) && defined(ISO_VTC_GRAPHIC_AUX)

/* ****************************** defines  ******************************** */

/* ****************************** global data   *************************** */
static iso_s16  s16_CfHndVtClient = HANDLE_UNVALID;      // Stored CF handle of VT client
static iso_u8   u8_CfVtInstance = ISO_INSTANCE_INVALID;  // Instance number of the VT client
static iso_u8   u8_CfVtInstance2 = ISO_INSTANCE_INVALID;  // Instance number of the VT client
static iso_u8   u8_CfAuxVtInstance = ISO_INSTANCE_INVALID;  // Instance number of the Aux VT client
static iso_u8   u8_poolChannel = 0U;   // pool channel for pool to be uploaded
static iso_u8   u8_poolChannelAux = 0U;   // pool channel for pool to be uploaded to aux function only instance 
/* ****************************** function prototypes ****************************** */
static void CbVtConnCtrl        (const ISOVT_EVENT_DATA_T* psEvData);
static void CbVtStatus          (const ISOVT_STATUS_DATA_T* psStatusData);
static void CbVtMessages        (const ISOVT_MSG_STA_T * pIsoMsgSta);
static void CbAuxPrefAssignment (const VT_AUX_PREF_PARAM_T* psParams, VT_AUXAPP_T asAuxAss[], iso_s16* ps16MaxNumberOfAssigns);

static void AppPoolSettings(const ISOVT_EVENT_DATA_T* psEvData, iso_u8* pu8PoolChannel);
static void AppVTClientDoProcess(void);

static void VTC_SetObjValuesBeforeStore(iso_u8 u8Instance);

static void fillAuxSectionName(iso_char auxSection[], iso_u32 u32ArraySize);


#if defined(ESP_PLATFORM)
static const char *POOL_FILENAME = "/spiffs/pools/MyProject1.iop";
#else
static const char *POOL_FILENAME = "pools/MyProject1.iop";
#endif // defined(ESP_PLATFORM)



/* ************************************************************************ */
void AppVTClientLogin(iso_s16 s16CfHandle)
{
   ISO_USER_PARAM_T  userParamVt = ISO_USER_PARAM_DEFAULT;
   uint64_t u64Name = 0;
   iso_u8 u8BootTime = 0;
   iso_u8 au8NamePreferredVT_1[8] = { 0x49, 0x2a, 0x69, 0x2a, 0x00, 0x1d, 0x00, 0xa0 }; // CCI
   iso_u8 au8NamePreferredVT_2[8] = { 0x49, 0x2a, 0x69, 0x2a, 0x08, 0x1d, 0x00, 0xa0 }; // CCI

   u8BootTime = getU8("CF-A", "bootTimeVT", 7u);

   // Initialize the VT client instance - Set (EE-stored) NAME and boot time of the preferred VT (in seconds)
   u8_CfVtInstance = IsoVtcCreateInstance(s16CfHandle, userParamVt, CbVtStatus, CbVtMessages, CbVtConnCtrl, CbAuxPrefAssignment,
                                          CAST_TO_CONST_ISONAME_PTR(&au8NamePreferredVT_1), u8BootTime);

   // Initialize the VT client instance - Set (EE-stored) NAME and boot time of the preferred VT (in seconds)
   u8_CfVtInstance2 = IsoVtcCreateInstance(s16CfHandle, userParamVt, CbVtStatus, CbVtMessages, CbVtConnCtrl, CbAuxPrefAssignment,
                                          CAST_TO_CONST_ISONAME_PTR(&au8NamePreferredVT_2), u8BootTime);
   
   // Use preferred assignment callback function, which is called before sending the preferred assignment for the auxiliary functions to the VT
   // Deprecated - already set with IsoVtcCreateInstance(): (void)IsoVtcAuxPrefAssignmentCbSet(u8_CfVtInstance, &CbAuxPrefAssignment);

#if defined(_LAY6_) && defined(ISO_VTC_GRAPHIC_AUX)
   /* Add CF to graphical aux implements */
   (void)vtcGAux_CfInit(s16CfHandle, userParamVt, POOL_FILENAME);
#endif // defined(_LAY6_) && defined(ISO_VTC_GRAPHIC_AUX)

   s16_CfHndVtClient = s16CfHandle; // Store VT client CF handle
}

/* ************************************************************************ */
static void CbVtConnCtrl(const ISOVT_EVENT_DATA_T* psEvData)
{
   iso_u8 abLCData[8];  /* V12 provide country code: array must be at least 8 bytes (not only 6 bytes) */

   switch (psEvData->eEvent)
   {
   case IsoEvInstanceClosed:
      if (psEvData->u8Instance == u8_CfVtInstance)
      {  // MASK instance
         u8_CfVtInstance = ISO_INSTANCE_INVALID;
         if (u8_poolChannel > 0u)
         {
            poolFree(u8_poolChannel);
            u8_poolChannel = 0;
         }
      }

      if (psEvData->u8Instance == u8_CfAuxVtInstance)
      {  // AUX instance
         u8_CfAuxVtInstance = ISO_INSTANCE_INVALID;
         if (u8_poolChannelAux > 0u)
         {
            poolFree(u8_poolChannelAux);
            u8_poolChannelAux = 0;
         }
      }
      break;
   case IsoEvConnSelectPreferredVT:
      /* preferred VT is not alive, but one or more other VTs */
      VTC_setNewVT(psEvData);
      break;
   case IsoEvMaskServerVersAvailable:
      if (IsoVtcGetStatusInfo(psEvData->u8Instance, VT_VERSIONNR) >= 4u)
      {
         // IsoVTObjTypeParsableSet(PNGObject);  // for test purposes (must be called here)
      }
      break;
   case IsoEvMaskLanguageCmd:
      IsoVtcReadWorkingSetLanguageData(psEvData->u8Instance, abLCData);
      break;
   case IsoEvMaskTechDataV4Request:
      /* If VT >= V4 then application can request some more technical data */
      if (IsoVtcGetStatusInfo(psEvData->u8Instance, WS_VERSION_NR) >= 4u)
      {
         IsoVtcCmd_GetSupportedObjects(psEvData->u8Instance);
         IsoVtcCmd_GetWindowMaskData(psEvData->u8Instance);
         //IsoVtcCmd_GetSupportedWidechar(psEvData->u8Instance, ...)
      }
      break;
   case IsoEvMaskLoadObjects:
      /* provide pool */
      AppPoolSettings(psEvData, &u8_poolChannel);
      break;
   case IsoEvMaskReadyToStore:
      /* pool upload finished - here we can change objects values which should be stored */
      VTC_SetObjValuesBeforeStore(psEvData->u8Instance);
      break;
   case IsoEvMaskActivated:
      /* pool is ready - here we can setup the initial mask and data which should be displayed */
	  VTC_setPoolReady(psEvData);
      {  /* Current VT and boot time of VT can be read and stored here in EEPROM */
         iso_s16 s16HndCurrentVT = (iso_s16)IsoVtcGetStatusInfo(psEvData->u8Instance, VT_HND);   /* get CF handle of actual VT */
         ISO_CF_INFO_T cfInfo = { 0 };
         iso_s16 s16Err = iso_NmGetCfInfo(s16HndCurrentVT, &cfInfo);
         if (s16Err == E_NO_ERR)
         {
            uint64_t u64Name = ((uint64_t)(cfInfo.au8Name[0])) |
               ((uint64_t)(cfInfo.au8Name[1]) << 8) |
               ((uint64_t)(cfInfo.au8Name[2]) << 16) |
               ((uint64_t)(cfInfo.au8Name[3]) << 24) |
               ((uint64_t)(cfInfo.au8Name[4]) << 32) |
               ((uint64_t)(cfInfo.au8Name[5]) << 40) |
               ((uint64_t)(cfInfo.au8Name[6]) << 48) |
               ((uint64_t)(cfInfo.au8Name[7]) << 56);
            setX64("CF-A", "preferredVT", u64Name);

            iso_u8 u8BootTime = (iso_u8)IsoVtcGetStatusInfo(psEvData->u8Instance, VT_BOOTTIME);
            setU8("CF-A", "bootTimeVT", u8BootTime);
         }
      }
      // no break -> free pool
      /* fall through */
      /* no break */
   case IsoEvMaskPoolReloadFinished:
      if (u8_poolChannel > 0u)
      {
         poolFree(u8_poolChannel);
         u8_poolChannel = 0;
      }
      break;
   case IsoEvMaskTick:  // Cyclic event; Called only after successful login
      AppVTClientDoProcess();   // Sending of commands etc. for mask instance
      break;
   case IsoEvMaskLoginAborted:
      // Login failed - application has to decide if login shall be repeated and how often
      //AppVTClientLogin(s16_CfHndVtClient);
      // u8_CfVtInstance = ISO_INSTANCE_INVALID; // we wait for IsoEvInstanceClosed event
      break;
   case IsoEvConnSafeState:
      // Connection closed ( VT lost, VT_LOGOUT (delete object pool response was received ) )
      break;
// AUX function instance on primary VT (only if MASK instance is on a secondary VT)
   case IsoEvAuxServerVersAvailable:
      break;
   case IsoEvAuxLanguageCmd:
      //IsoClServ_ReadLCOfServer( , );
      break;
   case IsoEvAuxTechDataV4Request:
      break;
   case IsoEvAuxLoadObjects:
      u8_CfAuxVtInstance = psEvData->u8Instance;
      AppPoolSettings(psEvData, &u8_poolChannelAux);
      break;
   case IsoEvAuxLoginAborted:
      // Login failed - application has to decide if login shall be repeated and how often
      // u8_CfAuxVtInstance = ISO_INSTANCE_INVALID; // we wait for IsoEvInstanceClosed event
      break;
   case IsoEvAuxReadyToStore:       
      break;
   case IsoEvAuxPoolReloadFinished: // currently not possible/used
   case IsoEvAuxActivated:          // aux instance pool loaded
      if (u8_poolChannelAux > 0u)
      {  // free pool 
         poolFree(u8_poolChannelAux);
         u8_poolChannelAux = 0;
      }
      break;
   case IsoEvAuxTick:
      break;
   default:
      break;
   }
}

/* ************************************************************************ */
static void AppVTClientDoProcess( void )
{  /* Cyclic VTClient function */

}




/* ************************************************************************ */
static void AppPoolSettings(const ISOVT_EVENT_DATA_T* psEvData, iso_u8* pu8PoolChannel)
{
   const iso_u8*  pu8PoolData;        // Pointer to the pool data ( Attention:  )
   iso_u32  u32PoolSize;

   

   if (*pu8PoolChannel > 0)
   {  // clean-up a previously open pool.
      poolFree(*pu8PoolChannel);  
   }

#if !defined(CCI_USE_POOLBUFFER)
   *pu8PoolChannel = poolLoadByFilename(POOL_FILENAME);
#else // !defined(CCI_USE_POOLBUFFER)
   *pu8PoolChannel = poolLoadByByteArray((iso_u8*)&pool_iop[0], sizeof(pool_iop));
#endif // !defined(CCI_USE_POOLBUFFER)

   poolOpen(*pu8PoolChannel, colour_256); // open a complete pool for a 256 colour VT
   u32PoolSize = (uint32_t)poolGetSize(*pu8PoolChannel);
   pu8PoolData = poolGetData(*pu8PoolChannel);

   IsoVtcPoolLoad(psEvData->u8Instance, (iso_u8 *)ISO_VERSION_LABEL, // Instance, Version,
      ISO_DESIGNATOR_WIDTH, ISO_DESIGNATOR_HEIGHT, ISO_MASK_SIZE,                                 // SKM width and height, DM res.
      PoolTransferFlash,
      pu8PoolData, u32PoolSize,                    // PoolAddress, PoolSize (optional),
      0, 0, 0);

   // Set pool manipulations
   VTC_setPoolManipulation( psEvData );
}

/* ************************************************************************ */
/* This function is called in case of every page change - you can do e. g. initialisations ...  */
static void CbVtStatus(const ISOVT_STATUS_DATA_T* psStatusData)
{
   switch (psStatusData->wPage)
   {
   case DataMask_Main:
      break;

   default:
       break;
   }
}


/* ************************************************************************ */
/*!                                                                               
   \brief       Receiving all messages of VT                                      
   \verbatim                                                                                 
    Callback function for responses, VT activation messages ...                                                                                            
      
    VT-Function:                Parameter of       Meaning:
                                ISOVT_MSG_STA_T:      
                                                   
    softkey_activation            wObjectID       key object ID                   
                                  wPara1          parent object ID                
                                  bPara           key number (hard coded)         
                                  lValue          activation code (0, 1, 2, 3(Version 4)) see [1]   
    button_activation             wObjectID       button object ID                
                                  wPara1          parent object ID                
                                  bPara           button key number               
                                  lValue          activation code (0, 1, 2, 3(Version 4)) see [1]
    pointing_event                wPara1          X position in pixel             
                                  wPara2          Y position in pixel             
    VT_select_input_object        wObjectID       input object ID                 
                                  wPara1          Selected/Deselected
                                  wPara2          Bitmask (Version 5 and later)
    VT_esc                        wObjectID       ID of input field where aborted 
                                  iErrorCode      error code see ISO Doku.        
    VT_change_numeric_value       wObjectID       ID of input object              
                                  lValue          new value                       
    VT_change_active_mask         wObjectID       momentan active mask            
                                  iErrorCode      error code see ISO Doku.        
    VT_change_softkey_mask        wObjectID       data or alarm mask object ID    
                                  wPara1          soft key mask object ID         
                                  iErrorCode      error code see ISO Doku         
    VT_change_string_value        wObjectID       ID of String object             
                                  bPara           Length of string                
                                  pabVtData       Pointer to characters 
    ( Version 4 )                 
    VT_onUserLayout_hideShow      wObjectID       Object ID of WM, DM, SKM, KG
                                  wPara2          Hide/show
                                  wPara1          Object ID of second WM, DM, SKM, KG
                                  bPara           Hide/show of second
    get_attribute_value           wObjectID       Object ID
                                  bPara           AID
                                  wPara1          Current value of attribute
                                  iErrorCode      ErrorCode (see F.59)
    ( Version 3 )                 
    preferred_assignment          wObjectID       Auxiliary function object if faulty
                                  iErrorCode      Error code see ISO Doku.
    auxiliary_assign_type_1, .._2 wObjectID       Object ID auxiliary function    
                                  wPara1          Object ID auxiliary input (or input number type 1) 
                                                  0xFFFF for unassign             
                                  wPara2          Type of auxiliary incl. Attribute bits see [2]
                                  bPara           ISO_TRUE: Store as pref. assign, else not (only type 2) 
                                  lValue          Bit 16 - 27: Manufacturer code,         
                                                  Bit  0 - 15 Model Identification code of auxiliary input 
                                                  (only type 2)
                                  pabVtData       only for auxiliary_assign_type_2:
                                                  Pointer to the last/current aux unit ISONAME or 8*0xFF
    auxiliary_input_status_type_2
    aux_input_status_type_1       wObjectID       Object ID Auxiliary function type          
                                  wPara1          Input object ID (type 1 = input number     
                                  lValue          Value 1                                    
                                  wPara2          Value 2                                    
                                  iErrorCode      E_NO_ERR, E_CANMSG_MISSED (Alive of input)
    ( Version 5 )
    auxiliary_capabilities        bPara           Number of auxiliary Units
                                  pabVtData       Pointer to data ( Byte 3 ... )

               [1] Timeout control of softkeys and buttons have to be done of application !
               [2] Attribute bits are given to application as additional information
                   For getting the Auxiliary type application have to mask out it.
   \endverbatim
                                                                                  
   \param[in]     \wpp{pIsoMsgSta, const #ISOVT_MSG_STA_T *}                                                   
                       Pointer on received IS0 messages                                                                                
*/           
static void CbVtMessages( const ISOVT_MSG_STA_T * pIsoMsgSta )
{
   OutputVtMessages(pIsoMsgSta, IsoClientsGetTimeMs());

   switch ( pIsoMsgSta->iVtFunction )
   {
   case button_activation :
   case softkey_activation :
      VTC_handleSoftkeysAndButtons((struct ButtonActivation_S *)(pIsoMsgSta));
      break;
   case VT_change_numeric_value :
	  VTC_handleNumericValues((struct InputNumber_S *)(pIsoMsgSta));
      break;
   case VT_change_string_value :
      // Receiving string see Page 3
      //VTC_process_VT_change_string_value(pIsoMsgSta);
      break;
   case auxiliary_assign_type_1 :
       break;
   case auxiliary_assign_type_2 :
#if defined(_LAY6_) && defined(ISO_VTC_GRAPHIC_AUX)
   {  /* Forward assignment message to aux unit */
       iso_s16 s16CfHandle;
       s16CfHandle = IsoVtcGetStatusInfo(pIsoMsgSta->u8Instance, CF_HND); /* or use the stored (s16CfHandleWs) */
       (void)vtcGAux_ForwardAssignment(s16CfHandle, pIsoMsgSta);
   }
#endif // defined(_LAY6_) && defined(ISO_VTC_GRAPHIC_AUX)
       /* Assignment is stored only in case of Byte 10, Bit 7 is zero (use as preferred assignment) */
       if ( pIsoMsgSta->bPara != 0 )
       {
          iso_char auxSection[64]; // storing aux assigns depending on the pool label
          fillAuxSectionName(auxSection, 64U);
#if (0)   // sample - read every time all assignments
          static iso_s16  iNumberOfFunctions = 0;
          static VT_AUXAPP_T asAuxAss[20];      // AUXINPUTMAX !
          /* Reading the complete actual assignment and storing this in a file or EE */
          IsoAuxAssignmentRead(asAuxAss, &iNumberOfFunctions);
          setAuxAssignment(auxSection, asAuxAss, iNumberOfFunctions);
          //IsoAuxWriteAssignToFile(asAuxAss, iNumberOfFunctions);  // Assignment -> File
#else
          if (pIsoMsgSta->wObjectID != NULL_OBJECTID)
          {
             VT_AUXAPP_T auxEntry = { 0 };
             auxEntry.wObjID_Fun = pIsoMsgSta->wObjectID;
             auxEntry.wObjID_Input = pIsoMsgSta->wPara1;
             auxEntry.eAuxType = (VTAUXTYP_e)(pIsoMsgSta->wPara2 & 0x1F);
             auxEntry.wManuCode = (iso_u16)(pIsoMsgSta->lValue >> 16);
             auxEntry.wModelIdentCode = (iso_u16)(pIsoMsgSta->lValue);
             auxEntry.qPrefAssign = pIsoMsgSta->bPara;
             auxEntry.bFuncAttribute = (iso_u8)(pIsoMsgSta->wPara2);
             iso_ByteCpyHuge(auxEntry.baAuxName, &pIsoMsgSta->pabVtData[0], 8);
             updateAuxAssignment(auxSection, &auxEntry);
          }
#endif
       }
       break;
   case auxiliary_input_status_type_2 :
	   VTC_handleAux((struct AUX_InputSignalData_T *)(pIsoMsgSta));
       break;
   default:
       break;
   }
}

static void VTC_SetObjValuesBeforeStore(iso_u8 u8Instance)
{



}

/* ************************************************************************ */
// Delete stored pool
iso_s16 VTC_PoolDeleteVersion(void)
{  
   // with V11 - String must be zero terminated (or should be 32 bytes long)
   iso_s16 s16Ret;
   iso_u8 au8VersionString[] = "       "; // We use spaces to delete the last stored pool from flash
   s16Ret = IsoVtcCmd_DeleteVersion(u8_CfVtInstance, au8VersionString);
   return s16Ret;
}

/* ************************************************************************ */
// Reload of objects during "application running"
iso_s16 VTC_PoolReload(void)
{
   iso_s16 iRet = E_NO_ERR;
   /* pointer to the pool data */
   const iso_u8*  pu8PoolData = 0;
   iso_u32  u32PoolSize = 0UL;
   iso_char poolFileName[128];

   getString("ObjectPool", "file_de", "pools/pool_de.iop", poolFileName, 128U);

   if (u8_poolChannel == 0)
   {
      #if !defined(CCI_USE_POOLBUFFER)
      u8_poolChannel = poolLoadByFilename(poolFileName);
      #else // !defined(CCI_USE_POOLBUFFER)
      u8_poolChannel = poolLoadByByteArray((iso_u8*)&pool_iop[0], sizeof(pool_iop));
      #endif // !defined(CCI_USE_POOLBUFFER)
   }

   poolOpen(u8_poolChannel, colour_256); // open a complete pool for a 256 colour VT
   u32PoolSize = (uint32_t)poolGetSize(u8_poolChannel);
   pu8PoolData = poolGetData(u8_poolChannel);

   if (IsoVtcPoolUpdate(u8_CfVtInstance, PoolTransferFlash, pu8PoolData, u32PoolSize, 0))
   {
      //iso_u16 wSKM_Scal = 0u;
      /* remove font from language pool (included from IsoDesigner)) */
      IsoVtcPoolSetIDRangeMode(u8_CfVtInstance, 23000, 23000, 0, NotLoad);
      /* Manipulating these objects */
      //wSKM_Scal = (iso_u16)IsoVtcPoolReadInfo(u8_CfVtInstance, PoolSoftKeyMaskScalFaktor);
      //sample IsoVtcPoolSetIDRangeMode(u8_CfVtInstance, 40012, 40012, wSKM_Scal, Centering);  /* Auxiliary function */
   }
   else
   {  // reload not possible - free pool
      poolFree(u8_poolChannel);
      u8_poolChannel = 0;
      iRet = E_ERROR_INDI;
   }
   return iRet;
}

/* ************************************************************************ */
// Callback function for setting the preferred assignment
static void CbAuxPrefAssignment(const VT_AUX_PREF_PARAM_T* psParams, VT_AUXAPP_T asAuxAss[], iso_s16* ps16MaxNumberOfAssigns)
{
   iso_s16 s16I = 0;
   iso_s16 s16NumbOfPrefAssigns = 0;
   VT_AUXAPP_T asPrefAss[20];
   iso_char auxSection[64]; // storing aux assigns depending on the pool label
   fillAuxSectionName(auxSection, 64U);

   /* Reading stored preferred assignment */
   s16NumbOfPrefAssigns = getAuxAssignment(auxSection, asPrefAss);

   if (s16NumbOfPrefAssigns > *ps16MaxNumberOfAssigns)
   {  /* we have more assignments than we can provide 
         (Increase also ISO_AUX_ENTRIES_INSTANCE_MAX if needed... size of asAuxAss[] is ISO_AUX_ENTRIES_INSTANCE_MAX)  */
      s16NumbOfPrefAssigns = *ps16MaxNumberOfAssigns;
   }

   for (s16I = 0; s16I < s16NumbOfPrefAssigns; s16I++)
   {
      asAuxAss[s16I] = asPrefAss[s16I];
   }
   *ps16MaxNumberOfAssigns = s16NumbOfPrefAssigns;
   (void)psParams;
}


/* ************************************************************************ */
// Multiple VT
iso_s16 VTC_NextVTButtonPressed(void)
{
   #define VT_LIST_MAX   5       /* Array size for VT cf handle entries */

   iso_s16 s16NumberOfVTs = 0, s16NumberAct = VT_LIST_MAX, iI = 0;
   iso_s16 s16HndCurrentVT;
   iso_s16 as16HandList[VT_LIST_MAX];

   s16HndCurrentVT = (iso_s16)IsoVtcGetStatusInfo(u8_CfVtInstance, VT_HND);   /* get CF handle of actual VT */
   /* Determine list number of actual VT */
   (void)IsoClientsReadListofExtHandles(virtual_terminal, VT_LIST_MAX, as16HandList, &s16NumberOfVTs);

   for (iI = 0; iI < s16NumberOfVTs; iI++)
   {
      if (s16HndCurrentVT == as16HandList[iI])
      {
         s16NumberAct = iI;
         break;
      }
   }

   /* Select next VT in list */ 
   if ((s16NumberOfVTs > 1) && (s16NumberAct != VT_LIST_MAX))
   {
      ISO_CF_INFO_T sUserVT;
      s16NumberAct++;
      if (s16NumberAct >= s16NumberOfVTs)
      {  /* select first VT in list*/
         s16NumberAct = 0;
      }
      iso_NmGetCfInfo(as16HandList[s16NumberAct], &sUserVT);
      IsoVtcMultipleNextVT(u8_CfVtInstance, CAST_TO_CONST_ISONAME_PTR(&sUserVT.au8Name));
      // NAME could be stored here in EEPROM
      // Application must go into safe state !!!
   }
   return 0;
}

/* ************************************************************************ */
iso_s16 VTC_Restart(void)
{
   if (u8_CfVtInstance != ISO_INSTANCE_INVALID)
   {  /* Hint: We allow the restart also during a possible pool load/upload/reload... */
      iso_s16 s16Ret;
      s16Ret = IsoVtcRestartInstance(u8_CfVtInstance, ISO_TRUE);
      if ((s16Ret == E_NO_ERR) && (u8_poolChannel > 0)) {
         poolFree(u8_poolChannel);  /* ... and close the pool channel in this case */
      }
   }
   else if (s16_CfHndVtClient != HANDLE_UNVALID)
   {  /* Test: Try to start again ... */
      AppVTClientLogin(s16_CfHndVtClient);
   }
   else { /* no CF handle */}
   return 0;
}

/* ************************************************************************ */
iso_s16 VTC_CloseInstance(void)
{
   if (u8_CfVtInstance != ISO_INSTANCE_INVALID)
   {
      (void)IsoVtcCloseInstance(u8_CfVtInstance);
   }
   return 0;
}

/* ************************************************************************ */
/* helper function  */
static void fillAuxSectionName(iso_char auxSection[], iso_u32 u32ArraySize) // TODO: consider moving function to AppMemAccess.cpp
{
   const iso_char cName[] = "CF-A-AuxAssignment-";
   iso_char au8Label[33];
   iso_u8 u8Idx = 0u, u8Pos = 0u;
   while ((cName[u8Idx] != 0) && (u8Idx < (u32ArraySize - 1UL)))
   {
      auxSection[u8Idx] = cName[u8Idx];
      u8Idx++;
   }
   auxSection[u8Idx] = 0;
   getString("ObjectPool", "label", "unknown", au8Label, 33U);
   while ((au8Label[u8Pos] != 0) && (u8Idx < (u32ArraySize - 1UL)))
   {
      auxSection[u8Idx] = au8Label[u8Pos];
      u8Idx++;
      u8Pos++;
   }
   auxSection[u8Idx] = 0;
}

/* ************************************************************************ */
#endif /* _LAY6_ */
/* ************************************************************************ */
