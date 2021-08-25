# Edit following two lines to set component requirements (see docs)



set(COMPONENT_SRCS 
  "App_Base.c"
  "App_Main.c"
  "App_VTClient.c"
  "App_TCClient.c"
  "App_VTClientLev2.cpp"
  "AppMemAccess.cpp"
)

set(COMPONENT_ADD_INCLUDEDIRS 
  "."
)


set(COMPONENT_REQUIRES 
)

set(COMPONENT_PRIV_REQUIRES 
	lib_cci 
	IsoConfig 
	ISODesigner 
	Settings 
	AppCommon 
	AppPool
	Diagnostic 
	AppCanDriverEsp32
	Samples
	SerialNumber
	PlcLib
)

register_component()
