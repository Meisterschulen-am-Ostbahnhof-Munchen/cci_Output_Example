/* ********************************************************************* */
/*!
   \file

   \brief          ISO Task Controller Client Demo Application

   \author         Erwin Hammerl
   \date           Created 12.11.2007
   \copyright      Wegscheider Hammerl Ingenieure Partnerschaft

   \par
   07.01.2015 - author E. Hammerl
   - More simply TC demo client
   \par
   05.05.2015 - author E. Hammerl
   - Changes in order to pass CT sequences 10-400, 10-500
   \par
   22.07.2016 - author E. Hammerl
   - Added PD for peer control tests
*/
/* ********************************************************************* */

#include "IsoCommonDef.h"
#if defined(_LAY10_) 

#include "IsoClientsApi.h"
#include "IsoTccApi.h"
#include "App_TCClient.h"
#include "DDI.h"
#include "DDIDesignator.h"



iso_u8 u8NumberSectionsImplement = 16u;


// Defines for task controller client
enum AppIso_Impl_TCApp_Object_ID {
	/** \brief
	 Device element Number
	 */
	DE_NUM_DEVICE, // ..
	DE_NUM_CONN, // ..
	DE_NUM_SECTION_001, // ..
	DE_NUM_SECTION_002, // ..
	DE_NUM_SECTION_003, // ..
	DE_NUM_SECTION_004, // ..
	DE_NUM_SECTION_005, // ..
	DE_NUM_SECTION_006, // ..
	DE_NUM_SECTION_007, // ..
	DE_NUM_SECTION_008, // ..
	DE_NUM_SECTION_009, // ..
	DE_NUM_SECTION_010, // ..
	DE_NUM_SECTION_011, // ..
	DE_NUM_SECTION_012, // ..
	DE_NUM_SECTION_013, // ..
	DE_NUM_SECTION_014, // ..
	DE_NUM_SECTION_015, // ..
	DE_NUM_SECTION_016, // ..
	/** \brief
	 Device element Object ID
	 */
	OBJID_DET_DEVICE, // ..
	OBJID_DET_CONN, // ..
	OBJID_DET_SECTION_001, // ..
	OBJID_DET_SECTION_002, // ..
	OBJID_DET_SECTION_003, // ..
	OBJID_DET_SECTION_004, // ..
	OBJID_DET_SECTION_005, // ..
	OBJID_DET_SECTION_006, // ..
	OBJID_DET_SECTION_007, // ..
	OBJID_DET_SECTION_008, // ..
	OBJID_DET_SECTION_009, // ..
	OBJID_DET_SECTION_010, // ..
	OBJID_DET_SECTION_011, // ..
	OBJID_DET_SECTION_012, // ..
	OBJID_DET_SECTION_013, // ..
	OBJID_DET_SECTION_014, // ..
	OBJID_DET_SECTION_015, // ..
	OBJID_DET_SECTION_016, // ..

	/** \brief
	 Device Process Data ObjectID
	 */
	OBJID_DPD_ACTUAL_WORK_STATE,
	OBJID_DPD_MAXIMUM_WORKING_WIDTH,
	OBJID_DPD_ACTUAL_WORKING_WIDTH,
	OBJID_DPD_ACTUAL_WORKING_WIDTH_SECTION,
	OBJID_DPD_OFFSET_X_BOOM,
	OBJID_DPD_OFFSET_Y_BOOM,
	OBJID_DPD_PRESCRIPTION_CONTROL_STATE,
	OBJID_DPD_SECTION_CONTROL_STATE,
	OBJID_DPD_ACTUAL_CONDENSED_WORK_STATE_1_16,
	OBJID_DPD_SETPOINT_CONDENSED_WORK_STATE_1_16,
	OBJID_DPD_OFFSET_X_CONNECTOR,
	OBJID_DPD_OFFSET_Y_CONNECTOR, 
	OBJID_DPD_CONNECTOR_TYPE,

	OBJID_DPD_OFFSET_X_SECTION,
	OBJID_DPD_OFFSET_Y_SECTION_001,
	OBJID_DPD_OFFSET_Y_SECTION_002,
	OBJID_DPD_OFFSET_Y_SECTION_003,
	OBJID_DPD_OFFSET_Y_SECTION_004,
	OBJID_DPD_OFFSET_Y_SECTION_005,
	OBJID_DPD_OFFSET_Y_SECTION_006,
	OBJID_DPD_OFFSET_Y_SECTION_007,
	OBJID_DPD_OFFSET_Y_SECTION_008,
	OBJID_DPD_OFFSET_Y_SECTION_009,
	OBJID_DPD_OFFSET_Y_SECTION_010,
	OBJID_DPD_OFFSET_Y_SECTION_011,
	OBJID_DPD_OFFSET_Y_SECTION_012,
	OBJID_DPD_OFFSET_Y_SECTION_013,
	OBJID_DPD_OFFSET_Y_SECTION_014,
	OBJID_DPD_OFFSET_Y_SECTION_015,
	OBJID_DPD_OFFSET_Y_SECTION_016,

	OBJID_DPD_SETPOINT,
	OBJID_DPD_ACTUAL,
	OBJID_DPD_ACTUAL_CULTURAL_PRACTICE,


	OBJID_DPD_TOTAL_AREA, //DDI 116
	OBJID_DPD_TOTAL_DISTANCE, //DDI 597
	OBJID_DPD_EFFECTIVE_TOTAL_DISTANCE, //DDI 117
	OBJID_DPD_TOTAL_DISTANCE_FIELD, //DDI 599
	OBJID_DPD_INEFFECTIVE_TOTAL_DISTANCE, //DDI 118
	OBJID_DPD_TOTAL_DISTANCE_STREET, //DDI 601
 	OBJID_DPD_EFFECTIVE_TOTAL_TIME, // DDI 119
	OBJID_DPD_INEFFECTIVE_TOTAL_TIME, // DDI 120
	OBJID_DPD_LIFETIME_TOTAL_AREA, // DDI 271
	OBJID_DPD_LIFETIME_TOTAL_DISTANCE, // DDI 598
	OBJID_DPD_LIFETIME_EFFECTIVE_TOTAL_DISTANCE, // DDI 272
	OBJID_DPD_LIFETIME_TOTAL_DISTANCE_FIELD, // DDI 600
	OBJID_DPD_LIFETIME_INEFFECTIVE_TOTAL_DISTANCE, //DDI 273
	OBJID_DPD_LIFETIME_TOTAL_DISTANCE_STREET, //DDI 602
 	OBJID_DPD_LIFETIME_EFFECTIVE_TOTAL_TIME, // DDI 274
	OBJID_DPD_LIFETIME_INEFFECTIVE_TOTAL_TIME, // DDI 275

	/** \brief
	 Device Value Presentation ObjectID
	 */
	OBJID_DVP_ACTUAL_WORK_STATE,
	OBJID_DVP_UNIT_M,
	OBJID_DVP_UNIT_HOUR,
	OBJID_DVP_UNIT_SEC,
	OBJID_DVP_UNIT_HA,
	OBJID_DVP_UNIT_HAUL_COUNTER

};

#define OBJID_DPD_DEFAULT_DDI					59999
#define OBJID_DVP_NO_UNIT						0xFFFF

// Local data and functions
static void  AppTCC_DDOPSet(iso_u8 u8ClNu);
static void  CbTcConnCtrl(const ISO_TCCBCONN_T * psTcCbConn);
static void  CbTcExData(ISO_TCLINK_T*);
static void  AppTCC_ReloadDDOs(iso_u8 u8ClNu);

static iso_u8   u8_TCCHa = TCCLIENT_UNKNOWN;
static iso_s16  s16TCCHandle = HANDLE_UNVALID; /* CF client handle*/
static iso_s16  s16TCHandle = HANDLE_UNVALID;
static iso_u16  u16TCprefBoottime = 10u;   // Boottime for first connecting
static iso_bool qNozzlesWorkState = ISO_FALSE;
static iso_bool qTotalsActive = ISO_FALSE;
static iso_bool qFlagMoveToOtherTC = ISO_FALSE;


