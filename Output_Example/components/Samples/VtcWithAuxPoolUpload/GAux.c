#include <string.h> // VTC sample strncmp memcmp
#include <stdlib.h> // VTC Aux pool loading...
#include <stdio.h>
#include "IsoCommonDef.h"
#include "IsoVtcApi.h"
#include "IsoClientsApi.h"
#include "GAux.h"
#include "esp_log.h"

#include "MyProject1.iop.h"
#include "MyProject1.c.h"

#if defined(_LAY6_) && defined(ISO_VTC_GRAPHIC_AUX)

static const char *TAG = "GAux";

#define USERPARAM_GAUX   ((ISO_USER_PARAM_TYPE)0xFF00u)

static const iso_u8 abPoolVersion[] = "       ";

/* pointer to the pool data which should be uploaded */
static iso_u8 *   pu8PoolData = 0;
static iso_u32    u32PoolSize = 0UL;

/* for graphical aux handling */
static void    CbVtcGAuxMsg(const ISOVT_MSG_STA_T *psMsg);
static iso_s16 CbVtcGAuxEvent(const IsoVtcGAux_ConnEv_Ts *pEvent);
static void    CbVtcGAuxPoolEvent(ISOPOOLCTRL_T *psPoolCtrl);
static void    SetGAuxPool(const IsoVtcGAux_ConnEv_Ts *pEvent);

static void    PoolDirectLoadObjects(ISOPOOLCTRL_T * psPoolCtrl, iso_u8 au8SrcPool[], iso_u32 u32SrcPoolSize);
static void    PoolSegmentedLoad(ISOPOOLCTRL_T * psPoolCtrl, iso_u8 au8SrcPool[], iso_u32 u32SrcPoolSize);

static void    ReducePool(iso_u8 pu8PoolDataIn[], iso_u32* pu32PoolSizeInOut);
#if 0
static void    CbPoolSecondaryAdaptation(OBJTYP_e eObjectType, iso_u16 u16ObjectId,
                     iso_u8 HUGE_C pau8Object[], iso_u32* pu32ObjectSize, ISO_USER_PARAM_T userParam);
#endif
/* app functions */
static iso_u32 PoolGetObjectOffset(const iso_u8 HUGE_C pau8ObjPool[], iso_u32 u32PoolSize,
    iso_u16 u16ObjIndex, iso_u16 u16ObjID);
static void    PoolLoadFromFile(const char * pcFilename);
static void    PoolFree(void);

void vtcGAux_CfInit(iso_s16 s16CfHandle, const ISO_USER_PARAM_T userParam, const char acPoolFilenameIn[])
{
   (void)userParam;
   /*(void)IsoVtcGAux_CfInit(s16CfHandle, userParam, CbVtcGAuxEvent, CbVtcGAuxMsg);*/
   (void)IsoVtcGAux_CfInit(s16CfHandle, USERPARAM_GAUX, CbVtcGAuxEvent, CbVtcGAuxMsg);
 

   /* Load the sample pool from file ... */
   // for a first time implementatioin use the provided IOP file
   PoolLoadFromFile(acPoolFilenameIn);

   /* Remove unnecessary objects from the provided IOP file */
#if 1
   ReducePool(pu8PoolData, &u32PoolSize);
#else 
   IsoPoolSecondaryAdaptInit(&CbPoolSecondaryAdaptation);
#endif 
}

void vtcGAux_ForwardAssignment(iso_s16 s16CfHandle, const ISOVT_MSG_STA_T* pIsoMsgSta)
{
/* set to 0 in case the forwarding can be done directly */
/* set to 1 in case the forwarding needs to be modified due to e.g. a pool mismatch */
#if(0)
    ISOVT_MSG_STA_T vtMsg = *pIsoMsgSta;

    iso_u16 u16IdFunction = vtMsg.wObjectID;        /* Function object ID */
    iso_u16 u16IdInput = vtMsg.wPara1;              /* Input object ID */
    iso_u8  au8MsgData[14u];
    memcpy(au8MsgData, vtMsg.pabVtData, sizeof(au8MsgData));

    // always display grafic object "20707" from IOP file at the provided position
    switch (u16IdFunction)
    {
        // replace image from assignment
        // use case: an unsupported entry shall be replaced by a specific image.
    case 29003:
        vtMsg.wObjectID = 20707;
        break;

        // keep all other from assignment 
        // default: if the object pool supports only the required aux assignment combinations.
    default:
        break;
    }

    (void)IsoVtcGAux_ForwardAssignment(s16CfHandle, &vtMsg, ISO_FALSE); /* ISO_FALSE means ignore connection ...*/
#else
    (void)IsoVtcGAux_ForwardAssignment(s16CfHandle, pIsoMsgSta, ISO_FALSE); /* ISO_FALSE means ignore connection ...*/
#endif
}

