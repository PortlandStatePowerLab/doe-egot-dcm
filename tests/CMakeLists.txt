set(COMPONENT_NAME dcm_testing)

add_executable (${COMPONENT_NAME}
    main.cpp
    https_tests.cpp
    ecs_tests.cpp
)

target_link_libraries(${COMPONENT_NAME} 
    gtest 
    gtest_main 
    Boost::boost
    https_client
    ecs_client
    pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${https_client_INCLUDE_DIRS}
    ${ecs_client_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${googletest_INCLUDE_DIRS}
)