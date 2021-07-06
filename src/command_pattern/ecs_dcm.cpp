#include "include/command_pattern/ecs_dcm.hpp"

using namespace dcm;

ECS_DCM::ECS_DCM()
    : combined_client_(nullptr),
      receiver_(nullptr),
      import_energy_c_(nullptr),
      export_energy_c_(nullptr),
      get_nameplate_c_(nullptr),
      idle_c_(nullptr)
{
    //SetReceiver();
    //need a program path
}

ECS_DCM::ECS_DCM(const std::string &root)
{
    std::cout << " ECS_DCM root arg overload constructor " << std::endl;
    SetReceiver();
    combined_client_ = new CombinedHttpsClient(root, "localhost", "443", root, "localhost", "4430");
    import_energy_c_ = new ImportEnergy(combined_client_, receiver_);
    export_energy_c_ = new ExportEnergy(combined_client_, receiver_);
    get_energy_c_ = new GetEnergy(combined_client_, receiver_);
    get_nameplate_c_ = new GetNameplate(combined_client_, receiver_);
    idle_c_ = new Idle(combined_client_, receiver_);
    sim_flow_invoker_ = new SimpleSimulatorFlowResInvoker(&dcm_world_, import_energy_c_,
                                                          export_energy_c_, get_energy_c_,
                                                          get_nameplate_c_, idle_c_);
    dcm_world_.import<dcm::dcm_components_module>();
}

ECS_DCM::~ECS_DCM()
{
    std::cout << "  ECS_DCM Destructor" << std::endl;
    delete combined_client_;
    if (sim_flow_invoker_)
        delete sim_flow_invoker_;
    delete receiver_;
    delete import_energy_c_;
    delete export_energy_c_;
    delete get_energy_c_;
    delete get_nameplate_c_;
    delete idle_c_;
}

void ECS_DCM::SetReceiver()
{
    std::cout << " ECS_DCM::SetReceiver(), please type 0 for simulator and 1 for CTA2045 " << std::endl;
    // imaginary comms tests, or pre-defined binary init
    int choice = 0;
    std::cin >> choice;
    std::cin.ignore(100, '\n');
    if (choice)
    {
        receiver_ = new CTA2045Receiver;
    }
    else
        receiver_ = new SimpleSimulatorReceiver; //emulated DER
}

void ECS_DCM::RunSimulatorLoop()
{
    // TODO
}

void ECS_DCM::TestCTA2045Commands()
{
    std::cout << "TESTING CTA-2045 COMMANDS" << std::endl;
    receiver_->GetNameplate();
    receiver_->GetEnergy();
}

void ECS_DCM::AddFlowResRespEntity(sep::FlowReservationResponse &flowresresp)
{
    // TODO
}

sep::FlowReservationResponse ECS_DCM::GetFlowResRespFromGSP()
{
    // TODO
}

void ECS_DCM::InitializeFlowResInvokingSystems()
{
    // TODO
}