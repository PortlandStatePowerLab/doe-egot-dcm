#include "include/command_pattern/s_sim_invoker.hpp"

using namespace dcm;

BaseInvoker::BaseInvoker(
    flecs::world *shared,
    ImportEnergy *imp,
    ExportEnergy *exp,
    GetEnergy *get_e,
    GetNameplate *get_n,
    Idle *idle)
    : shared_world_ptr_(shared),
      import_(imp),
      export_(exp),
      get_energy_(get_e),
      get_nameplate_(get_n),
      idle_(idle)
{
    shared_world_ptr_->import<sim_invoker_module>();
}

BaseInvoker::~BaseInvoker()
{
    delete idle_;
    delete get_nameplate_;
    delete get_energy_;
    delete export_;
    delete import_;
    delete shared_world_ptr_;
}

SimpleSimulatorFlowResInvoker::SimpleSimulatorFlowResInvoker(
    flecs::world *shared,
    ImportEnergy *imp,
    ExportEnergy *exp,
    GetEnergy *get_e,
    GetNameplate *get_n,
    Idle *idle)
    : BaseInvoker(shared, imp, exp, get_e, get_n, idle)
{
    std::cout << "SimpleSimulatorFlowResInvoker" << std::endl;
}

SimpleSimulatorFlowResInvoker::~SimpleSimulatorFlowResInvoker()
{
    // do nothing
}

void SimpleSimulatorFlowResInvoker::ProcessResource(flecs::entity *e)
{
    std::cout << "SSFRI ProcessResource method called" << std::endl;
    if (e->has<sep::FlowReservationResponse>())
    {
        std::cout << "entity has flowreservation response" << std::endl;
        sep::FlowReservationResponse *flowres_ptr = e->get_mut<sep::FlowReservationResponse>();
        sep::CurrentStatus *c_status_ptr = e->get_mut<sep::CurrentStatus>();

        // Hook to change entity's status components based on contents of flowresresp component
        // also, we can actually sent commands, though I don't know the specifics of how that logic should work
        // Now we can look at the data in the flowres_ptr and call a command or something

        // demo of commands
        if (*c_status_ptr == sep::CurrentStatus::kActive)
        {
            std::cout << "flowres entity currentStatus is Active " << std::endl;
            import_->Execute();
            shared_world_ptr_->set<dcm_components_module::DERPrevCommand>({dcm_components_module::DERPrevCommand::kImportEnergy});
        }
    }
}