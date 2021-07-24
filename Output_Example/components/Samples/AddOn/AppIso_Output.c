/*! \file
    \brief       Debug output functions for the driver callbacks. 
    \copyright   Wegscheider Hammerl Ingenieure Partnerschaft

*/

#include "IsoDef.h"
#include "IsoMnNiuApi.h"

#include "AppIso_Output.h"

/* ******************************************************************* */
/*!
    \brief        This function is called of the driver in order to give information to the application. \n
                  This information can have several reasons ( -> error classes ): 
                  - Configuration errors ( driver informs that an array, buffer is to small -> IsoConfig.h )
                  - Network errors ( an error code is received of the bus e. g. neg. response of a VT command )
                  - Application software errors ( wrong use of API-function ... )

                  With the help of the parameters its possible to find the affected function and source line. \n
                  An extra help page is in preparation.
                 
    \param[out]      \wp{bFun, iso_u8}         
                     Concerned function see IsoDef.h
    \param[out]      \wp{bLocation, iso_u8}     
                     Concerned module see #M_DATA ... in IsoDef.h
    \param[out]      \wp{iCause, iso_s16}
                     Error cause see #E_NO_ERR ... in IsoDef.h     
    \param[out]      \wp{s32TimeMs, iso_s32}
                     Time stamp in milliseconds 
 */
