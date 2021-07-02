
set(COMPONENT_NAME cta2045_receiver)

add_library(${COMPONENT_NAME} STATIC
  cta2045_rcvr.cpp
)
#re-add https_simple
target_link_libraries(${COMPONENT_NAME} PUBLIC cea2045 command_pattern dtm_msg_writer https_client Boost::boost OpenSSL::SSL pthread)

target_include_directories(${COMPONENT_NAME} PUBLIC
        ${cea2045_SOURCE_DIR}/cea2045
        ${Boost_INCLUDE_DIRS}
        ${SEP_INCLUDE_DIRS}
        ${https_client_INCLUDE_DIRS}
        ${ecs_client_INCLUDE_DIRS}
        ${https_client_INCLUDE_DIRS}
        ${command_pattern_INCLUDE_DIRS})



#this might not work

