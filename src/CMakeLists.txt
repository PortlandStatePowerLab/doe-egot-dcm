add_subdirectory(https)
add_subdirectory(ecs)

set(COMPONENT_NAME dcm)
add_library(${COMPONENT_NAME} STATIC
    main.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  DCM::https
  SEP::Model
  SEP::XML
  pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
  ${https_INCLUDE_DIRS}
  ${SEP_INCLUDES_DIRS}
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