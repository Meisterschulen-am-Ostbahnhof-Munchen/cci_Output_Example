# Edit following two lines to set component requirements (see docs)



set(COMPONENT_SRCS 
  "CanDriverEsp32.cpp"
)

set(COMPONENT_ADD_INCLUDEDIRS 
  "."
)

set(COMPONENT_REQUIRES 
)

set(COMPONENT_PRIV_REQUIRES 
	AppCommon 
	lib_cci 
	IsoConfig
)

register_component()
