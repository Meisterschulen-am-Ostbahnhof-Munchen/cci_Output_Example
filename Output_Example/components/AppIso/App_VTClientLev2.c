/* ************************************************************************ */
/*!
   \file

   \brief          VT client demo application

   \author         Erwin Hammerl
   \date           Created 17.09.2007

   \copyright  Wegscheider Hammerl Ingenieure Partnerschaft

   \par HISTORY:

*/
/* **************************  includes ********************************** */

#include "IsoDef.h"

#ifdef _LAY6_  /* compile only if VT client is enabled */


#include "VIEngine.h"
#include "App_VTClientLev2.h"   // -> Object defines

#include "MyProject1.iop.h"
#include "MyProject1.c.h"

#include "settings.h"

#include "esp_log.h"

static const char *TAG = "App_VTClientLev2";

#include "driver/gpio.h"


//********************************************************************************************
// Each command has several Unique Features. here they are encapsulated !
//********************************************************************************************
typedef struct {
	//
	//! The Commandnumber is here redundant, however a Testdriver can check for Validity !!!
	//
	iso_u16 objectIdOfAuxObject; // objectIdOfAuxObject
	iso_u16 objectIdOfButtonObject; // objectIdOfButtonObject

} CommandTranslateObject;

CommandTranslateObject CommandTranslate[] = {
	{ AuxFunction2_Q1,		SoftKey_Q1		}, //	0
	{ AuxFunction2_Q2,		SoftKey_Q2		}, //	1
	{ AuxFunction2_Q3,		SoftKey_Q3		}, //	2
	{ AuxFunction2_Q4,		SoftKey_Q4		} //	3
};


//make this Defines (Right side)
const int FIRST_AUX = AuxFunction2_Q1;
const int  LAST_AUX = AuxFunction2_Q4;
//do not Change this.
const int  NUM_AUX_FUNCTIONS = ((LAST_AUX-FIRST_AUX)+1);
iso_s32 InputSignalData_old_value1[20] = {AUX_PRESS_OFF};



// called from AppPoolSettings()
void VTC_setPoolManipulation(const ISOVT_EVENT_DATA_T* psEvData)
{
   iso_u16  u16DM_Scal  = 10000u;          // Scaling factor * 10000
   iso_u16  u16SKM_Scal = 10000u;

   // ------------------------------------------------------------------------------

   // IsoVtcPoolSetIDRangeMode(u8Instance, 0, 60000, 10000, NoScaling);          // Switch off automatic scaling

   u16DM_Scal = (iso_u16)IsoVtcPoolReadInfo(psEvData->u8Instance, PoolDataMaskScalFaktor);       // Call only after PoolInit !!
   u16SKM_Scal = (iso_u16)IsoVtcPoolReadInfo(psEvData->u8Instance, PoolSoftKeyMaskScalFaktor);

   IsoVtcPoolSetIDRangeMode(psEvData->u8Instance, 5100u, 5300u, u16SKM_Scal, Centering);       // Scale and center Keys
   IsoVtcPoolSetIDRangeMode(psEvData->u8Instance, 20700u, 20799u, u16SKM_Scal, Scaling);         // Scale Pictures in keys


   // ------------------------------------------------------------------------------


   IsoVtcPoolSetIDRangeMode(psEvData->u8Instance, 0u,     0u, u16SKM_Scal, Centering);  // Working set object
   IsoVtcPoolSetIDRangeMode(psEvData->u8Instance, 20000u, 20000u, u16SKM_Scal, Scaling);    // Working set designator
   IsoVtcPoolSetIDRangeMode(psEvData->u8Instance, 29000u, 29099u, u16SKM_Scal, Centering);  // Auxiliary function
   IsoVtcPoolSetIDRangeMode(psEvData->u8Instance, 20900u, 20999u, u16SKM_Scal, Scaling);    // Auxiliary bitmaps
   (void)u16DM_Scal;


	if (IsoVtcGetStatusInfo(psEvData->u8Instance, VT_VERSIONNR) == VT_V2_FE)
	{
		// Transforming Auxiliary function Type 2 into Type 1
		IsoVtcPoolSetIDRangeMode(psEvData->u8Instance, 29000, 29999, 0, AuxToV2);
	}
}














void VTC_handleNumericValues(const struct InputNumber_S * pInputNumberData) {
	// what number was entered
	switch (pInputNumberData->objectIdOfInputNumber) {



	default:
		break;
	}

}


void VTC_setNewVT(const ISOVT_EVENT_DATA_T* psEvData)
{
   // ------------------------------------------------------------------------------

   PARAM_UNUSED(psEvData->u8Instance);


   // ------------------------------------------------------------------------------
}

void VTC_setPoolReady(const ISOVT_EVENT_DATA_T* psEvData)
{

	// beim nächsten Anstecken des Gerätes muss der letzte gespeicherte Wert auf das Display gesendet werden.

}

#define GPIO_Q1 GPIO_NUM_19
#define GPIO_Q2 GPIO_NUM_23
#define GPIO_Q3 GPIO_NUM_33
#define GPIO_Q4 GPIO_NUM_25


