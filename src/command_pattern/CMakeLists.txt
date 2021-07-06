set(COMPONENT_NAME command_pattern)

add_library(${COMPONENT_NAME} STATIC
  main.cpp
  cta2045_rcvr.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  Boost::boost
  OpenSSL::SSL
  pthread
  cea2045
  flecs
  https_client
  SEP::XML
  ecs_client
  dtm_msg_writer
)

target_include_directories(${COMPONENT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${cea2045_SOURCE_DIR}/cea2045
  ${Boost_INCLUDE_DIRS}
  ${OpenSSL_INCLUDE_DIRS}
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