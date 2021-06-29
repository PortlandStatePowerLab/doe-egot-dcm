add_subdirectory(https)
add_subdirectory(ecs)
add_subdirectory(command_pattern)
add_subdirectory(dtm_msg_writer)
add_subdirectory(dcm)

set(COMPONENT_NAME dcm_main)

add_executable(${COMPONENT_NAME} 
  main.cpp
)

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  https_client
  SEP::Model
  ecs_client
  command_pattern
  dtm_msg_writer
  SEP::XML
  pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
  ${ecs_INCLUDE_DIRS}
  ${https_client_INCLUDE_DIRS}
  ${SEP_INCLUDES_DIRS}
)