/* ************************************************************************ */
/* CBS for graphical aux handling */
/* ************************************************************************ */

/*  
   Application specific F-Command A3 response callback 
*/
static void CbVtcGAuxMsg(const ISOVT_MSG_STA_T *psMsg)
{
#ifdef ISO_DEBUG_ENABLED  /*  only for debug tracing */ 
    iso_DebugPrint("VtcGaux - Msg: Conn: %2.2x VT-Func: %2.2x iError: %4.2d Time: %8.4d\n",
       psMsg->u8Instance, psMsg->iVtFunction, psMsg->iErrorCode, psMsg->lTimeSt);
#endif /* ISO_DEBUG_ENABLED */
}

/* ************************************************************************ */
static iso_s16 CbVtcGAuxEvent(const IsoVtcGAux_ConnEv_Ts *pEvent)
{
   iso_s16 s16Ret = E_NO_ERR;

#ifdef ISO_DEBUG_ENABLED  /*  only for debug tracing */ 
   iso_DebugPrint("VtcGaux - Event: %d Conn: %2.2x WS: %4.4x GA: %4.4x Time: %8.4d\n",
      pEvent->eEventId, pEvent->u8ConnHnd, pEvent->s16WsCfHnd, pEvent->s16VtCfHnd, IsoClientsGetTimeMs());
#endif /* ISO_DEBUG_ENABLED */

   switch (pEvent->eEventId)
   {
   case IsoVtcAux_EvReadyToConnect:
      /* new connection or restart of existing connection */
      /* The connection handle "pEvent->u8ConnHnd" can be stored for later handling. */
      #if 1
      {  /* delay (IsoVtcAux_ConnWait) or disable (IsoVtcAux_ConnClose) start */
         /* we simulate waiting (event is called every second) ... */
         static iso_u32 u32WaitSteps = 0UL;
         u32WaitSteps++;
         if (u32WaitSteps == 1UL)
         {
            (void)IsoVtcGAux_SetConnection(pEvent->u8ConnHnd, IsoVtcAux_ConnWait);
         }
         else if (u32WaitSteps >= 10UL)
         {  /* we continue... */
            u32WaitSteps = 0UL;
            (void)IsoVtcGAux_SetConnection(pEvent->u8ConnHnd, IsoVtcAux_ConnContinue);
         }
         else { /* waiting before start */}
      }
      #endif /* 1 or 0 */
      break;
   case IsoVtcAux_EvGetVersions:
      if ((pEvent->u16DataSize > 0u) && (pEvent->pau8Data != 0))
      {  /* TP data form get (extended) versions received... pau8Data[0] := Function ...  */
         /* we do not check but set our pool version label ... if it is one of the version only a pool load is done */
         // Only if VT and VTC is Version 5 or higher 32 bytes are used else the first 7 bytes
#if 1
         (void)IsoVtcGAux_PoolSetVersionLabel(pEvent->u8ConnHnd, 32u, abPoolVersion);
#else
         (void)IsoVtcCmd_DeleteVersion(pEvent->u8ConnHnd, abPoolVersion);
#endif          
      }
      break;
   case IsoVtcAux_EvWaitForPool:
      /* Initalise the graphical aux pool upload */
      SetGAuxPool(pEvent);
      break;
   case IsoVtcAux_EvActivated:
      #if 0
      {  /* command sample: set aux function background color */
         iso_u16 u16ObjID;
         for (u16ObjID = 29002u; u16ObjID <= 29004; u16ObjID++)
         {  /* set background color of Aux Functions */
            (void)IsoVtcCmd_BackgroundColour(pEvent->u8ConnHnd, u16ObjID, 15u);
         }
         /* set background color of workingset object */
         (void)IsoVtcCmd_BackgroundColour(pEvent->u8ConnHnd, 0u, 10u);
         /* send invalid command to WS object */
         //(void)IsoVtcCmd_NumericValue(pEvent->u8ConnHnd, 0u, 44u);
      }
      #endif /* 1 or 0 */
      break;
   case IsoVtcAux_EvAborted:
   case IsoVtcAux_EvSafeState:
      /* The connection handle "pEvent->u8ConnHnd" is invalid and can be removed. */
      break;
   default:
      break;
   }

   return s16Ret;
}

