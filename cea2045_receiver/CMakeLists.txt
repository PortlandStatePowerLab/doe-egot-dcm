
set(COMPONENT_NAME cea2045_receiver)

add_executable(${COMPONENT_NAME} cea2045_rcvr.cpp) 
#re-add https_simple
target_link_libraries(${COMPONENT_NAME} PUBLIC cea2045 Boost::boost OpenSSL::SSL pthread)

target_include_directories(${COMPONENT_NAME} PUBLIC
        ${cea2045_SOURCE_DIR}/cea2045
        ${Boost_INCLUDE_DIRS}
        ${SEP_INCLUDE_DIRS})