iso_s32 PrescriptionControlState = 0;
iso_s32 SectionControlState = 0;
iso_s32 Setpoint = 0;
iso_s32 SetpointCondensedWorkState = 0;
iso_s32 TotalArea = 0;
iso_s32 EffectiveTotalDistance = 0;
iso_s32 IneffectiveTotalDistance = 0;
iso_s32 EffectiveTotalTime = 0;
iso_s32 IneffectiveTotalTime = 0;


/* Structure label and extended structure label */
#ifdef TC_CONTROLSOURCE
static iso_u8 au8StructLabel[] = { '1','y','c','d','e','f','z' };
#else
static iso_u8 au8StructLabel[] = { '1','7','4','5','0','4','!' };
#endif

/* Extended structure label: Bytearray till first '/0' or max. 32 bytes */
static iso_u8 au8ExtStructLabel[] = { "Vers3.45 Facility Tankplus" };  // Auto close with '/0'
/* Default Localisation label  */
static iso_u8 au8LocalLabel[] = { 'e', 'n', 0u, 0u, 0u, 0u, 0xFFu };
/* Actual Language command data -> update Localisation label */
static iso_u8 au8LCDatAct[7] = { 0xFFu, 0xFFu, 0u, 0u, 0u, 0u, 0xFFu };

void AppTCClientLogin(iso_s16 s16CfHandle)
{
   // CF rpabName have to be a Working set master  
   ISO_USER_PARAM_T  userParamDefault = ISO_USER_PARAM_DEFAULT;
   iso_u8 u8ClNum;
   // Open TC client instance
   u8ClNum = IsoTC_InstCmd(s16CfHandle, userParamDefault, CbTcExData, CbTcConnCtrl, IsoTcOpenInst);
   if (u8ClNum != TCCLIENT_UNKNOWN)
   {
      // Set user parameter and additional connection callback function
      // deprecated - IsoTC_InstallCbConnection(u8ClNum, CbTcConnCtrl);

      // TC is selected in event "IsoEvPrefServerNotAvailable" in this sample

      // Storage of handles where the TCC belonged to it
      u8_TCCHa = u8ClNum;
      s16TCCHandle = s16CfHandle;
   }
}


/***************************************************************************/
/*!
   \brief      Releasing TC client shutdown

   This function is called if "Key Switch state not Off" to  "Key Switch state Off"

   \param[in]      \wp{s16CfHandle, iso_s16}
                     CF handle of TC client
*/
void AppTCClientLogOut(iso_s16 s16CfHandle)
{
   ISO_USER_PARAM_T  userParamDefault = ISO_USER_PARAM_DEFAULT;
   iso_u8 u8ClNum;
   u8ClNum = IsoTC_InstCmd(s16CfHandle, userParamDefault, 0, 0, IsoTcGetPointOfInst);
   if (u8ClNum != TCCLIENT_UNKNOWN)
   {
      IsoTC_InstCmd(s16CfHandle, userParamDefault, 0, 0, IsoTcLogOut);  // IsoEvCmdSafeState is called
   }
}