/* ************************************************************************ */
static void SetGAuxPool(const IsoVtcGAux_ConnEv_Ts * pEvent)
{
    iso_u16 u16SKM_Scal = 0u;         // Scaling factor * 10000
    iso_u16 u16DM_Scal = 0u;           // Scaling factor * 10000
    ISOVT_POOL_TRANSFER_MODE_e eTransferMode;

    (void)IsoVtcGAux_PoolSetVersionLabel(pEvent->u8ConnHnd, 32u, abPoolVersion);
    (void)IsoVtcGAux_PoolSetConfig(pEvent->u8ConnHnd, colour_256,
        ISO_DESIGNATOR_WIDTH, ISO_DESIGNATOR_HEIGHT, ISO_MASK_SIZE);
    /* and set the pool upload method */
    /*
    eTransferMode = PoolTransferFlash;       // normal pool upload with RAM buffer and manipulations
    eTransferMode = PoolTransferSeqmented;   // segmented pool upload with RAM buffer and manipulations
    //eTransferMode = PoolTransferDataBlocks;  // not supported by this sample
    eTransferMode = PoolTransferDirectLoad;  // direct transfer pool upload without pool RAM buffer and simple manipulations
    eTransferMode = PoolTransferRaw;         // for testing: transfer a pool without manipulations.... (single ETP)
    */
    eTransferMode = PoolTransferFlash;

    if (eTransferMode == PoolTransferDirectLoad)
    {  /* direct transfer pool upload without pool RAM buffer and simple manipulations */
       /* Sample: Set the direct load pool transfer repetition value for one loop */
       (void)IsoVtcPoolSetDTRepeatRate(10);
    }

    /* Hint not all transfer modes need all parameters - for the sample we provide valid values for all possibilities */
    (void)IsoVtcGAux_PoolLoad(pEvent->u8ConnHnd, eTransferMode, pu8PoolData, u32PoolSize, 200UL, 0u, CbVtcGAuxPoolEvent);

    /* set manipulations */
    u16DM_Scal = (iso_u16)IsoVtcGAux_PoolReadInfo(pEvent->u8ConnHnd, PoolDataMaskScalFaktor);          // Calling after PoolInit!!!
    u16SKM_Scal = (iso_u16)IsoVtcGAux_PoolReadInfo(pEvent->u8ConnHnd, PoolSoftKeyMaskScalFaktor);



    u16DM_Scal /= 2;
    u16SKM_Scal /= 2;

    ESP_LOGW(TAG, "PoolDataMaskScalFaktor    =  %i", u16DM_Scal);
    ESP_LOGW(TAG, "PoolSoftKeyMaskScalFaktor =  %i", u16SKM_Scal);

    (void)IsoVtcGAux_PoolSetIDRangeMode(pEvent->u8ConnHnd, 29000, 29099, u16SKM_Scal, Centering);  // Auxiliary function
    (void)IsoVtcGAux_PoolSetIDRangeMode(pEvent->u8ConnHnd, 20900, 20999, u16SKM_Scal, Scaling);    // Pictures in auxiliaries
    (void)u16DM_Scal;
}

