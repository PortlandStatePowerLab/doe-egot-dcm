add_subdirectory(https)
add_subdirectory(ecs)
add_subdirectory(command_pattern)

set(COMPONENT_NAME dcm)

add_executable(${COMPONENT_NAME} 
  main.cpp
  playground.cpp
)

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  https
  SEP::Model
  ecs
  command_pattern
  SEP::XML
  pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
  ${https_INCLUDE_DIRS}
  ${ecs_INCLUDE_DIRS}
  ${SEP_INCLUDES_DIRS}
)