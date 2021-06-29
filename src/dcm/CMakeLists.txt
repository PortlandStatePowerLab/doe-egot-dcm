# http://mariobadr.com/creating-a-header-only-library-with-cmake.html
set(COMPONENT_NAME dcm)
add_library(${COMPONENT_NAME} STATIC
    dcm.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_include_directories(
    ${COMPONENT_NAME} STATIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${COMPONENT_NAME} INTERFACE 
    https_client
    SEP::Model
    ecs_client
    command_pattern
    dtm_msg_writer
    SEP::XML
    pthread
)

# install the target and create export-set
install(
    TARGETS ${COMPONENT_NAME}
    EXPORT ${COMPONENT_NAME}Targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(
    EXPORT ${COMPONENT_NAME}Targets
    FILE ${COMPONENT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake
)