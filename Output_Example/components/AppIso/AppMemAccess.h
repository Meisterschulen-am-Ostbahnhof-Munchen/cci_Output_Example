/* ************************************************************************ */
/*!
   \file       AppMemAccess.h
   \brief      Header for memory access
   \author     Erwin Hammerl
   \date       Created xx.01.2017

   \copyright  Wegscheider Hammerl Ingenieure Partnerschaft

   \par HISTORY:

*/
/* ************************************************************************ */

#ifndef __APPMEM_H
#define __APPMEM_H

#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */

   iso_s16  getAuxAssignment(const char section[], VT_AUXAPP_T asAuxAss[]);
   void     setAuxAssignment(const char section[], VT_AUXAPP_T asAuxAss[], iso_s16 iNumberOfAssigns);
   void     updateAuxAssignment(const char auxSection[], VT_AUXAPP_T* sAuxAss);

/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* __APPMEM_H */
/* ************************************************************************ */

