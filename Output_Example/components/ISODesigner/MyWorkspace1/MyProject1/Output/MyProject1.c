// ISO-Designer ISO 11783   Version 5.5.1.4367 Jetter AG
// Do not change!

#include "MyProject1.iop.h"
#include "MyProject1.c.h"

#define WORD(w)  (unsigned char)w, (unsigned char)(w >> 8)
#define LONG(l)  (unsigned char)l, \
					(unsigned char)((unsigned long)l >> 8), \
					(unsigned char)((unsigned long)l >> 16), \
					(unsigned char)((unsigned long)l >> 24)
#define ID(id)           WORD(id)
#define REF(id)          WORD(id)
#define XYREF(id, x, y)  WORD(id), WORD(x), WORD(y)
#define MACRO(ev, id)    ev, id
#define COLOR(c)         c

const unsigned char ISO_OP_MEMORY_CLASS isoOP_MyProject1[] = {
	17,
	ID(WorkingSet_0), TYPEID_WORKSET, COLOR(249), 1, ID(DataMask_1000), 1, 0, 2,
		XYREF(Rectangle_14000, 36, 18),
		'e', 'n',
		'd', 'e',
	ID(DataMask_1000), TYPEID_DATAMASK, COLOR(249), ID(ID_NULL), 0, 0, 
	ID(SoftKeyMask_4000), TYPEID_SKEYMASK, COLOR_SILVER, 11, 0, 
		REF(Generated_Pointer_To_Null),
		REF(Generated_Pointer_To_Null),
		REF(Generated_Pointer_To_Null),
		REF(Generated_Pointer_To_Null),
		REF(Generated_Pointer_To_Null),
		REF(Generated_Pointer_To_Null),
		REF(Generated_Pointer_To_Null),
		REF(SoftKey_Q1),
		REF(SoftKey_Q2),
		REF(SoftKey_Q3),
		REF(SoftKey_Q4),
	ID(SoftKey_Q1), TYPEID_SOFTKEY, COLOR(254), 1, 0, 0, 
	ID(SoftKey_Q2), TYPEID_SOFTKEY, COLOR(254), 1, 0, 0, 
	ID(SoftKey_Q3), TYPEID_SOFTKEY, COLOR(254), 1, 0, 0, 
	ID(SoftKey_Q4), TYPEID_SOFTKEY, COLOR(254), 1, 0, 0, 
	ID(Rectangle_14000), TYPEID_OUTRECT, ID(LineAttributes_24000), 
		WORD(54), WORD(18), 0, ID(FillAttributes_25000), 0, 
	ID(LineAttributes_24000), TYPEID_LINEATTR, COLOR_BLACK, 1, WORD(65535), 0, 
	ID(FillAttributes_25000), TYPEID_FILLATTR, 2, COLOR_WHITE, ID(ID_NULL), 0, 
	ID(Generated_Pointer_To_Null), TYPEID_OBJPTR, ID(ID_NULL), 
	ID(AuxFunction2_Q1), TYPEID_AUXFUNC2, COLOR_WHITE, 128, 0, 
	ID(AuxFunction2_Q2), TYPEID_AUXFUNC2, COLOR_WHITE, 128, 0, 
	ID(AuxFunction2_Q3), TYPEID_AUXFUNC2, COLOR_WHITE, 128, 0, 
	ID(AuxFunction2_Q4), TYPEID_AUXFUNC2, COLOR_WHITE, 128, 0, 
}; // isoOP_MyProject1
