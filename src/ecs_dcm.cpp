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

    std::cout << " SimpleDER component count: " << dcm_world_.count<der::der_components::SimpleDER>() << std::endl;
    import_energy_c_->Execute();
    export_energy_c_->Execute();
    get_energy_c_->Execute();
    get_nameplate_c_->Execute();
    idle_c_->Execute();
}


} // namespace dcm