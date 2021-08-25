/* ************************************************************************ */
/*!
   \file           App_VTClientLev2.h

   \brief          Header file for VT client demo/workshop functions

   \author         Erwin Hammerl
   \date           Created 15.12.2013

   Copyright (c) WBZ-Engineering GmbH

   \par HISTORY:

*/
/* ************************************************************************ */

#ifndef __APPISO_VTLEV2_H
#define __APPISO_VTLEV2_H

#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */


void VTC_setNewVT(const ISOVT_EVENT_DATA_T* psEvData);
void VTC_setPoolReady(const ISOVT_EVENT_DATA_T* psEvData);
void VTC_setPoolManipulation(const ISOVT_EVENT_DATA_T* psEvData);

void VTC_handleSoftkeysAndButtons(const struct ButtonActivation_S *pButtonData);
void VTC_handleAux(const struct AUX_InputSignalData_T *InputSignalData);
void VTC_handleNumericValues(const struct InputNumber_S * pInputNumberData);

void AppVTClientDoProcess(const ISOVT_EVENT_DATA_T* psEvData);

void init_GPIO(void);

extern const int FIRST_AUX;
extern const int  LAST_AUX;


/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif 
#endif /* __APPISO_VTLEV2_H */
/* ************************************************************************ */