void init_GPIO(void)
{
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    gpio_reset_pin(GPIO_Q1);
    gpio_reset_pin(GPIO_Q2);
    gpio_reset_pin(GPIO_Q3);
    gpio_reset_pin(GPIO_Q4);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(GPIO_Q1, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_Q2, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_Q3, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_Q4, GPIO_MODE_OUTPUT);

    gpio_set_level(GPIO_Q1, 0);
    gpio_set_level(GPIO_Q2, 0);
    gpio_set_level(GPIO_Q3, 0);
    gpio_set_level(GPIO_Q4, 0);
}


void VTC_handleSoftkeysAndButton_Q1(const struct ButtonActivation_S *pButtonData) {

	switch (pButtonData->keyActivationCode) {


	case BUTTON_STATE_PRESSED:
	case BUTTON_STATE_HELD:
		gpio_set_level(GPIO_Q1, 1);
		break;


	case BUTTON_STATE_RELEASED:
	case BUTTON_STATE_ABORTED:
		gpio_set_level(GPIO_Q1, 0);
		break;


	}
}

void VTC_handleSoftkeysAndButton_Q2(const struct ButtonActivation_S *pButtonData) {

	switch (pButtonData->keyActivationCode) {


	case BUTTON_STATE_PRESSED:
	case BUTTON_STATE_HELD:
		gpio_set_level(GPIO_Q2, 1);
		break;


	case BUTTON_STATE_RELEASED:
	case BUTTON_STATE_ABORTED:
		gpio_set_level(GPIO_Q2, 0);
		break;


	}
}

void VTC_handleSoftkeysAndButton_Q3(const struct ButtonActivation_S *pButtonData) {

	switch (pButtonData->keyActivationCode) {


	case BUTTON_STATE_PRESSED:
	case BUTTON_STATE_HELD:
		gpio_set_level(GPIO_Q3, 1);
		break;


	case BUTTON_STATE_RELEASED:
	case BUTTON_STATE_ABORTED:
		gpio_set_level(GPIO_Q3, 0);
		break;


	}
}

void VTC_handleSoftkeysAndButton_Q4(const struct ButtonActivation_S *pButtonData) {

	switch (pButtonData->keyActivationCode) {


	case BUTTON_STATE_PRESSED:
	case BUTTON_STATE_HELD:
		gpio_set_level(GPIO_Q4, 1);
		break;


	case BUTTON_STATE_RELEASED:
	case BUTTON_STATE_ABORTED:
		gpio_set_level(GPIO_Q4, 0);
		break;


	}
}



void VTC_handleSoftkeysAndButtons(const struct ButtonActivation_S *pButtonData)
{

	ESP_LOGI(TAG, "press");

	// what button was operated
	switch (pButtonData->objectIdOfButtonObject) {
	case SoftKey_Q1:
		VTC_handleSoftkeysAndButton_Q1(pButtonData);
		break;
	case SoftKey_Q2:
		VTC_handleSoftkeysAndButton_Q2(pButtonData);
		break;
	case SoftKey_Q3:
		VTC_handleSoftkeysAndButton_Q3(pButtonData);
		break;
	case SoftKey_Q4:
		VTC_handleSoftkeysAndButton_Q4(pButtonData);
		break;
	}

}

void VTC_handleAux(const struct AUX_InputSignalData_T *InputSignalData) {
	struct ButtonActivation_S pButtonData;


	// Application may decide to lookup the object ID of the function assigned to this input
	// and then check the status data reported...
	//functionObjID = <maybe you have a lookup to get function object Id from (InputSignalData.inputObjectID)>;

	// Store the sprintf format string in HUGE ROM.
	//static SprinthfFormatChar_T format[] = "Pressed = %s, Status= %i\n";


	if (InputSignalData->objectIdOfAuxObject < FIRST_AUX)
	{
		return;
	}



	pButtonData.objectIdOfButtonObject = CommandTranslate[InputSignalData->objectIdOfAuxObject - FIRST_AUX].objectIdOfButtonObject;
	pButtonData.wPara2 = (iso_u16)InputSignalData->value1;
	pButtonData.u8Instance = InputSignalData->u8Instance;

	switch (InputSignalData->value1) {
	case AUX_PRESS_OFF:
		switch (InputSignalData_old_value1[InputSignalData->objectIdOfAuxObject - FIRST_AUX]) {
		case AUX_PRESS_OFF:
			//NOOP!
			break;
		default:
			pButtonData.keyActivationCode = BUTTON_STATE_RELEASED;
			VTC_handleSoftkeysAndButtons(&pButtonData);
			break;
		}
		break;
	case AUX_PRESS_MOMENTARY:
		pButtonData.keyActivationCode = BUTTON_STATE_PRESSED;
		VTC_handleSoftkeysAndButtons(&pButtonData);
		break;
	case AUX_PRESS_HELD:
		switch (InputSignalData_old_value1[InputSignalData->objectIdOfAuxObject - FIRST_AUX]) {
		case AUX_PRESS_OFF:
			pButtonData.keyActivationCode = BUTTON_STATE_PRESSED;
			VTC_handleSoftkeysAndButtons(&pButtonData);
			break;
		default:
			pButtonData.keyActivationCode = BUTTON_STATE_HELD;
			VTC_handleSoftkeysAndButtons(&pButtonData);
			break;
		}
		break;
	default:
		break;

	}

	InputSignalData_old_value1[InputSignalData->objectIdOfAuxObject - FIRST_AUX] = InputSignalData->value1;
}



/* ************************************************************************ */
#endif /* _LAY6_ */
/* ************************************************************************ */
