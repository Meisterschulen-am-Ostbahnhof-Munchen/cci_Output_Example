# Edit following two lines to set component requirements (see docs)



set(COMPONENT_SRCS 
  "AppOutput.c"
  "AppHW.cpp"
  "AppUtil.c"
)

set(COMPONENT_ADD_INCLUDEDIRS 
  "."
  ".."
)

set(COMPONENT_REQUIRES 
)

set(COMPONENT_PRIV_REQUIRES 
	lib_cci 
	Settings 
	IsoConfig
)

register_component()

