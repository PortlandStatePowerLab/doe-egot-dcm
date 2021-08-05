set(COMPONENT_NAME cta2045_receiver)

add_library(${COMPONENT_NAME} STATIC
  cta2045_receiver.cpp
  ecs_epri_ucm_impl.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME} )

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  Boost::boost
  OpenSSL::SSL
  dtm_msg_writer
  command_pattern
  pthread
  cea2045
)

target_include_directories(${COMPONENT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${Boost_INCLUDE_DIRS}
  ${OpenSSL_INCLUDE_DIRS}
  ${cea2045_SOURCE_DIR}/cea2045
  ${command_pattern_INCLUDE_DIRS}
)