/* ************************************************************************ */
/*! \brief  Callback function which is called from the pool service.
    \param[in]  \wp{psPoolCtrl, ISOPOOLCTRL_T*}
            Pointer to the message.
            See #ISOPOOLCTRL_T for more information.
*/
static void CbVtcGAuxPoolEvent(ISOPOOLCTRL_T * psPoolCtrl)
{
   switch (psPoolCtrl->ePoolCtrl)
   {
   case PoolObjectRequest:
   /* Direct load: pool objects requested */
      if (psPoolCtrl->ePoolTransferMode == PoolTransferDirectLoad) {
         PoolDirectLoadObjects(psPoolCtrl, pu8PoolData, u32PoolSize);
      }
      break;
   case PoolFirstBlockRequest:   /* PoolTransferDataBlocks */
   case PoolBlockRequest:
      /* PoolTransferSeqmented or PoolTransferDataBlocks  - read requested pool data */
      if (psPoolCtrl->ePoolTransferMode == PoolTransferSeqmented) {
         PoolSegmentedLoad(psPoolCtrl, pu8PoolData, u32PoolSize);
      }
      break;
   case PoolGetMemoryFailed:
      /* There is not enough memory available on VT */
#ifdef ISO_DEBUG_ENABLED
      iso_DebugPrint("Get Memory - VT has not enough memory \n");
#endif /* ISO_DEBUG_ENABLED */
      /* -> Application reaction: Choosing a smaller pool ( e. g. set a alternative AppPoolSettingsSeg-function ) */
      break;
   case PoolStatemachine:
#ifdef ISO_DEBUG_ENABLED
      switch (psPoolCtrl->ePoolServState)
      {
      case PoolLazy: iso_DebugTrace("Poolstate: PoolLazy               \n"); break;
      case PoolLoadInit: iso_DebugTrace("Poolstate: PoolLoadInit           \n"); break;
      case PoolLoadSeg: iso_DebugTrace("Poolstate: PoolLoadSeg            \n"); break;
      case PoolScanSeg: iso_DebugTrace("Poolstate: PoolScanSeg            \n"); break;
      case PoolScanning: iso_DebugTrace("Poolstate: PoolScanning           \n"); break;
      case PoolWaitTransfer: iso_DebugTrace("Poolstate: PoolWaitTransfer       \n"); break;
      case PoolGetMemory: iso_DebugTrace("Poolstate: PoolGetMemory          \n"); break;
      case ETPBuffLoad: iso_DebugTrace("Poolstate: ETPBuffLoad            \n"); break;
      case ETPBuffLoadSeg: iso_DebugTrace("Poolstate: ETPBuffLoadSeg         \n"); break;
      case ETPBuffScanSeg: iso_DebugTrace("Poolstate: ETPBuffScanSeg         \n"); break;
      case ETPBuffManiSeg: iso_DebugTrace("Poolstate: ETPBuffManiSeg         \n"); break;
      case ETPBlockManipulated: iso_DebugTrace("Poolstate: ETPBlockManipulated    \n"); break;
      case ETPBuffLoadSegAfterETP: iso_DebugTrace("Poolstate: ETPBuffLoadSegAfterETP \n"); break;
      case ETP_start: iso_DebugTrace("Poolstate: ETP_start              \n"); break;
      case ETP_Trans_running: iso_DebugTrace("Poolstate: ETP_Trans_running      \n"); break;
      case ETP_finished: iso_DebugTrace("Poolstate: ETP_finished           \n"); break;
      default: break;
      }
#endif /* ISO_DEBUG_ENABLED */
      break;
   case PoolFileCloseRequest:
      /* V12: all transfer methods - all objects are scanned or loaded */
      if (psPoolCtrl->ePoolTransferMode == PoolTransferSeqmented) {
         PoolSegmentedLoad(psPoolCtrl, pu8PoolData, u32PoolSize);
      }
      break;
   default:
      break;
   }
}