static void AppTCC_DDOPSet(iso_u8 u8ClNu)
{
   static iso_u8 u8PoolStep = 0u; // Test for feature request ID 9304: Wait in Event IsoEvLoadObjects

   if (u8PoolStep == 0u)
   {  /* first test - we wait one cycle */
      IsoTC_TriggerEventAgain(u8ClNu);
      u8PoolStep++;
   }
   else if (u8PoolStep == 1u)
   {  /* second test - we prepare first part */
      iso_u8 * pau8LC;

      IsoTC_TriggerEventAgain(u8ClNu);
      u8PoolStep++;

      /* In case of valid LC data use this as localisation label else default LC */
      if (IsoTC_ReadLCDataofConnection(u8ClNu, au8LCDatAct) == E_NO_ERR)
      {
         pau8LC = au8LCDatAct;
      }
      else
      {
         pau8LC = au8LocalLabel;  // Default LC
      }
      /* else use Default Language command data */

      // The descriptors are not adapted to the used language in this sample !!
      // Take care of order - first DEs then DPDs and DPTs 

      /* rpcDeviceDesignator,       = B
         rpcDeviceSoftwareVersion,  = C
         rpbSerialNumber,           = E
         rpcDeviceStructureLabel,   = F
         rpcDeviceLocalisationLabel = G
         rpcExtendedStructureLabel  = H */
         //                                         B           C       E         
	au8StructLabel[3] = u8NumberSectionsImplement; //This Example uses 16 Sections !
	IsoTC_DeviceExt_Set(u8ClNu, "OutputExample", "EEX", "01",
         au8StructLabel, pau8LC, au8ExtStructLabel);

      /* rwDeviceElementObjectID,   = B
         reDeviceElementType,       = C
         rpcDeviceElementDesignator = D
         rwDeviceElementNumber,     = E
         rwParentObjectID,          = F   */
         //                             B        C        D        E     F    
	IsoTC_DeviceElement_Set(u8ClNu, OBJID_DET_DEVICE, de_device, "OutputExample", DE_NUM_DEVICE, 0u);

	IsoTC_DeviceElement_Set(u8ClNu, OBJID_DET_CONN, de_connector, "Front Connector", DE_NUM_CONN, OBJID_DET_DEVICE);
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_X_CONNECTOR); // Device Element Offset X
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_Y_CONNECTOR); // Device Element Offset Y
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_CONNECTOR_TYPE);
	IsoTC_DeviceElement_End(u8ClNu);

	if (u8NumberSectionsImplement > 1)
	{
		//Sections
		//Section 16:
		IsoTC_DeviceElement_Set(u8ClNu, OBJID_DET_SECTION_016, de_section, "Section 016", DE_NUM_SECTION_016, OBJID_DET_DEVICE);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH_SECTION);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_X_SECTION); // Device Element Offset X
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_016); // Device Element Offset Y
		IsoTC_DeviceElement_End(u8ClNu);
		//Section  15:
		IsoTC_DeviceElement_Set(u8ClNu, OBJID_DET_SECTION_015, de_section, "Section 015", DE_NUM_SECTION_015, OBJID_DET_DEVICE);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH_SECTION);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_X_SECTION); // Device Element Offset X
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_015); // Device Element Offset Y
		IsoTC_DeviceElement_End(u8ClNu);
		//Section  14:
		IsoTC_DeviceElement_Set(u8ClNu, OBJID_DET_SECTION_014, de_section, "Section 014", DE_NUM_SECTION_014, OBJID_DET_DEVICE);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH_SECTION);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_X_SECTION); // Device Element Offset X
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_014); // Device Element Offset Y
		IsoTC_DeviceElement_End(u8ClNu);
		//Section  13:
		IsoTC_DeviceElement_Set(u8ClNu, OBJID_DET_SECTION_013, de_section, "Section 013", DE_NUM_SECTION_013, OBJID_DET_DEVICE);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH_SECTION);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_X_SECTION); // Device Element Offset X
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_013); // Device Element Offset Y
		IsoTC_DeviceElement_End(u8ClNu);
		//Section  12:
		IsoTC_DeviceElement_Set(u8ClNu, OBJID_DET_SECTION_012, de_section, "Section 012", DE_NUM_SECTION_012, OBJID_DET_DEVICE);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH_SECTION);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_X_SECTION); // Device Element Offset X
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_012); // Device Element Offset Y
		IsoTC_DeviceElement_End(u8ClNu);
		//Section  11:
		IsoTC_DeviceElement_Set(u8ClNu, OBJID_DET_SECTION_011, de_section, "Section 011", DE_NUM_SECTION_011, OBJID_DET_DEVICE);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH_SECTION);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_X_SECTION); // Device Element Offset X
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_011); // Device Element Offset Y
		IsoTC_DeviceElement_End(u8ClNu);
		//Section  10:
		IsoTC_DeviceElement_Set(u8ClNu, OBJID_DET_SECTION_010, de_section, "Section 010", DE_NUM_SECTION_010, OBJID_DET_DEVICE);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH_SECTION);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_X_SECTION); // Device Element Offset X
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_010); // Device Element Offset Y
		IsoTC_DeviceElement_End(u8ClNu);
		//Section  9:
		IsoTC_DeviceElement_Set(u8ClNu, OBJID_DET_SECTION_009, de_section, "Section 009", DE_NUM_SECTION_009, OBJID_DET_DEVICE);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH_SECTION);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_X_SECTION); // Device Element Offset X
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_009); // Device Element Offset Y
		IsoTC_DeviceElement_End(u8ClNu);
		//Section  8:
		IsoTC_DeviceElement_Set(u8ClNu, OBJID_DET_SECTION_008, de_section, "Section 008", DE_NUM_SECTION_008, OBJID_DET_DEVICE);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH_SECTION);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_X_SECTION); // Device Element Offset X
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_008); // Device Element Offset Y
		IsoTC_DeviceElement_End(u8ClNu);
		//Section  7:
		IsoTC_DeviceElement_Set(u8ClNu, OBJID_DET_SECTION_007, de_section, "Section 007", DE_NUM_SECTION_007, OBJID_DET_DEVICE);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH_SECTION);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_X_SECTION); // Device Element Offset X
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_007); // Device Element Offset Y
		IsoTC_DeviceElement_End(u8ClNu);
		//Section  6:
		IsoTC_DeviceElement_Set(u8ClNu, OBJID_DET_SECTION_006, de_section, "Section 006", DE_NUM_SECTION_006, OBJID_DET_DEVICE);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH_SECTION);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_X_SECTION); // Device Element Offset X
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_006); // Device Element Offset Y
		IsoTC_DeviceElement_End(u8ClNu);
		//Section  5:
		IsoTC_DeviceElement_Set(u8ClNu, OBJID_DET_SECTION_005, de_section, "Section 005", DE_NUM_SECTION_005, OBJID_DET_DEVICE);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH_SECTION);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_X_SECTION); // Device Element Offset X
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_005); // Device Element Offset Y
		IsoTC_DeviceElement_End(u8ClNu);
		//Section  4:
		IsoTC_DeviceElement_Set(u8ClNu, OBJID_DET_SECTION_004, de_section, "Section 004", DE_NUM_SECTION_004, OBJID_DET_DEVICE);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH_SECTION);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_X_SECTION); // Device Element Offset X
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_004); // Device Element Offset Y
		IsoTC_DeviceElement_End(u8ClNu);
		//Section  3:
		IsoTC_DeviceElement_Set(u8ClNu, OBJID_DET_SECTION_003, de_section, "Section 003", DE_NUM_SECTION_003, OBJID_DET_DEVICE);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH_SECTION);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_X_SECTION); // Device Element Offset X
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_003); // Device Element Offset Y
		IsoTC_DeviceElement_End(u8ClNu);
		//Section  2:
		IsoTC_DeviceElement_Set(u8ClNu, OBJID_DET_SECTION_002, de_section, "Section 002", DE_NUM_SECTION_002, OBJID_DET_DEVICE);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH_SECTION);
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_X_SECTION); // Device Element Offset X
		IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_002); // Device Element Offset Y
		IsoTC_DeviceElement_End(u8ClNu);
		//here we did make Sections 16-15-14 and so on ...
	}

	//this is Section 1. if the Display only can do 1 Section, we can only load 1.
	//TODO. make a logic so the other Sections work virtually.
	//Section  1:
	IsoTC_DeviceElement_Set(u8ClNu, OBJID_DET_SECTION_001, de_section, "Section 001", DE_NUM_SECTION_001, OBJID_DET_DEVICE);
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH_SECTION);
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_X_SECTION); // Device Element Offset X
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_001); // Device Element Offset Y
	IsoTC_DeviceElement_End(u8ClNu);


	// Sections done.


	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_WORK_STATE);
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_CULTURAL_PRACTICE);
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_MAXIMUM_WORKING_WIDTH);
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH);
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_X_BOOM); // Device Element Offset X
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_OFFSET_Y_BOOM); // Device Element Offset Y
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_PRESCRIPTION_CONTROL_STATE);
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_SECTION_CONTROL_STATE);
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL_CONDENSED_WORK_STATE_1_16);
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_SETPOINT_CONDENSED_WORK_STATE_1_16);
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_SETPOINT);
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_ACTUAL);
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_TOTAL_AREA); //DDI 116
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_TOTAL_DISTANCE); //DDI 597
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_EFFECTIVE_TOTAL_DISTANCE); //DDI 117
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_TOTAL_DISTANCE_FIELD); //DDI 599
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_INEFFECTIVE_TOTAL_DISTANCE); //DDI 118
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_TOTAL_DISTANCE_STREET); //DDI 601
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_EFFECTIVE_TOTAL_TIME); // DDI 119
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_INEFFECTIVE_TOTAL_TIME); // DDI 120
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_LIFETIME_TOTAL_AREA); // DDI 271
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_LIFETIME_TOTAL_DISTANCE); // DDI 598
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_LIFETIME_EFFECTIVE_TOTAL_DISTANCE); // DDI 272
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_LIFETIME_TOTAL_DISTANCE_FIELD); // DDI 600
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_LIFETIME_INEFFECTIVE_TOTAL_DISTANCE); //DDI 273
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_LIFETIME_TOTAL_DISTANCE_STREET); //DDI 602
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_LIFETIME_EFFECTIVE_TOTAL_TIME); // DDI 274
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_LIFETIME_INEFFECTIVE_TOTAL_TIME); // DDI 275
	IsoTC_AddDPDObject(u8ClNu, OBJID_DPD_DEFAULT_DDI); // Request for default DDI

      IsoTC_DeviceElement_End(u8ClNu);
   }
   else
   {  /* last test - prepare last part */
      u8PoolStep = 0u; /* Rest counter for next run */

      /* rwProcessDataObjectID,       = A
         rwProcessDataDDI,            = B
         rbProcessDataProperty,       = C  - TC_PROP_DEFAULT_SET, TC_PROP_SETABLE
         rbProcessDataTriggMethods,   = D  - trigger 1=time, 2=distance, 4=threshold, 8=on change, 16=total
         rpcProcessDataDesignator,    = E
         rwDeviceValuePresentObjectID = F   */
	//Device ConnectID
	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_ACTUAL_WORK_STATE, // A
			DDI_ACTUAL_WORK_STATE, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_ACTUAL_WORK_STATE_DESIGNATOR, OBJID_DVP_ACTUAL_WORK_STATE); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_PRESCRIPTION_CONTROL_STATE, // A
			DDI_PRESCRIPTION_CONTROL_STATE, // B
			TC_PROP_DEFAULT_SET | TC_PROP_SETABLE, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_PRESCRIPTION_CONTROL_STATE_DESIGNATOR, OBJID_DVP_NO_UNIT); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_SECTION_CONTROL_STATE, // A
			DDI_SECTION_CONTROL_STATE, // B
			TC_PROP_DEFAULT_SET | TC_PROP_SETABLE, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_SECTION_CONTROL_STATE_DESIGNATOR, OBJID_DVP_NO_UNIT); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_ACTUAL_CONDENSED_WORK_STATE_1_16, // A
			DDI_ACTUAL_CONDENSED_WORK_STATE_1_16, // B
			TC_PROP_DEFAULT_SET | TC_PROP_SETABLE, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_ACTUAL_CONDENSED_WORK_STATE_1_16_DESIGNATOR, OBJID_DVP_NO_UNIT); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_SETPOINT_CONDENSED_WORK_STATE_1_16, // A
			DDI_SETPOINT_CONDENSED_WORK_STATE_1_16, // B
			TC_PROP_DEFAULT_SET | TC_PROP_SETABLE, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_SETPOINT_CONDENSED_WORK_STATE_1_16_DESIGNATOR,
			OBJID_DVP_NO_UNIT); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_TOTAL_AREA, // A //DDI 116
			DDI_TOTAL_AREA, // B
			TC_PROP_DEFAULT_SET | TC_PROP_SETABLE, // C
			TC_TRIG_TOTAL | TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_TOTAL_AREA_DESIGNATOR, OBJID_DVP_UNIT_HA); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_TOTAL_DISTANCE, // A //DDI 597
			DDI_TOTAL_DISTANCE, // B
			TC_PROP_DEFAULT_SET | TC_PROP_SETABLE, // C
			TC_TRIG_TOTAL | TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_TOTAL_DISTANCE_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_EFFECTIVE_TOTAL_DISTANCE, // A  117
			DDI_EFFECTIVE_TOTAL_DISTANCE, // B
			TC_PROP_DEFAULT_SET | TC_PROP_SETABLE, // C
			TC_TRIG_TOTAL | TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_EFFECTIVE_TOTAL_DISTANCE_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_TOTAL_DISTANCE_FIELD, // A  599
			DDI_TOTAL_DISTANCE_FIELD, // B
			TC_PROP_DEFAULT_SET | TC_PROP_SETABLE, // C
			TC_TRIG_TOTAL | TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_TOTAL_DISTANCE_FIELD_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_INEFFECTIVE_TOTAL_DISTANCE, // A  118
			DDI_INEFFECTIVE_TOTAL_DISTANCE, // B
			TC_PROP_DEFAULT_SET | TC_PROP_SETABLE, // C
			TC_TRIG_TOTAL | TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_INEFFECTIVE_TOTAL_DISTANCE_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_TOTAL_DISTANCE_STREET, // A  601
			DDI_TOTAL_DISTANCE_STREET, // B
			TC_PROP_DEFAULT_SET | TC_PROP_SETABLE, // C
			TC_TRIG_TOTAL | TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_TOTAL_DISTANCE_STREET_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_EFFECTIVE_TOTAL_TIME, // A 119
			DDI_EFFECTIVE_TOTAL_TIME, // B
			TC_PROP_DEFAULT_SET | TC_PROP_SETABLE, // C
			TC_TRIG_TOTAL | TC_TRIG_TIMEINTERVAL, // D
			DDI_EFFECTIVE_TOTAL_TIME_DESIGNATOR, OBJID_DVP_UNIT_HOUR); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_INEFFECTIVE_TOTAL_TIME, // A 120
			DDI_INEFFECTIVE_TOTAL_TIME, // B
			TC_PROP_DEFAULT_SET | TC_PROP_SETABLE, // C
			TC_TRIG_TOTAL | TC_TRIG_TIMEINTERVAL, // D
			DDI_INEFFECTIVE_TOTAL_TIME_DESIGNATOR, OBJID_DVP_UNIT_HOUR); // E,  F


	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_LIFETIME_TOTAL_AREA, // A  DDI 271
			DDI_LIFETIME_TOTAL_AREA, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // D
			DDI_LIFETIME_TOTAL_AREA_DESIGNATOR, OBJID_DVP_UNIT_HA); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_LIFETIME_TOTAL_DISTANCE, // A  DDI 598
			DDI_LIFETIME_TOTAL_DISTANCE, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // D
			DDI_LIFETIME_TOTAL_DISTANCE_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F


	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_LIFETIME_EFFECTIVE_TOTAL_DISTANCE, // A // DDI 272
			DDI_LIFETIME_EFFECTIVE_TOTAL_DISTANCE, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // D
			DDI_LIFETIME_EFFECTIVE_TOTAL_DISTANCE_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_LIFETIME_TOTAL_DISTANCE_FIELD, // A // DDI 600
			DDI_LIFETIME_TOTAL_DISTANCE_FIELD, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // D
			DDI_LIFETIME_TOTAL_DISTANCE_FIELD_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_LIFETIME_INEFFECTIVE_TOTAL_DISTANCE, // A // DDI 273
			DDI_LIFETIME_INEFFECTIVE_TOTAL_DISTANCE, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // D
			DDI_LIFETIME_INEFFECTIVE_TOTAL_DISTANCE_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_LIFETIME_TOTAL_DISTANCE_STREET, // A // DDI 602
			DDI_LIFETIME_TOTAL_DISTANCE_STREET, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // D
			DDI_LIFETIME_TOTAL_DISTANCE_STREET_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_LIFETIME_EFFECTIVE_TOTAL_TIME, // A // DDI 274
			DDI_LIFETIME_EFFECTIVE_TOTAL_TIME, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // D
			DDI_LIFETIME_EFFECTIVE_TOTAL_TIME_DESIGNATOR, OBJID_DVP_UNIT_HOUR); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_LIFETIME_INEFFECTIVE_TOTAL_TIME, // A // DDI 275
			DDI_LIFETIME_INEFFECTIVE_TOTAL_TIME, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // D
			DDI_LIFETIME_INEFFECTIVE_TOTAL_TIME_DESIGNATOR, OBJID_DVP_UNIT_HOUR); // E,  F








	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_SETPOINT, // A
			DDI_SETPOINT_VOLUME_PER_AREA_APPLICATION_RATE, // B
			TC_PROP_DEFAULT_SET | TC_PROP_SETABLE, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_SETPOINT_VOLUME_PER_AREA_APPLICATION_RATE_DESIGNATOR, OBJID_DVP_NO_UNIT); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_ACTUAL, // A
			DDI_ACTUAL_VOLUME_PER_AREA_APPLICATION_RATE, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_ACTUAL_VOLUME_PER_AREA_APPLICATION_RATE_DESIGNATOR, OBJID_DVP_NO_UNIT); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_ACTUAL_CULTURAL_PRACTICE, // A
			DDI_ACTUAL_CULTURAL_PRACTICE, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_ACTUAL_CULTURAL_PRACTICE_DESIGNATOR, OBJID_DVP_NO_UNIT); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_X_SECTION, // A
			DDI_DEVICE_ELEMENT_OFFSET_X, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_ACTUAL_TILLAGE_DEPTH_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_001, // A
			DDI_DEVICE_ELEMENT_OFFSET_Y, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_Y_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_002, // A
			DDI_DEVICE_ELEMENT_OFFSET_Y, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_Y_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_003, // A
			DDI_DEVICE_ELEMENT_OFFSET_Y, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_Y_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_004, // A
			DDI_DEVICE_ELEMENT_OFFSET_Y, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_Y_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_005, // A
			DDI_DEVICE_ELEMENT_OFFSET_Y, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_Y_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_006, // A
			DDI_DEVICE_ELEMENT_OFFSET_Y, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_Y_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_007, // A
			DDI_DEVICE_ELEMENT_OFFSET_Y, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_Y_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_008, // A
			DDI_DEVICE_ELEMENT_OFFSET_Y, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_Y_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_009, // A
			DDI_DEVICE_ELEMENT_OFFSET_Y, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_Y_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_010, // A
			DDI_DEVICE_ELEMENT_OFFSET_Y, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_Y_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_011, // A
			DDI_DEVICE_ELEMENT_OFFSET_Y, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_Y_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_012, // A
			DDI_DEVICE_ELEMENT_OFFSET_Y, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_Y_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_013, // A
			DDI_DEVICE_ELEMENT_OFFSET_Y, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_Y_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_014, // A
			DDI_DEVICE_ELEMENT_OFFSET_Y, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_Y_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_015, // A
			DDI_DEVICE_ELEMENT_OFFSET_Y, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_Y_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_Y_SECTION_016, // A
			DDI_DEVICE_ELEMENT_OFFSET_Y, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_Y_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_X_CONNECTOR, // A
			DDI_DEVICE_ELEMENT_OFFSET_X, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_X_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_Y_CONNECTOR, // A
			DDI_DEVICE_ELEMENT_OFFSET_Y, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_Y_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_X_BOOM, // A
			DDI_DEVICE_ELEMENT_OFFSET_X, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_X_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_OFFSET_Y_BOOM, // A
			DDI_DEVICE_ELEMENT_OFFSET_Y, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_DEVICE_ELEMENT_OFFSET_Y_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_MAXIMUM_WORKING_WIDTH, // A
			DDI_MAXIMUM_WORKING_WIDTH, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_MAXIMUM_WORKING_WIDTH_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH, // A
			DDI_ACTUAL_WORKING_WIDTH, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_ACTUAL_WORKING_WIDTH_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_ACTUAL_WORKING_WIDTH_SECTION, // A
			DDI_ACTUAL_WORKING_WIDTH, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_ACTUAL_WORKING_WIDTH_DESIGNATOR, OBJID_DVP_UNIT_M); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_CONNECTOR_TYPE, // A
			DDI_CONNECTOR_TYPE, // B
			TC_PROP_DEFAULT_SET, // C
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // D
			DDI_CONNECTOR_TYPE_DESIGNATOR, OBJID_DVP_NO_UNIT); // E,  F

	IsoTC_DeviceProcessData_Set(u8ClNu, OBJID_DPD_DEFAULT_DDI, // A
			DDI_REQUEST_DEFAULT_PROCESS_DATA, // A,  B Request for default data
			0, // C
			31, // D - all triggermethods see standard
			DDI_REQUEST_DEFAULT_PROCESS_DATA_DESIGNATOR, OBJID_DVP_NO_UNIT); // E,  F

      /* Setting Default trigger - necessary for all belonging to "Member of default set" */
      /* rwProcessDataObjectID
         rbPdDeftTriggMethods
         rlPdDeftValTimeInt
         rlPdDeftValDistanceInt
         rlPdDeftValThreshMini
         rlPdDeftValThreshMaxi
         rlPdDeftValThreshChan   */
	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_ACTUAL_WORK_STATE, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 1L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_SETPOINT, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 1L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_ACTUAL, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 1L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_PRESCRIPTION_CONTROL_STATE, // Object ID
			TC_TRIG_ON_CHANGE, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 3L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_SECTION_CONTROL_STATE, // Object ID
			TC_TRIG_ON_CHANGE, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 3L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_ACTUAL_CONDENSED_WORK_STATE_1_16, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 1L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_SETPOINT_CONDENSED_WORK_STATE_1_16, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_ON_CHANGE, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 1L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_TOTAL_AREA, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 3L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_TOTAL_DISTANCE, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 3L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_EFFECTIVE_TOTAL_DISTANCE, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 3L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_TOTAL_DISTANCE_FIELD, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 3L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_INEFFECTIVE_TOTAL_DISTANCE, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 3L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_TOTAL_DISTANCE_STREET, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 3L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_EFFECTIVE_TOTAL_TIME, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 3L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_INEFFECTIVE_TOTAL_TIME, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 3L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_LIFETIME_TOTAL_AREA, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 3L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_LIFETIME_TOTAL_DISTANCE, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 3L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_LIFETIME_EFFECTIVE_TOTAL_DISTANCE, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 3L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_LIFETIME_TOTAL_DISTANCE_FIELD, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 3L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_LIFETIME_INEFFECTIVE_TOTAL_DISTANCE, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 3L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_LIFETIME_TOTAL_DISTANCE_STREET, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 3L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_LIFETIME_EFFECTIVE_TOTAL_TIME, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 3L); // Values in ms, mm ..

	IsoTC_ProcessDataDefTrigger_Set(u8ClNu, OBJID_DPD_LIFETIME_INEFFECTIVE_TOTAL_TIME, // Object ID
			TC_TRIG_TIMEINTERVAL | TC_TRIG_TOTAL, // Used Triggermethods
			3000L, 1000L, 10L, 60L, 3L); // Values in ms, mm ..



      /* rwDevicePropertyObjectID,    = A
         rwDevicePropertyDDI,         = B
         rlDevicePropertyValue,       = C
         rpcDevicePropertyDesignator, = D
         rwDeviceValuePresentObjectID = E   */
         /*                               A      B               C         D              E         */

      /* rwDeviceValuePresentObjectID, = A
         rlOffset,                     = B
         rfScale,                      = C
         rbNumberOfDecimals,           = D
         rpcUnitDesignator             = E    */
         /*                                A   B         C       D   E         */
	IsoTC_DeviceValuePresent_Set(u8ClNu, OBJID_DVP_ACTUAL_WORK_STATE, 0, (iso_f32) 1, 0, "n.a.");
	IsoTC_DeviceValuePresent_Set(u8ClNu, OBJID_DVP_UNIT_HA, 0, (iso_f32) 0.0001, 2, "ha"); //TODO !
	IsoTC_DeviceValuePresent_Set(u8ClNu, OBJID_DVP_UNIT_HOUR, 0, (iso_f32) 0.00027777777, 2, "h"); //0.00027777777 ist definitiv richtig !
	IsoTC_DeviceValuePresent_Set(u8ClNu, OBJID_DVP_UNIT_SEC, 0, 1, 0, "sec");
	IsoTC_DeviceValuePresent_Set(u8ClNu, OBJID_DVP_UNIT_M, 0, (iso_f32) 0.001, 1, "m");
	IsoTC_DeviceValuePresent_Set(u8ClNu, OBJID_DVP_UNIT_HAUL_COUNTER, 0, (iso_f32) 1, 1, "#");

      // Calling IsoTcClosePool is not necessary anymore - deprecated with driver version 8

   } /* END test steps */

}


