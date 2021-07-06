#include <iostream>
#include <string>
#include <sstream>
#include <https/https_client.hpp>
#include <https/combined_client.hpp>
#include <sep/models.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <ecs/sim_module.hpp>
#include <ecs/der_simulator.hpp>
#include <command_pattern/ecs_dcm.hpp>

INITIALIZE_EASYLOGGINGPP //this is needed for part of the cea2045 deps

void GetParentPath(char** arg)
{
    g_program_path = arg[0];
    std::size_t found = g_program_path.find_last_of("/\\");
    g_program_path = g_program_path.substr(0,found);
}; 
void SimulateDCMSystem()
{
  std::cout << "Now simulating dcm system" << std::endl;
  dcm::ECS_DCM dcm(g_program_path);
  dcm.TestCTA2045Commands();
  //dcm.RunSimulatorLoop();

}
void SimulateDER()
{
    std::cout << "playground simulate DER function " << std::endl;
    der::DERSimulator simulated_der;

    simulated_der.TestRun();
    
}
void RunHttpsTests()
{
  std::cout << " RunHttpsTests() " << std::endl;
  //HttpsClient client(g_program_path, "host.docker.internal", "8886");
  CombinedHttpsClient combined_client(g_program_path, "0.0.0.0", 
                                      "443", g_program_path, "0.0.0.0",
                                      "4430");
/*
  std::cout << client.Get("/dcap") << std::endl;
  std::cout << client.Get("/tm") << std::endl;
  std::cout << client.Get("/edev") << std::endl;
  
std::string freq = R"(<?xml version="1.0" encoding="utf-8"?>
<FlowReservationRequest href="http://uri1" xmlns="urn:ieee:std:2030.5:ns">
  <mRID>0FB7</mRID>
  <description>description1</description>
  <version>0</version>
  <creationTime>1</creationTime>
  <durationRequested>0</durationRequested>
  <energyRequested>
    <multiplier>1</multiplier>
    <value>-140737488355328</value>
  </energyRequested>
  <intervalRequested>
    <duration>0</duration>
    <start>1</start>
  </intervalRequested>
  <powerRequested>
    <multiplier>1</multiplier>
    <value>1</value>
  </powerRequested>
  <RequestStatus>
    <dateTime>1</dateTime>
    <requestStatus>0</requestStatus>
  </RequestStatus>
</FlowReservationRequest>)";
*/
  std::string test_dtm_msg = R"(    <message>
        <from>DCM</from>
        <to>DER</to>
        <content>
            <command>
                <type>SHED</type>
                <start>1617498512</start>
                <duration>3.1415</duration>
            </command>
            <expect_response>1</expect_response>
        </content>
        <logged>1617498512</logged>
    </message>)";
   //auto thing = client.Post("/na", test_dtm_msg);
   auto thing2 = combined_client.Post("DTM", test_dtm_msg);
   
   //std::cout << client.Get("/fres") << std::endl;
   //std::cout << client.Get("/sdev") << std::endl;
    //std::cout << response << std::endl;
    //sep::DeviceCapability *dcap = new sep::DeviceCapability;
    //xml::Parse(boost::beast::buffers_to_string(response.body().data()), dcap);

}