/* ************************************************************************ */
/*! \brief  Direct pool transfer object load function.
    \details The function is used from the test application
            to give the next objects to the ISOBUS driver.

    \param[in]  \wp{psPoolCtrl, ISOPOOLCTRL_T*}
            Pointer to the message.
            See #ISOPOOLCTRL_T for more information.
    \param[in]  \wpp{au8SrcPool, const #iso_u8 []}
            Pointer to the source/flash pool array.
    \param[in]  \wp{u32SrcPoolSize, iso_u32}
            Size of the source pool in bytes.
*/
static void PoolDirectLoadObjects(ISOPOOLCTRL_T * psPoolCtrl, iso_u8 au8SrcPool[], iso_u32 u32SrcPoolSize)
{
    static iso_u32 u32PoolPos = 0UL;
    iso_u16 u16RelIndex;
    iso_u32 u32Offset;

    /* BlockSize contains a request counter starting with 1 */
    if (psPoolCtrl->u32BlockSizeLoad == 1UL)
    {   /* reset pool position */
        u32PoolPos = 0UL;
    }

    if (u32PoolPos < u32SrcPoolSize)
    {
        iso_u16 u16Nr = 5u;
        do
        {   /* max objects */
            u16RelIndex = u16Nr * (iso_u16)psPoolCtrl->u32BlockSizeLoad;
            u32Offset = PoolGetObjectOffset(&au8SrcPool[u32PoolPos], (u32SrcPoolSize - u32PoolPos),
                u16RelIndex, 0xFFFFu);
            u16Nr--;
        } while ((u32Offset > 0x0FFFFFuL) && (u16Nr > 0u)); /* Test limit to 1 MB */


        if (u32Offset == 0UL)
        {   /* last block */
            u32Offset = u32SrcPoolSize - u32PoolPos;
        }

        if (u32Offset > 0x0000FFFFuL)
            iso_DebugTrace("LoadPoolObjects: PoolPos=%i \t size=%i bigger 65KB\n", u32PoolPos, u32Offset);
        else
            iso_DebugTrace("LoadPoolObjects: PoolPos=%i \t size=%i \n", u32PoolPos, u32Offset);

        psPoolCtrl->pbAddress = &au8SrcPool[u32PoolPos];
        psPoolCtrl->u32BlockSizeLoad = u32Offset;
        psPoolCtrl->u32BlockSizeReq = ISO_POOLDATA_READY;
        u32PoolPos += u32Offset;
    }
    else
    {   /* no more data - pool finished */
        iso_DebugTrace("LoadPoolObjects finished for pool with size %i\n", u32SrcPoolSize);
        psPoolCtrl->pbAddress = 0;
        psPoolCtrl->u32BlockSizeLoad = 0UL;   /* set size to zero */
        psPoolCtrl->u32BlockSizeReq = ISO_POOLDATA_READY; /* and data valid flag */
    }
}

/* ************************************************************************ */
/*! \brief  Segmented pool transfer callback function.
    \details The function is used from the test application
            to give the next objects to the ISOBUS driver.

    \param[in]  \wp{psPoolCtrl, ISOPOOLCTRL_T*}
            Pointer to the message.
            See #ISOPOOLCTRL_T for more information.
    \param[in]  \wpp{au8SrcPool, const #iso_u8 []}
            Pointer to the source/flash pool array.
    \param[in]  \wp{u32SrcPoolSize, iso_u32}
            Size of the source pool in bytes.
*/
static void PoolSegmentedLoad(ISOPOOLCTRL_T * psPoolCtrl, iso_u8 au8SrcPool[], iso_u32 u32SrcPoolSize)
{
    static iso_u32 u32PoolPos = 0UL;

    if (psPoolCtrl->ePoolCtrl == PoolFileCloseRequest)
    {  /* finished scan and transfer - file/memory can be freed */
        u32PoolPos = 0UL;
    }
    else /* PoolBlockRequest */
    {
        iso_u32  u32Length, u32I;

        /* get length of pool data for this run */
        u32Length = u32SrcPoolSize - u32PoolPos;
        if (u32Length > psPoolCtrl->u32BlockSizeReq)
        {
            u32Length = psPoolCtrl->u32BlockSizeReq;
        }

        /* copy pool data to buffer */
        for (u32I = 0uL; u32I < u32Length; u32I++)
        {
            psPoolCtrl->pbAddress[u32I] = au8SrcPool[u32PoolPos + u32I];
        }

        psPoolCtrl->u32BlockSizeLoad = u32Length;
        u32PoolPos += u32Length;

        /* check for end off source pool -> Hint we have a scan and an upload.... */
        if (u32PoolPos >= u32SrcPoolSize)
        {  /* End of pool */
            u32PoolPos = 0uL;
        }
    }
}

/* ************************************************************************ */