void CbErrorOutp(iso_u8 bFun, iso_u8 bLocation, iso_s16 iCause, iso_s32 s32TimeMs)
{
#if defined(ISO_DEBUG_ENABLED) || defined(DOXYGEN)
   const iso_char *strMod, *strFun, *strCau;

   switch ( bLocation )
   {  /* Core driver  */                          
      case M_DRV:  
         strMod = "Core     ";
         switch (bFun)
         {
            case ISOCANMSGREC:       strFun = "iso_CoreCanMsgRec()"; break;
            case ISODRVINIT:         strFun = "iso_drvInitIntern()"; break;
            case ISODRVCANINIT:      strFun = "iso_drvInitCanNodes()"; break;
            case ISOGETPTRCANNODE:   strFun = "iso_drvGetNodePtr()"; break;
            case ISODRVCYCLE:        strFun = "iso_drvCyclicRun "; break;
            default:                 strFun = "Unknown           "; break;
         }   
         break;   
      case M_DD  :  
         strMod = "Core DD  ";
         switch (bFun)
         {
            case ISODDPROCMSG:       strFun = "iso_ddDistributeMsg()"; break;
            default:                 strFun = "Unknown           "; break;
         }           
         break;
      case M_DATA  :  
         strMod = "Core Data";
         switch (bFun)
         {
            case ISODLPGNSEND:       strFun = "iso_dlPgnSend() "; break;
            /* case ISOBROADCASTSEND:   strFun = "IsoBroadcastSend()"; break; */
            case ISOFPPRECEIVE:      strFun = "iso_TlNmeaFptReceive()"; break;
            case ISOOPENTP:          strFun = "iso_tlOpenTransport()"; break;
            case ISORELEASETP:       strFun = "iso_tlReleaseChannel()"; break;
            case ISOTLDOSEND:        strFun = "iso_tlDoSend()    "; break;
            case ISOTLDIRECTSEND:    strFun = "TL_DoTpSingleProcess()"; break;
            case ISOCORESETSTATE:    strFun = "iso_CoreSetState()"; break;
            default:                 strFun = "Unknown           "; break;
         }           
         break;
      case M_USER  :  
         strMod = "Core User";
         switch (bFun)
         {
            case ISOUSERADD:         strFun = "iso_nmUserDataSet()"; break;
            case ISOUSERGETDATA:     strFun = "iso_nmUserFillCfInfo()"; break;
            default:                 strFun = "Unknown           "; break;
         }   
         break;
      case M_NET   :
         strMod = "Core Net ";
         switch (bFun)
         {  
            case ISOUSERANNOUNCE:      strFun = "iso_nmUserAnnounce()"; break;
            case ISOUSERFORCEANNOUNCE: strFun = "iso_nmUserExternForceAnnounce()"; break;
            /* case ISOUSERLOGOUT:       strFun = "IsoUserLogOut()   "; break; */
            default:                   strFun = "Unknown           "; break;
         }     
         break;
      case M_NMNET:
         strMod = "Core Nm  ";
         switch (bFun)
         {
            case ISONM_LISTOFHANDLES:         strFun = "iso_NmReadListOfCfHandles()"; break;
            default:                          strFun = "Unknown           "; break;
         }
         break;

      case M_NIU: /* NIU management */
         strMod = "Core NIU ";
         switch (bFun)
         {
            case ISONIU_FUNCTION:           strFun = "NIU_Function()    "; break;
            case ISONIU_FN_INIT:            strFun = "iso_NiuInit()     "; break;
            case ISONIU_FN_PROCESS_REQUEST: strFun = "iso_niuProcessMsg()"; break;
            case ISONIU_FN_CYCLIC_RUN:      strFun = "iso_niuCyclicRun()"; break;
            default:                        strFun = "Unknown "; break;
         }
         break;
      case M_NL: /* NIU network layer */
         strMod = "Core NL  ";  
         switch (bFun)
         {
            case ISONL_FUNCTION:            strFun = "NL_Function()     "; break;
            case ISONL_FN_INIT:             strFun = "iso_nlInit()      "; break;
            case ISONL_FN_PROCESS_CAN_MSG:  strFun = "iso_nlProcessMsg()"; break;
            case ISONL_FN_CYCLIC_RUN:       strFun = "iso_nlCyclicRun   "; break;
            case ISONL_FN_DO_BRIDGING:      strFun = "NL_DoBridging()   "; break;
            case ISONL_FN_DO_ROUTING:       strFun = "NL_DoRouting()    "; break;
            case ISONL_FN_FILTER_MSG:       strFun = "NL_FilterMsg()    "; break;
            case ISONL_FN_TRANSMIT_MSG:     strFun = "NL_TransmitMsg()  "; break;
            case ISONL_FN_TR_TABLE:         strFun = "NL_SetTREntry()   "; break;
            default:                        strFun = "Unknown "; break;
         }
         break;

      /* Base driver */
      case M_BASE:
         strMod = "Base     ";
         switch (bFun)
         {
            case ISOUSERADD:    strFun = "iso_BaseMemberAdd()"; break;
            default:            strFun = "Unknown           "; break;
         }
         break;
      case M_APLAY:
         strMod = "Base AL  ";
         switch (bFun)
         {
            case ISOAL_PGNTXNEW:            strFun = "iso_AlPgnTxNew()  "; break;
            case ISOAL_PGNRXNEW:            strFun = "iso_AlPgnRxNew()  "; break;
            case ISOAL_PGNACTIVATE:         strFun = "iso_AlPgnActivate()"; break;
            case ISOAL_PGNDEACTIVATE:       strFun = "iso_AlPgnDeactivate()"; break;
            case ISOAL_PGNDISABLE:          strFun = "iso_AlPgnDisable()"; break;
            case ISOAL_PGNCHANGEPRIORITY:   strFun = "iso_AlPgnTxChangePriority()"; break;
            case ISOAL_PGNCHANGESRCDEST:    strFun = "iso_AlPgnChangeSrcDestination()"; break;
            case ISOAL_PGNSETREPETITIONRATE: strFun = "iso_AlPgnTxSetRepetitionRateMs()"; break;
            case ISOAL_PGNRXREQUEST:        strFun = "iso_AlPgnRxRequest()"; break;
            case ISOAL_PGNRXREQUESTCYC:     strFun = "iso_AlPgnRxRequestCyclic()"; break;
            case ISOAL_PGNTXSETLIMITS:      strFun = "iso_AlPgnTxSetLimitsReqForRepet()"; break;
            case ISOAL_PGNTXSEND:           strFun = "iso_AlPgnTxSend() "; break;
            case ISOAL_PGNSEND:             strFun = "IsoAlPGNSend()    "; break;
            case ISOAL_RUN:                 strFun = "IsoAlRunPGN()     "; break;
            case ISOAL_PGNCHANGEDATASIZE:   strFun = "iso_AlPgnTxChangeDataSize()"; break;
            default:                        strFun = "Unknown           "; break;
         }
         break;
      case M_SPN:
         strMod = "Base SPN ";
         switch (bFun)
         {
            case ISOSPNDEFINE:     strFun = "iso_SpnDefineSpn()"; break;
            case ISOALPGNDATASET:  strFun = "iso_SpnDataSet()  "; break;
            case ISOALPGNDATAREAD: strFun = "iso_SpnDataRead() "; break;
            case ISOALSPNADDDTC:   strFun = "iso_SpnDMAddDTC() "; break;
            default:               strFun = "Unknown           "; break;
         }
         break;

      /* Client driver */
      case M_CLSH:
         strMod = "Client Sh";
         switch (bFun)
         {
            case ISOCLSHREADLISTEXTHAND: strFun = "IsoClientsReadListofExtHandles()"; break;
            case ISOCLSHMSGDISTRIBUTOR:  strFun = "IsoCbDataOfBasicDistributor()"; break;
            default:                     strFun = "Unknown "; break;
         }
         break;
      case M_WOSE  :  
         strMod = "Client Wo";
         switch (bFun)
         {
            case ISOADDWORKINGSETMEMBER: strFun ="IsoAddWorkingSetMember()"; break;
            default:                     strFun ="Unknown           "; break;
         }  
         break;
      
      /* Task controller client */
      case M_TCCTRL :  
         strMod = "TC Ctrl   ";
         switch (bFun)
         {
            case ISOTC_STATUSREC:       strFun ="IsoTcStatusRec()  "; break;
            default:                    strFun ="Unknown           "; break;
         }  
         break;
      case M_TCCONN :  
         strMod = "TC Conn   ";
         switch (bFun)
         {
            case ISOTC_INSTCMD:           strFun = "IsoTC_InstCmd()   "; break;
            case ISOTC_CONDOPROCESS:      strFun = "IsoTcConnDoProcess()"; break;
            case ISOTC_SUBCOMMANDREC:     strFun = "IsoTC_SubCommandRec()"; break;
            case ISOTC_SETPREFDL:         strFun = "IsoTC_SetPrefDL() "; break;
            case ISOTC_SETPREFTC:         strFun = "IsoTC_SetPrefTC() "; break;
            case ISOTC_MOVETOANOTHERTC:   strFun = "IsoTC_MoveToAnotherTCoDL()"; break;
            case ISOTC_DEVICESETVERSION:  strFun = "IsoTC_SetVersionMsg()"; break;
            default:                      strFun = "Unknown           "; break;
         }
         break;
      case M_TCPD :  
         strMod = "TC PD    ";
         switch (bFun)
         {
            case ISOTC_PROCESSDATADEFTRIGGER_SET:  strFun = "IsoTC_ProcessDataDefTrigger_Set()"; break;
            default:                               strFun = "Unknown           "; break;
         }           
         break;
      case M_TCPOOL :  
         strMod = "TC Pool  ";
         switch (bFun)
         {
            case ISOTC_SUBCMDPOOL:              strFun = "IsoTcClSubCmdToPoolService()"; break;
            case ISOTC_DEVICE_SET:              strFun = "IsoTC_DeviceExt_Set()"; break;
            case ISOTC_DEVICEELEMENT_SET:       strFun = "IsoTC_DeviceElement_Set()"; break;
            case ISOTC_DEVICEPROCESSDATA_SET:   strFun = "IsoTC_DeviceProcessData_Set()"; break;
            case ISOTC_DEVICEPROPERTY_SET:      strFun = "IsoTC_DeviceProperty_Set()"; break;
            case ISOTC_DEVICEVALUEPRESENT_SET:  strFun = "IsoTC_DeviceValuePresent_Set()"; break;
            case ISOTC_ADDDPDOBJECT:            strFun = "IsoTC_AddDPDObject()"; break;
            case ISOTC_ADDDPTOBJECT:            strFun = "IsoTC_AddDPTObject()"; break;
            case ISOTC_CHANGE_DESIGNATOR:       strFun = "IsoTC_ChangeDesignator_Send()"; break;
            case ISOTC_RELOADDDOBJECTS:         strFun = "IsoTC_ReloadDDObjects()"; break;   
            default:                            strFun = "Unknown           "; break;
         }           
         break;

      /* VT-Client */
      case M_ALARM :  
         strMod = "VT Alarm ";
         switch (bFun)
         {
            case ISOALARMCMD:          strFun = "IsoAlarmCmd()    "; break;
            default:                   strFun = "Unknown          "; break;
         }     
         break;
      case M_AUX   :  
         strMod = "VT Aux   ";
         switch (bFun)
         {
            case ISOAUXIMPCYCLIC:  strFun ="IsoAuxImpCyclic() "; break;
            case ISOAUXASSIGNEXT:  strFun ="AuxFunctionAssignExt()"; break;
            case ISOAUXFUNCTOAPP:  strFun ="AuxFunctionToApplication()"; break;
            case ISOAUXPREFASSIGN: strFun ="IsoAuxPreferredAssignSend()"; break;
            default:               strFun ="Unknown           "; break;
         }  
         break;
      case M_VTCPOOL : /* old M_POOL: */
         strMod = "VT Pool  "; 
         switch (bFun)
         {
            case ISOPOOLSETIDRANGEMODE: strFun ="VtcPoolSetIDRangeMode()"; break;
            case ISOPOOLMANIPULATE:     strFun ="PoolObjManipulate()"; break;
            case ISOPOOLRUN:            strFun ="VtcPoolServiceCycle()"; break;
            case ISOPOOLSCAN:           strFun ="PoolObjSingleScan()"; break;
            case ISOPOOLTESTIFLOAD:     strFun ="PoolObjTestIfLoad()"; break;
            default:                    strFun ="Unknown           "; break;
         }              
         break;

      case M_UTPICT:  
         strMod = "VT Pict  ";
         switch (bFun)
         {
            case POOLOBJPICTCONVERT          :strFun ="PoolObjPictureConvert()"; break;
            default:                          strFun ="Unknown            "; break;
         }  
         break;
      case M_VT : 
         strMod = "VT       ";
         switch (bFun)
         {
            case ISOVTMULTIPLENEXTVT:  strFun = "IsoVtcMultipleNextVT()"; break;
            case ISOVTRUN:             strFun = "ProcessState()    "; break;
            case ISOVTINIT:            strFun = "IsoVtcCreateInstance()"; break;
            case ISOWORKINGSET:        strFun = "VtcWorkingSetMsg()"; break;
            default:                   strFun = "Unknown "          ; break;
         }
         break;
      case M_VTCAUX:
         strMod = "VT GAux  ";
         switch (bFun)
         {
         case ISOWORKINGSET:  strFun = "DoStatePublishWorkingSet()"; break;
         case ISOVTRUN:       strFun = "DoStateRequestVtConfig()"; break;
         default:
            switch (iCause)
            {
               case E_COM:    strFun = "DoConnMaintenance()"; break;
               case E_NOACT:  strFun = "DoStateRequestVtConfig()"; break;
               case E_CANMSG_MISSED:  strFun = "CheckStateCommand()"; break;
               case E_WARN:   strFun = "DoStateRequestXyz() message not expected"; break;
               default:       strFun = "Unknown "; break;
            }
            break;
         }
         break;
      case M_VTCMD:
         strMod = "VT CmdMsg";
#if defined(_LAY6_)
         switch (bFun)
         {  /* Annex F */
            case (iso_u8)select_active_workingset: strFun = "IsoVtcCmd_SelectActiveWorkingSet()"; break;
            case (iso_u8)esc                     : strFun = "IsoVtcCmd_ESC()   "; break;
            case (iso_u8)hide_show_object        : strFun = "IsoVtcCmd_ObjHideShow()"; break;
            case (iso_u8)enable_disable_object   : strFun = "IsoVtcCmd_ObjEnableDisable()"; break;
            case (iso_u8)select_input_object     : strFun = "IsoVtcCmd_ObjSelectInput()"; break;
            case (iso_u8)control_audio_device    : strFun = "IsoVtcCmd_CtrlAudioSignal()"; break;
            case (iso_u8)set_audio_volume        : strFun = "IsoVtcCmd_SetAudioVolume()"; break;
            case (iso_u8)change_child_location   : strFun = "IsoVtcCmd_ChildLocation()"; break;
            case (iso_u8)change_size             : strFun = "IsoVtcCmd_Size()  "; break;
            case (iso_u8)change_background_colour: strFun = "IsoVtcCmd_BackgroundColour()"; break;
            case (iso_u8)change_numeric_value    : strFun = "IsoVtcCmd_NumericValue()"; break;
            case (iso_u8)change_end_point        : strFun = "IsoVtcCmd_EndPoint()"; break;
            case (iso_u8)change_font_attributes  : strFun = "IsoVtcCmd_FontAttributes()"; break;
            case (iso_u8)change_line_attributes  : strFun = "IsoVtcCmd_LineAttributes()"; break;
            case (iso_u8)change_fill_attributes  : strFun = "IsoVtcCmd_FillAttributes()"; break;
            case (iso_u8)change_activ_mask       : strFun = "IsoVtcCmd_ActiveMask()"; break;
            case (iso_u8)change_softkey_mask     : strFun = "IsoVtcCmd_SoftKeyMask()"; break;
            case (iso_u8)change_attribute        : strFun = "IsoVtcCmd_Attribute()"; break;
            case (iso_u8)change_priority         : strFun = "IsoVtcCmd_Priority()"; break;
            case (iso_u8)change_list_item        : strFun = "IsoVtcCmd_ListItem()"; break;
            case (iso_u8)delete_object_pool      : strFun = "IsoVtcCmd_DeleteObjectPool()"; break;
            case (iso_u8)change_string_value     : strFun = "IsoVtcCmd_String()"; break;
            case (iso_u8)change_child_position   : strFun = "IsoVtcCmd_ChildPosition()"; break;
            case (iso_u8)change_object_label     : strFun = "IsoVtcCmd_ChangeObjectLabel()"; break;
            case (iso_u8)change_polygon_point    : strFun = "IsoVtcCmd_ChangePolygonPoint()"; break;
            case (iso_u8)change_polygon_scale    : strFun = "IsoVtcCmd_ChangePolygonScale()"; break;
            case (iso_u8)graphics_context        : strFun = "IsoVtcCmd_GraphicsContext()"; break;
            case (iso_u8)get_attribute_value     : strFun = "IsoVtcCmd_GetAttribute()"; break;
            case (iso_u8)select_colour_map       : strFun = "IsoVtcCmd_SelectColourMap()"; break;
            case (iso_u8)execute_ExtMacro        : strFun = "IsoVtcCmd_ExecuteExtendedMacro()"; break;
            case (iso_u8)lockunlock_mask         : strFun = "IsoVtcCmd_LockUnlockMask()"; break;
            case (iso_u8)execute_Macro           : strFun = "IsoVtcCmd_ExecuteMacro()"; break;
            /* Annex C, D, E, J */
            case (iso_u8)end_of_pool_transfer:     strFun = "IsoVtcMsg_EndofObjectPool()"; break;
            case (iso_u8)get_memory:               strFun = "IsoVtcMsg_GetMemory()"; break;
            case (iso_u8)get_number_softkey:       strFun = "IsoVtcMsg_GetNumberOfSoftkeys()"; break;
            case (iso_u8)get_textfonddata:         strFun = "IsoVtcMsg_GetTextFontData()"; break;
            case (iso_u8)get_hardware:             strFun = "IsoVtcMsg_GetHardware()"; break;
            case (iso_u8)get_supported_widechar:   strFun = "IsoVtcCmd_GetSupportedWidechar()"; break;
            case (iso_u8)get_WM_data:              strFun = "IsoVtcCmd_GetWindowMaskData()"; break;
            case (iso_u8)get_supported_objects:    strFun = "IsoVtcCmd_GetSupportedObjects()"; break;
            case (iso_u8)screen_capture:           strFun = "IsoVtcCmd_ScreenCapture()"; break;
            case (iso_u8)identify_VT:              strFun = "IsoVtcCmd_IdentifyVT()"; break;
            case (iso_u8)get_version:
            case (iso_u8)extended_get_version:     strFun = "IsoVtcMsg_GetVersions()"; break;
            case (iso_u8)load_version:
            case (iso_u8)extended_load_version:    strFun = "IsoVtcMsg_LoadVersion()"; break;
            case (iso_u8)delete_version:
            case (iso_u8)extended_delete_version:  strFun = "IsoVtcCmd_DeleteVersion()"; break;
            case (iso_u8)store_version:
            case (iso_u8)extended_store_version:   strFun = "IsoVtcCmd_StoreVersion()"; break;
            case (iso_u8)preferred_assignment:     strFun = "IsoVtcCmd_PreferredAssignment()"; break;
            default:                               strFun = "Unknown "          ; break;
         }           
#else  /* defined(_LAY6_) */
         strFun = "VtcCmdAdd() ";
#endif /* defined(_LAY6_) */
         break;

      case M_SC:  /* Sequence control client */
         strMod = "IsoSeqC  ";
         strMod = "SeqC     ";
         switch (bFun)
         {
            case ISOSCCtoSCMSEND:             strFun = "IsoSccToScmSend() "; break;    
            case ISOSC_INSTCMD:               strFun = "IsoSC_InstCmd()   "; break;
            case ISOSC_FUNCTIONOBJSET:        strFun = "IsoSC_FunctionObjSet()"; break;
            case ISOSC_FUNCTVALUESET:         strFun = "IsoSC_FunctValueSet()"; break;
            case ISOSC_STATEOBJSET:           strFun = "IsoSC_StateObjSet()"; break;
            case ISOSC_EXECUTIONINDICATION:   strFun = "IsoSC_ExecutionIndication()"; break;
            case ISOSC_EXECUTIONSTATUS:       strFun = "IsoSC_ExecutionStatus()"; break;
            case ISOSC_CLIENTABORT:           strFun = "IsoSC_ClientAbort()"; break;
            case ISOSC_FUNERRORSTATUSSET:     strFun = "IsoSC_FunErrorStatusSet()"; break;
            case ISOSC_FUNTRIGGERSET:         strFun = "IsoSC_FunTriggerSet()"; break;
            case ISOSC_LOGINREC:              strFun = "IsoSccLoginCanRec()"; break;
            case ISOSCDPOOLPREPARE:           strFun = "IsoScdPoolPrepare()"; break;
            case ISOSC_EXTOBJDEFSET:          strFun = "IsoSC_ExternalObjDefSet()"; break;
            case ISOSC_SETVERSION:            strFun = "IsoSC_SetSCCVersion()"; break;
            case ISOSC_INIT:                  strFun = "IsoSCClientInit()  "; break;
            default:                          strFun = "Unknown           "; break;
         }           
         break;

      case M_FSC:   /* File server client */
         strMod = "FSC      ";
         switch (bFun)
         {
            case ISOFSC_FUNCTION            : strFun ="FSC_Function()    "; break;
            case ISOFSC_INIT                : strFun ="iso_fscInit()     "; break;
            case ISOFSC_PROCESSMSG          : strFun ="iso_fscProcessMsg()"; break;
            case ISOFSC_RUN                 : strFun ="iso_fscRun()      "; break;
            case ISOFSC_SEND                : strFun ="FSC_Send()        "; break;
            case ISOFSC_DOCALLBACK          : strFun ="FSC_Do Callback() "; break;
            case ISOFSC_CLOSE_CONNECTION    : strFun ="FSC_CloseConnection()"; break;
            case ISOFSC_CLOSE_IO            : strFun ="FSC_CloseIO()     "; break;
            case ISOFSC_IOMODE_CALLBACK     : strFun ="FSC_IOMode_Cb()   "; break;
            case ISOFSC_FUNCTION_CALL       : strFun ="iso_Fsc...()      "; break;
            default                         : strFun = "Unknown "         ; break;
         }
         break;

      case M_INTERN: /* not used */
         strMod = "unused   ";
         strFun = "         ";
         break;
      case M_APP: /* Application defined */
         strMod = "App      ";
         strFun = "         ";
         break;

      default:  
         strMod = "???????  ";  
         strFun = "???????  ";         
         break;
   }

   switch ( iCause )   
   {                       
      case E_NO_ERR        : strCau = "E_NO_ERR       "; break;  
      case E_UNKNOWN_ERR   : strCau = "E_UNKNOWN_ERR  "; break;  
      case E_WARN          : strCau = "E_WARN         "; break;  
      case E_DEFAULT       : strCau = "E_DEFAULT      "; break;  
      case E_BUSY          : strCau = "E_BUSY         "; break;  
      case E_RANGE         : strCau = "E_RANGE        "; break;  
      case E_OVERFLOW      : strCau = "E_OVERFLOW     "; break;  
      case E_RD_WR         : strCau = "E_RD_WR        "; break;  
      case E_NOACT         : strCau = "E_NOACT        "; break;  
      case E_COM           : strCau = "E_COM          "; break;  
      case E_CONFIG        : strCau = "E_CONFIG       "; break;  
      case E_CHECKSUM      : strCau = "E_CHECKSUM     "; break;  
      case E_ERROR_INDI    : strCau = "E_ERROR_INDI   "; break;  
      case E_NOT_AVAILABLE : strCau = "E_NOT_AVAILABLE"; break;  
      case E_PGN_UNKNOWN   : strCau = "E_PGN_UNKNOWN  "; break;  
      case E_USER_ERROR    : strCau = "E_USER_ERROR   "; break;  
      case E_DATA_LINK     : strCau = "E_DATA_LINK    "; break;  
      case E_NO_INSTANCE   : strCau = "E_NO_INSTANCE  "; break; 
      case E_CANMSG_MISSED : strCau = "E_CANMSG_MISSED"; break; 
      case E_VALUE_WRONG   : strCau = "E_VALUE_WRONG  "; break; 
      case E_OUT_OF_MEMORY : strCau = "E_OUT_OF_MEMORY"; break; 
      case E_NACK          : strCau = "E_NACK         "; break; 
      case E_RESPTOCMDERROR: strCau = "E_RESPTOCMDERROR"; break;
      default              : strCau = "     "          ; break;
   }
    
   iso_DebugPrint("ERROR %3.2d: %-12.17s M0x%2.2X: %-10.14s, F0x%2.2X: %-18.36s Time: %8.4d \n", 
                  iCause, strCau, bLocation, strMod, bFun, strFun, s32TimeMs);

#endif /* defined(ISO_DEBUG_ENABLED) || defined(DOXYGEN) */
} /* EndDoxyErrorOutput */

