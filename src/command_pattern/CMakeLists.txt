set(COMPONENT_NAME command_pattern)

add_library(${COMPONENT_NAME} STATIC
  main.cpp
  cta2045_rcvr.cpp
  UCMImpl.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  cea2045
  Boost::boost
  OpenSSL::SSL
  pthread
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

