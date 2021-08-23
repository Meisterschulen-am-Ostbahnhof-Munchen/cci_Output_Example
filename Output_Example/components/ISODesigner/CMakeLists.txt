# Edit following two lines to set component requirements (see docs)



set(COMPONENT_SRCS 
	"src"
)

set(COMPONENT_ADD_INCLUDEDIRS 
  "MyWorkspace1/MyProject1/Output/"
)

set(COMPONENT_REQUIRES 
)

set(COMPONENT_PRIV_REQUIRES 
)

register_component()


# After build, copy the iop file to spiffs
add_custom_command(TARGET ${COMPONENT_LIB}
                  POST_BUILD
                  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/components/ISODesigner/MyWorkspace1/MyProject1/Output/MyProject1.iop ${CMAKE_SOURCE_DIR}/spiffs_image/pools
                  COMMENT "Copying MyProject1.iop to spiffs_image...")

# Create a SPIFFS image from the contents of the 'spiffs_image' directory
# that fits the partition named 'storage'. FLASH_IN_PROJECT indicates that
# the generated image should be flashed when the entire project is flashed to
# the target with 'idf.py -p PORT flash'. 
spiffs_create_partition_image(storage ${CMAKE_SOURCE_DIR}/spiffs_image FLASH_IN_PROJECT)

