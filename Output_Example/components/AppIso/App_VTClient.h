/* ************************************************************************ */
/*!
   \file       AppIso_Impl_VTClient.h

   \brief      Header file for VT client implementation 

   \author     Erwin Hammerl
   \date       Created 15.12.2013 
   \copyright  Wegscheider Hammerl Ingenieure Partnerschaft

   \par HISTORY:

*/
/* ************************************************************************ */

#ifndef __APPISO_VT_H
   #define __APPISO_VT_H
#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */

void    AppVTClientLogin(iso_s16 s16CfHandle);
//void    AppVTClientLogOut(void);

// for key control
iso_s16 VTC_PoolDeleteVersion(void);
iso_s16 VTC_PoolReload(void);
iso_s16 VTC_NextVTButtonPressed(void);
iso_s16 VTC_Restart(void);
iso_s16 VTC_CloseInstance(void);


/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif
#endif /* __APPISO_VT_H */
/* ************************************************************************ */
