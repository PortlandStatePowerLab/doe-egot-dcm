# http://mariobadr.com/creating-a-header-only-library-with-cmake.html
set(COMPONENT_NAME ecs)
add_library(${PROJECT_NAME}-${COMPONENT_NAME} INTERFACE)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${PROJECT_NAME}-${COMPONENT_NAME} )

target_include_directories(
    ${PROJECT_NAME}-${COMPONENT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME}-${COMPONENT_NAME} INTERFACE 
  flecs
  pthread
)

# install the target and create export-set
install(
    EXPORT ${PROJECT_NAME}-${COMPONENT_NAME}Targets
    FILE ${PROJECT_NAME}-${COMPONENT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake
)