/* ************************************************************************ */
/*! \brief  Helper function to load a pool from an iop file to a RAM buffer.

    \param[in]  \wpp{pau8ObjPool, const iso_u8 HUGE_C[]}
            Pointer to the object pool byte array.
    \param[in]  \wp{u32PoolSize, iso_u32}
            Size of the object pool array in bytes.
    \param[in]  \wp{u16ObjIndex, iso_u16}
            Object index starting with 0 for the first object. \n
            Set 0 to disable the index check.
    \param[in]  \wp{u16ObjID, iso_u16}
            Object-ID of a object. \n
            set to 0xFFFFu to disable the object ID check.

    \retval iso_u32
            Offset in bytes where the object are located.
*/
static iso_u32 PoolGetObjectOffset(const iso_u8 HUGE_C pau8ObjPool[], iso_u32 u32PoolSize,
    iso_u16 u16ObjIndex, iso_u16 u16ObjID)
{
    iso_u32 u32Offet = 0UL;
    if ((pau8ObjPool != 0) && (u32PoolSize > 0UL)
        && ((u16ObjIndex > 0u) || (u16ObjID != 0xFFFFu)))
    {
        iso_u32 u32Pos = 0UL;
        iso_u16 u16Index = 0u;
        while ((u32Pos + 3UL) < u32PoolSize)
        {
            iso_u32 u32SSize;
            u32SSize = IsoVtcPoolObjSize(&pau8ObjPool[u32Pos]);
            if (u32SSize == 0UL)
            {  /* error in pool - exit loop */
                u32Pos = u32PoolSize;
            }
            else
            {
                iso_u16 u16ID;
                u16ID = ((iso_u16)pau8ObjPool[u32Pos]) | (iso_u16)((iso_u16)pau8ObjPool[u32Pos + 1uL] << 8u);
                if (((u16Index == u16ObjIndex) && (u16Index > 0u)) || (u16ID == u16ObjID))
                {  /* object found - store pos and exit loop */
                    u32Offet = u32Pos;
                    u32Pos = u32PoolSize;
                }
                else
                {  /* next object */
                    u32Pos += u32SSize;
                    u16Index++;
                }
            }
        }
    }

    return u32Offet;
}


#if defined(_MSC_VER )
#pragma warning(disable : 4996) /* for fopen() Hint disables also ISO_DEPRECATED */
#endif // defined(_MSC_VER )

/* ************************************************************************ */
/*! \brief  Helper function to load a pool from an iop file to a RAM buffer.
    \param[in]  \wpp{pcFilename, const char *}
            Pointer to the file name string.
*/
static void PoolLoadFromFile(const char * pcFilename)
{
    /* load pool from file into RAM */
    FILE *pFile;
    if (pu8PoolData)
    {   /* free the pool data RAM */
        PoolFree();
    }

    pFile = fopen(pcFilename, "rb");
    if (pFile)
    {
        fseek(pFile, 0L, SEEK_END);
        u32PoolSize = ftell(pFile);
        pu8PoolData = malloc(u32PoolSize);
        fseek(pFile, 0L, SEEK_SET);
        u32PoolSize = (iso_u32)fread(pu8PoolData, sizeof(iso_u8), u32PoolSize, pFile);
        fclose(pFile);
    }
}

/* ************************************************************************ */
static void PoolFree(void)
{
    if (pu8PoolData)
    {   /* free the pool data RAM */
        free(pu8PoolData);
        pu8PoolData = 0;
        u32PoolSize = 0UL;
    }
}

