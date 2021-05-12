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

namespace dcm
{

void ECS_DCM::RunSimulatorLoop()
{
    std::cout << "   ECS_DCM::RunSimulatorLoop() " << std::endl;
}


} // namespace dcm