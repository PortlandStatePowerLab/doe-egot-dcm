add_subdirectory(https)
add_subdirectory(ecs)
add_subdirectory(command_pattern)
add_subdirectory(dtm_msg_writer)
add_subdirectory(cta2045_receiver)

set(COMPONENT_NAME dcm)

add_executable(${COMPONENT_NAME} 
  main.cpp
  playground.cpp
)

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  https_client
  SEP::Model
  ecs_client
  command_pattern
  dtm_msg_writer
  cta2045_receiver
  SEP::XML
  pthread
 
)

target_include_directories(${COMPONENT_NAME} PUBLIC
  ${ecs_client_INCLUDE_DIRS}
  ${https_client_INCLUDE_DIRS}
  ${SEP_INCLUDES_DIRS}
  ${command_pattern_INCLUDE_DIRS}
  ${dtm_msg_writer_INCLUDE_DIRS}
  ${cta2045_receiver_INCLUDE_DIRS}
)