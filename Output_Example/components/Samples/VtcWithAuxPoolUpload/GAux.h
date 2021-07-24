#ifndef DEF_GAUX_H
#define DEF_GAUX_H

#include "IsoVtcApi.h"

#if defined(_LAY6_) && defined(ISO_VTC_GRAPHIC_AUX)

// make sure, that the following defines are set in IsoConf.h
// #define ISO_AUX_ENTRIES_MAX 36
// #define ISO_VTC_GRAPHIC_AUX
// #define CCI_CUSTOM_GAUX_VT_STATUS

// for understanding it is suggested to search for
// "IsoVtcGAux_" in the file "GAux.c"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// This function needs to be called after "IsoVtcCreateInstance()"; 
// see \src\Samples\VtcWithAuxPoolUpload\AppImpl_VtcAux.c
void vtcGAux_CfInit(iso_s16 s16CfHandleMaster, const ISO_USER_PARAM_T userParam, const char fileName[]);

// This function needs to be called in "CbVtMessages()"
// at position "case auxiliary_assign_type_2:"
// see \src\Samples\VtcWithAuxPoolUpload\AppImpl_VtcAux.c
void vtcGAux_ForwardAssignment(iso_s16 s16CfHandleMaster, const ISOVT_MSG_STA_T* pVtMsg);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // defined(_LAY6_) && defined(ISO_VTC_GRAPHIC_AUX)
#endif // DEF_GAUX_H
