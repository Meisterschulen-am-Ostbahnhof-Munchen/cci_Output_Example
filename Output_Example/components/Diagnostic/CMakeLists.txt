# Edit following two lines to set component requirements (see docs)



set(COMPONENT_SRCS 
  "AppIso_Diagnostic.c"
)

set(COMPONENT_ADD_INCLUDEDIRS 
  "."
)

set(COMPONENT_REQUIRES 
)

set(COMPONENT_PRIV_REQUIRES 
	lib_cci 
	IsoConfig 
	SerialNumber 
	AppIso
)

register_component()


