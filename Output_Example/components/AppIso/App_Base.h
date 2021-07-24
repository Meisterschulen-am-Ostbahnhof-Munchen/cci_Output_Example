/* ************************************************************************ */
/*!
   \file           
   \brief      Header file for basic test implementation 
  
   \author     Erwin Hammerl
   \date       Created 15.12.2011 
   \copyright  Wegscheider Hammerl Ingenieure Partnerschaft

   \par HISTORY:
*/
/* ************************************************************************ */


#ifndef __APPISO_IMPL_H
   #define __APPISO_IMPL_H

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************ */
/*! 
   \brief  Initialize Demo Application

   - Initialize demo application data
   - Announce user / member
*/
void AppImpl_Ignition(iso_bool qIgnition, iso_u8 funcInstance);


/* ************************************************************************ */
/*!
   \brief  Cyclic function for executing the tests

   - Check for member announced
   - Connect to file server
   - Check the global variable eFscActiveCMD for a test command and execute the test...
*/
void AppImpl_doProcess(void);


/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* __APPISO_IMPL_H */
/* ************************************************************************ */