/***************************************************************************/
/*!
   \brief       Callback for connection control

   \param[in]      \wp{psTcCbConn, ISO_TCCBCONN_T*}
                     Pointer to TC link struct
*/
static void CbTcConnCtrl(const ISO_TCCBCONN_T * psTcCbConn)
{
   ISO_TCVERS_T sVersDat;
   switch (psTcCbConn->eClEvent)
   {
   case IsoEvPrefServerNotAvailable:
   {
      iso_s16 s16Handles[5], s16Numb = 0, s16I, s16Re;
      ISO_CF_INFO_T sTcInf;
      IsoClientsReadListofExtHandles(task_controller, 5, s16Handles, &s16Numb);
      // If there are TCs available select one
      for (s16I = 0; s16I < s16Numb; s16I++)
      {
         s16Re = IsoCl_GetCfInfo(s16Handles[0], &sTcInf);
         if ((s16Re == E_NO_ERR))
            // && (sTcInf.psName->wManufCode == ...) Select a TC
         {
            IsoTC_SetPrefTC(s16TCCHandle, &sTcInf.au8Name, u16TCprefBoottime);
         }
      }
   }
   break;
   case IsoEvServerVersionAvailable:
      IsoTC_ReadVersionOfServer(psTcCbConn->u8ClNum, &sVersDat);
      /* NAME and boottime should be stored for next session as preferred TC/DL
         - NAME of TC/DL can be determined with IsoTC_Read_TCHandle() and iso_NmGetCfInfo()
         - sVersDat.u8Boottime of TC/DL ( >= version 3 else 0xFF )    */
      s16TCHandle = IsoTC_Read_TCHandle(s16TCCHandle);

		//now Special Case !!!
		//we have a OLD TC Server !


		if (sVersDat.u8NumberSectionsForSC < u8NumberSectionsImplement)
		{
			//now we are in Big Trouble.
			u8NumberSectionsImplement = 1;

		}



		/* Own version message has to be adapted to Server version ( see Standard "connection management" ) */
		if (sVersDat.u8VersionNumber == TC_R2DIS) {
			IsoTC_SetVersionMsg(psTcCbConn->u8ClNum, TC_R2DIS, /* must be 3 here !!! */
			TC_SUPPORT_DOCU | TC_SUPPORT_TC_GEO | TC_SUPPORT_TC_SC,
			TC_SUPPORT_OPT2, 1u, //u8NumberBoomsForSC,
					u8NumberSectionsImplement, //u8NumberSectionsForSC,
					1u //u8NumberControlChannels
					);
		} else if (sVersDat.u8VersionNumber >= TC_R2IS) {
			IsoTC_SetVersionMsg(psTcCbConn->u8ClNum, TC_R2IS,
			TC_SUPPORT_DOCU | TC_SUPPORT_TC_GEO | TC_SUPPORT_TC_SC,
			TC_SUPPORT_OPT2, 1u, //u8NumberBoomsForSC,
					u8NumberSectionsImplement, //u8NumberSectionsForSC,
					1u //u8NumberControlChannels
					);
		} else { /* Version 1 or 2 -> we work with defaults ( Version 2 ) */
		}

      // e. g. sVersDat.u8NumberBoomsForSC for adjusting the client DDOP
      // Note: There is a TC which requests the version after first TC status ( not conform! )
		/* Own version message has to be adapted to Server version ( see Standard "connection management" ) */
		//Store for later usage
      break;
   case IsoEvLanguageCmdReceived:
      if (IsoTC_StatusInfoGet(psTcCbConn->u8ClNum, TCC_STATEOFANNOUNCING) == TcRunning)
      {
         // Language or metrics updated during runtime -> Reload updated objects and descriptors
         // Event during runtime only for version 4 or higher 
         IsoTC_ReloadDDObjects(u8_TCCHa, IsoClType_DontCare);
      }
      break;
   case IsoEvLoadObjects:
      // Driver requests Device description 
      AppTCC_DDOPSet(psTcCbConn->u8ClNum);
      break;
   case IsoEvActivated:
      // TCC/DLC successful logged in
      qNozzlesWorkState = ISO_TRUE;
      qTotalsActive = ISO_FALSE;    // After unexpected shutdown during active task 1
		//TODO // After unexpected shutdown during active task 1

		//IsoCmd_Attribute(EL_TOTALS_TASKCONTROLLER_CONNECTED, AID_OE_FILL_ATT, FillAttributes_GREEN);

      break;
   case IsoEvDeactivated:
      // TCC/DLC successful logged out
      break;
   case IsoEvCmdSafeState:
#ifdef ISO_DEBUG_ENABLED
      iso_DebugPrint("TC - Event: Unexpected shutdown -> Safestate   Time: %8.4d\n", IsoClientsGetTimeMs());
#endif /* ISO_DEBUG_ENABLED */
      // Connection stopped -> Application can react
      // Called if 
      if (qFlagMoveToOtherTC == ISO_FALSE)
      {
         ISO_CF_INFO_T sTCDat;
         IsoCl_GetCfInfo(s16TCHandle, &sTCDat);
         if (sTCDat.bIsActive == ISO_TRUE)
         {
            /* Peercontrolled PD not received
              -> Client will restart because TC status msg is regular received
              -> Application has to log out manual the TC Client
              -> for safety reasons it is recommended to completely log out the implement
            */
            AppTCClientLogOut(s16TCCHandle);  /* only TC Client is logged out here */
         }
         else
         {
            // "Unexpected shutdown" (TC server lost) -> if another TC is available TCC connects automatic !
         }
      }
      else
      {
         // "Move to another TC"  ->  TC clients restarts automatic with new TC/DL
      }
      break;
   case IsoEvTick:
      // Called every cyclic tick after login use for e. g. AppTCClientdoProcess();
      // Test manual sending (with breakpoint): TC2 has same PD !
      // IsoTC_SetDPDValue(psTcCbConn->u8ClNum, 0, 0x77, 345);  
      break;
   case IsoEvLoginAborted:
      break;
   case IsoEvReloadDDOs:
      AppTCC_ReloadDDOs(psTcCbConn->u8ClNum);
      break;
   case IsoEvReloadFinished:
      break;
   default:
      break;
   }
#ifdef ISO_DEBUG_ENABLED
   //AppTCC_LoginStateOutput(psTcCbConn->u8ClNum);
   switch (psTcCbConn->eClEvent)
   {
   case IsoEvServerVersionAvailable:
      iso_DebugPrint("TC - Event: TC Version: %d                    Time: %8.4d\n", sVersDat.u8VersionNumber, IsoClientsGetTimeMs());
      break;
   case IsoEvLanguageCmdReceived:
      iso_DebugPrint("TC - Event: LC available                     Time: %8.4d\n", IsoClientsGetTimeMs());
      break;
   case IsoEvLoadObjects:
      iso_DebugPrint("TC - Event: DD objects are loaded            Time: %8.4d\n", IsoClientsGetTimeMs());
      break;
   case IsoEvActivated:
      iso_DebugPrint("TC - Event: is activated ( TC running )      Time: %8.4d\n", IsoClientsGetTimeMs());
      break;
   case IsoEvDeactivated:
      iso_DebugPrint("TC - Event: is deactivated                   Time: %8.4d\n", IsoClientsGetTimeMs());
      break;
   case IsoEvCmdSafeState:
      break;
   case IsoEvLoginAborted:
      iso_DebugPrint("TC - Event: Uncoverable error during login   Time: %8.4d\n", IsoClientsGetTimeMs());
      break;
   case IsoEvReloadDDOs:
      iso_DebugPrint("TC - Event: Reload started (Changed DDIs)    Time: %8.4d\n", IsoClientsGetTimeMs());
      break;
   case IsoEvReloadFinished:
      iso_DebugPrint("TC - Event: Reload finished (Changed DDIs)   Time: %8.4d\n", IsoClientsGetTimeMs());
      break;
   default: break;
   }
#endif /* ISO_DEBUG_ENABLED */
}


