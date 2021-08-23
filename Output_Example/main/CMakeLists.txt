# Edit following two lines to set component requirements (see docs)

set(COMPONENT_REQUIRES 
)

set(COMPONENT_PRIV_REQUIRES 
)

set(COMPONENT_SRCS 
  "main.c"
)

set(COMPONENT_ADD_INCLUDEDIRS 
  "."
)


register_component()

  



# Import the library, specifying a target name and the library path.
# The private dependencies of the library is also specified.
add_prebuilt_library(libcci_ecu_driver "../components/lib_cci/libcci_ecu_driver.a")

# `main` calls a function from the library, so link it to `main`
target_link_libraries(${COMPONENT_LIB} PRIVATE libcci_ecu_driver)



