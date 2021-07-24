
#ifndef VIEngine_h__
#define VIEngine_h__



/* Various shorthand strucths to improve readability and maintainability
 * they are copies of ISOVT_MSG_STA_T
 * iso_s16          iVtFunction;       VT function of received message (#ISOVT_FUNC_e)
 * iso_u16          wObjectID;         Object ID (if available)
 * iso_u32          lValue;            Long value depending of command/activation message see table
 * iso_u16          wPara1;            Unsigned short value 1 depending of command/activation message see table
 * iso_u16          wPara2;            Unsigned short value 2 depending of command/activation message see table
 * iso_u8           bPara;             Unsigned char value depending of command/activation message see table
 * iso_u8           u8Instance;        Identifier of the client instance
 * iso_s16          iErrorCode;        Error code of response messages or error code e. g. #E_CANMSG_MISSED
 * iso_s32          lTimeSt;           Time stamp of received message
 * const iso_u8*    pabVtData;         Data of VT e. g. string characters see table
 * ISO_USER_PARAM_T userParam;         User parameter set with IsoVT_CreateInstance()
 */




/*
 *
 *     softkey_activation
 *     		wObjectID       key object ID
 *     		wPara1          parent object ID
 *     		bPara           key number (hard coded)
 *     		lValue          activation code (0, 1, 2, 3(Version 4)) see [1]
 *
 */

// SOFT KEY ACTIVATION (Response == Request)
struct SoftKeyActivation_S
{
    iso_s16          iVtFunction;                           /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          objectIdOfKeyObject;                   /**< \brief key object ID */
    iso_u32          keyActivationCode;                     /**< \brief activation code (0, 1, 2, 3(Version 4)) see [1] */
    iso_u16          objectIdOfVisibleParentDataOrAlarmMask;/**< \brief parent object ID */
    iso_u16          wPara2;                                /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           softKeyCode;                           /**< \brief key number (hard coded) */
    iso_u8           u8Instance;                            /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;                            /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;                               /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;                             /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;                             /**< \brief User parameter set with IsoVT_CreateInstance() */
};

/*
 *
 *     button_activation
 *     		wObjectID       button object ID
 *     		wPara1          parent object ID
 *     		bPara           button key number
 *     		lValue          activation code (0, 1, 2, 3(Version 4)) see [1]
 *
 */

// BUTTON ACTIVATION (Response == Request)
struct ButtonActivation_S
{
    iso_s16          iVtFunction;                           /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          objectIdOfButtonObject;                /**< \brief button object ID */
    iso_u32          keyActivationCode;                     /**< \brief activation code (0, 1, 2, 3(Version 4)) see [1] */
    iso_u16          objectIdOfParentDataMask;              /**< \brief parent object ID */
    iso_u16          wPara2;                                /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           buttonKeyCode;                         /**< \brief button key number */
    iso_u8           u8Instance;                            /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;                            /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;                               /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;                             /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;                             /**< \brief User parameter set with IsoVT_CreateInstance() */
};

/*
 *
 *     VT_change_numeric_value
 *     		wObjectID       ID of input object
 *     		lValue          new value
 *
 */

// Input Number
struct InputNumber_S
{
    iso_s16          iVtFunction;                           /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          objectIdOfInputNumber;                 /**< \brief ID of input object */
    iso_u32          newValue;                              /**< \brief new value */
    iso_u16          wPara1;                                /**< \brief Unsigned short value 1 depending of command/activation message see table */
    iso_u16          wPara2;                                /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           bPara;                                 /**< \brief Unsigned char value depending of command/activation message see table */
    iso_u8           u8Instance;                            /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;                            /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;                               /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;                             /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;                             /**< \brief User parameter set with IsoVT_CreateInstance() */
};


/*
 *
 *     VT_change_string_value
 *     		wObjectID       ID of String object
 *     		bPara           Length of string
 *     		pabVtData       Pointer to characters
 *
 */

struct InputString_S
{
    iso_s16          iVtFunction;                           /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          objectIdOfInputString;                 /**< \brief ID of String object */
    iso_u32          lValue;                                /**< \brief Long value depending of command/activation message see table */
    iso_u16          wPara1;                                /**< \brief Unsigned short value 1 depending of command/activation message see table */
    iso_u16          wPara2;                                /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           numberOfBytes;                         /**< \brief Length of string */
    iso_u8           u8Instance;                            /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;                            /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;                               /**< \brief Time stamp of received message */
    const iso_u8*    newStringValue;                        /**< \brief Pointer to characters */
    ISO_USER_PARAM_T userParam;                             /**< \brief User parameter set with IsoVT_CreateInstance() */
};


enum Button_States_E
{
	BUTTON_STATE_RELEASED,
	BUTTON_STATE_PRESSED,
	BUTTON_STATE_HELD,
	BUTTON_STATE_ABORTED
};



enum AUX_PRESS_E {

	AUX_PRESS_OFF = 0, //0 = Off = backward, down, left, or not pressed
	AUX_PRESS_MOMENTARY = 1,//1 = Momentary = forward, up, right, or pressed
	AUX_PRESS_HELD = 2//2 = held
};



#define	AUX_DOWN_FLOAT  0xFAFF
#define	AUX_DOWN  		0xFAFE
#define	AUX_MIDDLE  	0x7D7F
#define	AUX_UP  		0x0



/* AUX input signal activation callback notification struct */
struct AUX_InputSignalData_T
{
	iso_s16    iVtFunction;       /**< Last function of VT response (#ISOVT_FUNC_e) */
	iso_u16    objectIdOfAuxObject;
	iso_s32    value1;            /**< Value of VT change numeric value */
	iso_u16    inputObjectID;            /**< Word storage 1 */
	iso_u16    value2;            /**< Word storage 2 */
	iso_u8     bPara;             /**< Byte storage i. e. soft key number */
    iso_u8     u8Instance;                            /**< \brief Identifier of the client instance */
	iso_s16    iErrorCode;        /**< Error iso_u8 of response messages */

};

enum VT_line_width
{
	Line_Width_0,
	Line_Width_1,
	Line_Width_2,
	Line_Width_3,
};

enum
{
	Null_Language,
	German,
	English,
	Czech,	
	French,		
	Hungarian,	
	Italian,	
	Polish,	
	Portuguese,	
	Russian,	
	Spanish,
	Swedish,
	Bulgarian,
	Dutch

};

#endif // VIEngine_h__
