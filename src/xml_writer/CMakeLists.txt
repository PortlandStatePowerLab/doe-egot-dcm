
set(COMPONENT_NAME dtm_xml_writer)

add_executable(${COMPONENT_NAME} main.cpp announce_xml.cpp abstract_command.cpp) 
#re-add https_simple
target_link_libraries(${COMPONENT_NAME} PUBLIC cea2045 Boost::boost OpenSSL::SSL pthread)

target_include_directories(${COMPONENT_NAME} PUBLIC
        ${cea2045_SOURCE_DIR}/cea2045
        ${Boost_INCLUDE_DIRS}
        ${SEP_INCLUDE_DIRS})