/***************************************************************************/
/*!
   \brief       Application-Interface to the task controller client

   This function is called of the driver if sending a new process data is necessary
   or error codes are reveived.

   \code
   struct _tclink_
   {
       iso_u16        wDDObjID;             Object ID of device description object
       iso_u16        wDevElementNumb;      Requested element number of TC (only process data)
       iso_u16        wDDI;                 Data dictionary identifier (only process data)
       iso_s32       lValueNew;            Depends on ePDCmd:
                                         - IsoValueCommand:        New value for application
                                         - IsoRequestValueCommand: Application must set new value for TC
       ISO_TCAPP_e ePDCmd;               Request value command, value command or Response to command,
                                         IsoTaskStartStop ..
   };
   \endcode
   \param[in]      \wp{psTcLink, ISO_TCLINK_T*}
                     Pointer to TC link struct

   \note  \par
    Following exceptions for data are available: \n
    \code
    ePDCmd = IsoTCVersionReceived ( deprecated - see connection callback )
      - wDDObjID:            Version of TC received of Version message
      - wDevElementNumb:     Boot time of TC in seconds received of Version message
      - wDDI:                Provided options of TC ( Low == Byte4, High == Byte5 )
      - lValueNew:           Number .. ( Low == Byte6, Second = Byte7, Third = Byte8 )
    ePDCmd = IsoTCSizeOfDD
      - lValueNew: Real size of the DD in bytes ( for development )
    ePDCmd = IsoTCPDACKReceived
      - lValueNew:           LSB: PD error code, Second iso_u8: PD command
    \endcode

*/
static void CbTcExData(ISO_TCLINK_T* psTcLink)
{

   iso_bool qDoReport = ISO_TRUE;

   switch (psTcLink->ePDCmd)
   {
   case IsoTCVersionReceived:
      break;
   case IsoTaskStartStop:
      if (psTcLink->lValueNew == 1)
      {
         qTotalsActive = ISO_TRUE;
      }
      else
      {
         qTotalsActive = ISO_FALSE;
      }
      /* Note: Call with Ulrich 15.5.2019 - see 6.8.3.1 - Totals to 0 if paused or stopped - ???*/
      break;
   case IsoRequestValueCommand:
      // Actual values from machine for TC
      // Receiving TC_DDI_REQUEST_DEFAULT_PD is possible too but handling is automated
      // Requests are also reponded if Task is not active
      switch (psTcLink->wDevElementNumb)
      {
		case DE_NUM_DEVICE:
			switch (psTcLink->wDDI) {
			case DDI_ACTUAL_WORK_STATE:
				psTcLink->lValueNew = 1; // Workstate ON!
				break;

			case DDI_TOTAL_AREA: //DDI 116
				psTcLink->lValueNew = TotalArea + 4001;  //1 m� in mm� //TODO implement Hectar Counter !
				break;

			case DDI_TOTAL_DISTANCE: //DDI 597
				psTcLink->lValueNew = 4001; //TODO implement Distance Counter !
				break;

			case DDI_EFFECTIVE_TOTAL_DISTANCE: //DDI 117
				psTcLink->lValueNew =  EffectiveTotalDistance + 4001; //TODO
				break;

			case DDI_TOTAL_DISTANCE_FIELD: //DDI 599
				psTcLink->lValueNew =  4001; //TODO
				break;

			case DDI_INEFFECTIVE_TOTAL_DISTANCE: //DDI 118
				psTcLink->lValueNew =  IneffectiveTotalDistance + 4001; //TODO
				break;

			case DDI_TOTAL_DISTANCE_STREET: //DDI 601
				psTcLink->lValueNew =  4001; //TODO
				break;

			case DDI_EFFECTIVE_TOTAL_TIME: //DDI 119
				// MUST send Time in s here. not in ms. !!! IMPORTANT !!!!
				psTcLink->lValueNew = 4001; //TODO;  //1s in 탎
				break;

			case DDI_INEFFECTIVE_TOTAL_TIME: //DDI 120
				// MUST send Time in s here. not in ms. !!! IMPORTANT !!!!
				psTcLink->lValueNew =  4001; //TODO  //1s in 탎
				break;

			case DDI_PRESCRIPTION_CONTROL_STATE:
				psTcLink->lValueNew = PrescriptionControlState;
				break;

			case DDI_SECTION_CONTROL_STATE:
				psTcLink->lValueNew = SectionControlState;
				break;

			case DDI_ACTUAL_CONDENSED_WORK_STATE_1_16:
				psTcLink->lValueNew = SetpointCondensedWorkState;
				break;

			case DDI_SETPOINT_VOLUME_PER_AREA_APPLICATION_RATE:
				psTcLink->lValueNew = Setpoint;
				break;



			case DDI_LIFETIME_TOTAL_AREA: //DDI 271
				psTcLink->lValueNew = 4001;  //1 m� in mm�
				break;

			case DDI_LIFETIME_TOTAL_DISTANCE: //DDI 598
				psTcLink->lValueNew = 4001; //1m in mm
				break;

			case DDI_LIFETIME_EFFECTIVE_TOTAL_DISTANCE: //DDI 272
				psTcLink->lValueNew = 4001; //TODO
				break;

			case DDI_LIFETIME_TOTAL_DISTANCE_FIELD: //DDI 600
				psTcLink->lValueNew = 4001; //TODO
				break;

			case DDI_LIFETIME_INEFFECTIVE_TOTAL_DISTANCE: //DDI 273
				psTcLink->lValueNew = 4001; //TODO
				break;

			case DDI_LIFETIME_TOTAL_DISTANCE_STREET: //DDI 602
				psTcLink->lValueNew = 4001; //TODO
				break;

			case DDI_LIFETIME_EFFECTIVE_TOTAL_TIME: //DDI 274
				psTcLink->lValueNew =4001; //TODO
				break;

			case DDI_LIFETIME_INEFFECTIVE_TOTAL_TIME: //DDI 275
				psTcLink->lValueNew =   4001; //TODO
				break;

			case DDI_ACTUAL_CULTURAL_PRACTICE:
				psTcLink->lValueNew = 3; //Crop Protection
				break;

			case DDI_ACTUAL_VOLUME_PER_AREA_APPLICATION_RATE:
				psTcLink->lValueNew = Setpoint;
				break;

			case DDI_ACTUAL_WORKING_WIDTH:
				psTcLink->lValueNew = 16 * 500; //16 Sections, 500mm
 				break;

			case DDI_MAXIMUM_WORKING_WIDTH:
				psTcLink->lValueNew = 16 * 500; //16 Sections, 500mm
				break;

			case DDI_DEVICE_ELEMENT_OFFSET_X:
				psTcLink->lValueNew = 0;
				break;

			case DDI_DEVICE_ELEMENT_OFFSET_Y:
				psTcLink->lValueNew = 0;
				break;

			default:
				break;
			}
			break;

		case DE_NUM_CONN:
			switch (psTcLink->wDDI) {
			case DDI_DEVICE_ELEMENT_OFFSET_X:
				psTcLink->lValueNew = 0;
				break;

			case DDI_DEVICE_ELEMENT_OFFSET_Y:
				psTcLink->lValueNew = 0;
				break;

			case DDI_CONNECTOR_TYPE:
				psTcLink->lValueNew = 1; //1 = ISO 6489-3 Tractor drawbar
				break;

			default:
				break;
			}

			break;

		case DE_NUM_SECTION_001:	switch (psTcLink->wDDI) { 	case DDI_DEVICE_ELEMENT_OFFSET_Y:	psTcLink->lValueNew = -3750;	break;	default:	break;	}	break;
		case DE_NUM_SECTION_002:	switch (psTcLink->wDDI) {	case DDI_DEVICE_ELEMENT_OFFSET_Y:	psTcLink->lValueNew = -3250;	break;	default:	break;	}	break;
		case DE_NUM_SECTION_003:	switch (psTcLink->wDDI) {	case DDI_DEVICE_ELEMENT_OFFSET_Y:	psTcLink->lValueNew = -2750;	break;	default:	break;	}	break;
		case DE_NUM_SECTION_004:	switch (psTcLink->wDDI) {	case DDI_DEVICE_ELEMENT_OFFSET_Y:	psTcLink->lValueNew = -2250;	break;	default:	break;	}	break;
		case DE_NUM_SECTION_005:	switch (psTcLink->wDDI) {	case DDI_DEVICE_ELEMENT_OFFSET_Y:	psTcLink->lValueNew = -1750;	break;	default:	break;	}	break;
		case DE_NUM_SECTION_006:	switch (psTcLink->wDDI) {	case DDI_DEVICE_ELEMENT_OFFSET_Y:	psTcLink->lValueNew = -1250;	break;	default:	break;	}	break;
		case DE_NUM_SECTION_007:	switch (psTcLink->wDDI) {	case DDI_DEVICE_ELEMENT_OFFSET_Y:	psTcLink->lValueNew = -750 ;	break;	default:	break;	}	break;
		case DE_NUM_SECTION_008:	switch (psTcLink->wDDI) {	case DDI_DEVICE_ELEMENT_OFFSET_Y:	psTcLink->lValueNew = -250 ;	break;	default:	break;	}	break;
		case DE_NUM_SECTION_009:	switch (psTcLink->wDDI) {	case DDI_DEVICE_ELEMENT_OFFSET_Y:	psTcLink->lValueNew = +250 ;	break;	default:	break;	}	break;
		case DE_NUM_SECTION_010:	switch (psTcLink->wDDI) {	case DDI_DEVICE_ELEMENT_OFFSET_Y:	psTcLink->lValueNew = +750 ;	break;	default:	break;	}	break;
		case DE_NUM_SECTION_011:	switch (psTcLink->wDDI) {	case DDI_DEVICE_ELEMENT_OFFSET_Y:	psTcLink->lValueNew = +1250;	break;	default:	break;	}	break;
		case DE_NUM_SECTION_012:	switch (psTcLink->wDDI) {	case DDI_DEVICE_ELEMENT_OFFSET_Y:	psTcLink->lValueNew = +1750;	break;	default:	break;	}	break;
		case DE_NUM_SECTION_013:	switch (psTcLink->wDDI) {	case DDI_DEVICE_ELEMENT_OFFSET_Y:	psTcLink->lValueNew = +2250;	break;	default:	break;	}	break;
		case DE_NUM_SECTION_014:	switch (psTcLink->wDDI) {	case DDI_DEVICE_ELEMENT_OFFSET_Y:	psTcLink->lValueNew = +2750;	break;	default:	break;	}	break;
		case DE_NUM_SECTION_015:	switch (psTcLink->wDDI) {	case DDI_DEVICE_ELEMENT_OFFSET_Y:	psTcLink->lValueNew = +3250;	break;	default:	break;	}	break;
		case DE_NUM_SECTION_016:	switch (psTcLink->wDDI) {	case DDI_DEVICE_ELEMENT_OFFSET_Y:	psTcLink->lValueNew = +3750;	break;	default:	break;	}	break;

		}
		switch (psTcLink->wDevElementNumb) {

		case DE_NUM_SECTION_001:
		case DE_NUM_SECTION_002:
		case DE_NUM_SECTION_003:
		case DE_NUM_SECTION_004:
		case DE_NUM_SECTION_005:
		case DE_NUM_SECTION_006:
		case DE_NUM_SECTION_007:
		case DE_NUM_SECTION_008:
		case DE_NUM_SECTION_009:
		case DE_NUM_SECTION_010:
		case DE_NUM_SECTION_011:
		case DE_NUM_SECTION_012:
		case DE_NUM_SECTION_013:
		case DE_NUM_SECTION_014:
		case DE_NUM_SECTION_015:
		case DE_NUM_SECTION_016:
			switch (psTcLink->wDDI) {
			case DDI_DEVICE_ELEMENT_OFFSET_X:
				psTcLink->lValueNew = -3000; //TODO !! this is a HACK, remove it !
				break;

			case DDI_ACTUAL_WORKING_WIDTH:
				psTcLink->lValueNew = 500; //500 mm Section with
            break;
         default:
            break;
         }
         break;
      }
      break;
   case IsoValueCommand:
   case IsoValueCommandAcknow:
      // Setpoint values from TC for machine
		switch (psTcLink->wDDObjID) {
		// something to Set on a TC !
		case OBJID_DPD_TOTAL_AREA: //DDI 116
			TotalArea = psTcLink->lValueNew;
			break;


		case OBJID_DPD_EFFECTIVE_TOTAL_DISTANCE:
			EffectiveTotalDistance = psTcLink->lValueNew;
			break;

		case OBJID_DPD_INEFFECTIVE_TOTAL_DISTANCE:
			IneffectiveTotalDistance = psTcLink->lValueNew;
			break;

		case OBJID_DPD_EFFECTIVE_TOTAL_TIME:
			EffectiveTotalTime = psTcLink->lValueNew; //1s in 탎
			break;

		case OBJID_DPD_INEFFECTIVE_TOTAL_TIME:
			IneffectiveTotalTime = psTcLink->lValueNew; //1s in 탎
			break;

		case OBJID_DPD_PRESCRIPTION_CONTROL_STATE:
			PrescriptionControlState = psTcLink->lValueNew;
			break;

		case OBJID_DPD_SECTION_CONTROL_STATE:
			SectionControlState = psTcLink->lValueNew;
			break;

		case OBJID_DPD_SETPOINT_CONDENSED_WORK_STATE_1_16:
			SetpointCondensedWorkState = psTcLink->lValueNew;
			break;

		case OBJID_DPD_SETPOINT:
			Setpoint = psTcLink->lValueNew;
         break;
      default:
         break;
      }
      /* "Set value and acknowledge" use value new as error code for PDACK:
         no_Pd_error, err_PdNotConformDDIDefinition, err_PdOutsideOperationalRange viable
         other error codes are handled intern ! */
      if (psTcLink->ePDCmd == IsoValueCommandAcknow)
      {
         psTcLink->lValueNew = no_Pd_error;
      }
      break; /* End ValueCommand */
   case IsoTCPDACKReceived:
      break;
   default:
      break;
   }
#ifdef ISO_DEBUG_ENABLED
   if (qDoReport == ISO_TRUE)
   {
      switch (psTcLink->ePDCmd)
      {
      case IsoRequestValueCommand:
         iso_DebugTrace("TC ReqCmd ElNr: %4x  DDI: %4x  Wert: %d \n", psTcLink->wDevElementNumb, psTcLink->wDDI, psTcLink->lValueNew);
         break;
      case IsoValueCommand:
         iso_DebugTrace("TC ValCmd ElNr: %4x  DDI: %4x  Wert: %d \n", psTcLink->wDevElementNumb, psTcLink->wDDI, psTcLink->lValueNew);
         break;
      case IsoResponseToCommand:
         iso_DebugTrace("TC-Work - Respo change design  Wert: %d\n", psTcLink->lValueNew); break;
      case IsoTaskStartStop:
         iso_DebugTrace("TC-Work - Task Start/Stop      Wert: %d\n", psTcLink->lValueNew); break;
      case IsoTCSizeOfDD:
         iso_DebugTrace("TC-Work - Size of DD           Wert: %d\n", psTcLink->lValueNew); break;
      case IsoTCVersionReceived:
         iso_DebugTrace("TC-Work - TC Version received  Wert: %d\n", psTcLink->lValueNew); break;
      case IsoTCPDACKReceived:
         iso_DebugTrace("TC-Work - PDACK of TC/DL       Wert: %d\n", psTcLink->lValueNew); break;
      default: break;
      }
   }
#endif 
}



