/* ************************************************************************ */
/*!
   \file
   \brief       Debug output functions for the driver callbacks. 
   \copyright   Wegscheider Hammerl Ingenieure Partnerschaft

*/
/* ************************************************************************ */
#ifndef DEF_APPISO_OUTPUT_H
    #define DEF_APPISO_OUTPUT_H

#include "IsoCommonDef.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */

/* **************************  defines  *********************************** */

/* **************************  typedef  *********************************** */

/* **************************  function declarations  ********************* */

   /* Single and multi threaded */
   void CbErrorOutp(iso_u8 bFun, iso_u8 bLocation, iso_s16 iCause, iso_s32 s32TimeMs);

/* ************************************************************************ */

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* DEF_APPISO_OUTPUT_H */
/* ************************************************************************ */
