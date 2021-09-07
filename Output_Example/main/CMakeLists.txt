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



set(src_file ${CMAKE_SOURCE_DIR}/components/ISODesigner/MyWorkspace1/MyProject1/Output/MyProject1.iop)
set(dst_file ${CMAKE_SOURCE_DIR}/spiffs_image/pools/MyProject1.iop)

# After build, copy the archive file and header file to parent example directory's main component
add_custom_command(OUTPUT ${dst_file}
                  COMMAND ${CMAKE_COMMAND} -E echo "Copying spiffsgen_example_main.c to spiffs_image..."
                  COMMAND ${CMAKE_COMMAND} -E copy ${src_file} ${dst_file}
                  DEPENDS ${src_file})
                  
                  
                  
add_custom_target(update_spiffs DEPENDS "${dst_file}")
  
# Create a SPIFFS image from the contents of the 'spiffs_image' directory
# that fits the partition named 'storage'. FLASH_IN_PROJECT indicates that
# the generated image should be flashed when the entire project is flashed to
# the target with 'idf.py -p PORT flash'. 
spiffs_create_partition_image(storage ../spiffs_image FLASH_IN_PROJECT DEPENDS update_spiffs)

