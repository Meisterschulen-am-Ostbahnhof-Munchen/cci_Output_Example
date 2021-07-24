/* ************************************************************************ */
#ifndef DEF_APPISO_DIAGNOSTIC_H
#define DEF_APPISO_DIAGNOSTIC_H
/* ************************************************************************ */

#include "IsoCommonDef.h"

/* this enum is application specific and defines the different CF's being used. */
enum CFType
{
    CFTypeIsInvalid = 0,
    CFTypeIsAuxN = 1
};

#ifdef __cplusplus
extern "C" {
#endif

iso_bool processPart12PGN(ISO_TPREP_E eTpRep, const ISO_TPINFO_T* psMsgInfo);

/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif
/* ************************************************************************ */

#endif /* DEF_APPISO_DIAGNOSTIC_H */
/* ************************************************************************ */