static void AppTCC_ReloadDDOs(iso_u8 u8ClNu)
{
   // Only reloading of DVC- and DVP-objects are allowed
   if (IsoTC_ReadLCDataofConnection(u8ClNu, au8LCDatAct) == E_NO_ERR)
   {
      // Analysing LC or metrics is not implemented in this sample ...
      /* rpcDeviceDesignator,       = B
         rpcDeviceSoftwareVersion,  = C
         rpbSerialNumber,           = E
         rpcDeviceStructureLabel,   = F
         rpcDeviceLocalisationLabel = G */
         //                           B           C       E      F            G    
		IsoTC_DeviceExt_Set(u8ClNu, "OutputExample", "EEX", "01", au8StructLabel, au8LCDatAct, au8ExtStructLabel);

      /* rwDeviceValuePresentObjectID, = A
         rlOffset,                     = B
         rfScale,                      = C
         rbNumberOfDecimals,           = D
         rpcUnitDesignator             = E    */
         //                                    A    B         C        D        E         
   }
}


void AppTCC_MoveToAnotherTC()
{
   iso_s16 s16TCHandleCurrent = HANDLE_UNVALID;
   iso_s16 s16Handles[5], sNumb = 0;
   iso_u8  u8I;
   ISO_CF_INFO_T sTCServDat;

   s16TCHandleCurrent = IsoTC_Read_TCHandle(s16TCCHandle);
   IsoClientsReadListofExtHandles(task_controller, 5, s16Handles, &sNumb);
   for (u8I = 0; u8I < sNumb; u8I++)
   {
      if (s16Handles[u8I] != s16TCHandleCurrent)
      {
         IsoCl_GetCfInfo(s16Handles[u8I], &sTCServDat);
         /* Connect with another TC */
         IsoTC_MoveToAnotherTCoDL(u8_TCCHa, &sTCServDat.au8Name, 5);
         qFlagMoveToOtherTC = ISO_TRUE;
      }
   }
}

void AppFertilizer_Workstate_ONOFF()
{
   qNozzlesWorkState = (qNozzlesWorkState == ISO_FALSE) ? ISO_TRUE : ISO_FALSE;
}

#endif /* defined(_LAY10_) */