/* ************************************************************************ */
#if 0
static void  CbPoolSecondaryAdaptation(OBJTYP_e eObjectType, iso_u16 u16ObjectId,
   iso_u8 HUGE_C pau8Object[], iso_u32* pu32ObjectSize, ISO_USER_PARAM_T userParam)
{
   (void)u16ObjectId;
   if (userParam == USERPARAM_GAUX)
   {  /* our user parameter for an GAux client pool -> reduce it */
      iso_bool copyObject = ISO_FALSE;
      switch (eObjectType)
      {
      case WorkingSet:  /* Top level object describes an implement (working set). */
         copyObject = ISO_TRUE;
         break;
         /* Picture graphic object */
      case PictureGraphic: /* Used to output a picture graphic (bitmap). */
      {
         iso_u16 width = (pau8Object[6] << 8) + pau8Object[5];
         iso_u16 hight = (pau8Object[8] << 8) + pau8Object[7];
         if ((width <= 64U) && (hight <= 64U))
         {
            copyObject = ISO_TRUE;
         }

         break;
      }
#if 1    /* object pointer object - CCI A3 feature BugID 11522 */
      case ObjectPointer:
         copyObject = ISO_TRUE;
         break;
#endif 
      /* Auxiliary control */
      case AuxiliaryFunction2: /* Defines the designator and function type 2. OK*/
      {
         iso_u8 auxFunctionType = pau8Object[4] & 0x0FU;
         if (auxFunctionType == 2)   // non latching boolean
         {
            copyObject = ISO_TRUE; // in use for a break point.
         }

         break;
      }
      default:
         break;
      }

      if (copyObject == ISO_FALSE)
      {  /* WIP - first test to remove objects during runtime */
         *pu32ObjectSize = 0UL;
      }
   }
}
#endif
/* ************************************************************************ */
static iso_u16 getU16(iso_u8 data[]);

void ReducePool(iso_u8 pu8PoolDataInOut[], iso_u32* pu32PoolSizeInOut)
{
    if ((pu8PoolDataInOut != NULL) && (pu32PoolSizeInOut != NULL))
    {
        iso_u32 u32PoolSrcIdx = 0;
        iso_u32 u32PoolCopyIdx = 0;
        iso_u32 u32PoolSize = *pu32PoolSizeInOut;
        while (u32PoolSrcIdx < u32PoolSize)
        {
            iso_bool copyObject = ISO_FALSE;
            iso_u8* poolData = &pu8PoolDataInOut[u32PoolSrcIdx];
            iso_u32 objectSize = IsoVtcPoolObjSize(poolData);
            iso_u32 newObjectSize = objectSize;
//          iso_u16 objectID = getU16(poolData);
            OBJTYP_e eObjTyp = (OBJTYP_e)poolData[2];
            switch (eObjTyp)
            {
            case WorkingSet:  /* Top level object describes an implement (working set). */
                copyObject = ISO_TRUE;
                break;

            /* Picture graphic object */
            case PictureGraphic: /* Used to output a picture graphic (bitmap). */
            {
                iso_u16 width = getU16(&poolData[5]);
                iso_u16 hight = getU16(&poolData[7]);
                if ((width <= 64U) && (hight <= 64U))
                {
                    copyObject = ISO_TRUE;
                }
                else if ((width <= 128U) && (hight <= 128U))
                {	// e.g. crop all pictures smaller then 128 pix.
                    if (IsoPoolCropCenterOfPictureObject(poolData, 64, 64, &newObjectSize) == E_NO_ERR)
                    {
                        copyObject = ISO_TRUE;
                    }
                }
                else { /* skip picture object */ }
                break;
            }

            /* Auxiliary control */
            case AuxiliaryFunction2: /* Defines the designator and function type 2. OK*/
            {
                iso_u8 auxFunctionType = poolData[4] & 0x0FU;
                if (auxFunctionType == 2)   // non latching boolean
                {
                    copyObject = ISO_TRUE; // in use for a break point.
                }

                break;
            }
#if 1    /* object pointer object - CCI A3 feature BugID 11522 */
            case ObjectPointer:
               copyObject = ISO_TRUE;
               break;
#endif 
            default:
                break;
            }

            if ((copyObject != ISO_FALSE) && (newObjectSize > 0))
            {
                memmove(&pu8PoolDataInOut[u32PoolCopyIdx], poolData, newObjectSize);
                u32PoolCopyIdx += newObjectSize;
            }

            u32PoolSrcIdx += objectSize;
        }

        *pu32PoolSizeInOut = u32PoolCopyIdx;
    }
    else
    {
        if (pu32PoolSizeInOut != NULL)
        {
            *pu32PoolSizeInOut = 0;
        }
    }
}

static iso_u16 getU16(iso_u8 data[])
{
    return (iso_u16)((iso_u16)data[1] << 8) | (iso_u16)(data[0]); 
}

#endif /* defined(_LAY6_) && defined(ISO_VTC_GRAPHIC_AUX) */
