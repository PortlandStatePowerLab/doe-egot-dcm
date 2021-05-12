set(COMPONENT_NAME https)

add_library(${PROJECT_NAME}-${COMPONENT_NAME} STATIC
  https_client.cpp
  combined_client.cpp
)

# Create ALIAS targets.
add_library( ${PROJECT_NAME}::${COMPONENT_NAME} ALIAS ${PROJECT_NAME}-${COMPONENT_NAME} )

target_link_libraries(
  ${PROJECT_NAME}-${COMPONENT_NAME} PUBLIC 
  Boost::boost
  OpenSSL::SSL
  pthread
)

target_include_directories(
  ${PROJECT_NAME}-${COMPONENT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${Boost_INCLUDE_DIRS}
  ${OpenSSL_INCLUDE_DIRS}
)

# install the target and create export-set
install(
    EXPORT ${PROJECT_NAME}-${COMPONENT_NAME}Targets
    FILE ${PROJECT_NAME}-${COMPONENT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake
)