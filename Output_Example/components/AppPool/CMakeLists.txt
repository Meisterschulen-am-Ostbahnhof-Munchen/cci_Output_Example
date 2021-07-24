# Edit following two lines to set component requirements (see docs)



set(COMPONENT_SRCS 
  "AppPool.cpp"

)

set(COMPONENT_ADD_INCLUDEDIRS 
  "."
  ".."
)


set(COMPONENT_REQUIRES 
)

set(COMPONENT_PRIV_REQUIRES 
	lib_cci 
	IsoConfig 
	AppCommon
	spiffs
)

register_component()
