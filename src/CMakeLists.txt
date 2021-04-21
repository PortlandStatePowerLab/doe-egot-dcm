set(COMPONENT_NAME dcm)

add_executable(${COMPONENT_NAME} 
  main.cpp
  https_client.cpp
)

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  Boost::boost
  OpenSSL::SSL
  pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
    ${Boost_INCLUDE_DIRS}
    ${OpenSSL_INCLUDE_DIRS}
)