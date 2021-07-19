#include "include/command_pattern/dcm_commands.hpp"

using namespace dcm;

BaseCommand::BaseCommand() : https_client_(nullptr), receiver_(nullptr)
{
    // do nothing
}

BaseCommand::BaseCommand(CombinedHttpsClient *c, BaseReceiver *r)
    : https_client_(c), receiver_(r)
{
    // do nothing
}

BaseCommand::~BaseCommand()
{
    //delete https_client_;
    //delete receiver_;
}

//=================================================================================

ImportEnergy::ImportEnergy()
{
    // do nothing
}

ImportEnergy::ImportEnergy(CombinedHttpsClient *client, BaseReceiver *receiver)
    : BaseCommand(client, receiver)
{
    std::cout << "ImportEnergy Command Constructed " << std::endl;
}

ImportEnergy::~ImportEnergy()
{
    // do nothing
}

std::string ImportEnergy::Execute()
{
    std::string response_from_der = "der response not supported yet";
    std::cout << "  ImportEnergy Command Executing... " << std::endl;

    //this is specific to a simulated receiver at this point, and not based on a particular resource.
    std::string msg_out = xml_writer_.ReturnCustomCommand("DER", "DCM", "ImportEnergy", "na", "na", "command");
    https_client_->Post("DTM", msg_out);

    response_from_der = receiver_->Import();
    https_client_->Post("DTM", response_from_der);

    //std::cout << "response from DER was: " << response_from_der << std::endl;
    //std::string msg_in =  xml_writer_.ReturnCustomCommand("DCM", "DER", response_from_der, "na", "na", "response");
    //https_client_->Post("DTM",msg_in);

    return response_from_der;
}

//=================================================================================

ExportEnergy::ExportEnergy()
{
    // do nothing
}

ExportEnergy::ExportEnergy(CombinedHttpsClient *client, BaseReceiver *receiver)
    : BaseCommand(client, receiver)
{
    // do nothing
}

ExportEnergy::~ExportEnergy()
{
    // do nothing
}

std::string ExportEnergy::Execute()
{
    std::string response_from_der = "der response not supported yet";
    std::cout << "  ExportEnergy Command Executing... " << std::endl;

    //this is specific to a simulated receiver at this point, and not based on a particular resource.
    std::string msg_out = xml_writer_.ReturnCustomCommand("DER", "DCM", "ExportEnergy", "na", "na", "command");
    https_client_->Post("DTM", msg_out);

    response_from_der = receiver_->Export();
    https_client_->Post("DTM", response_from_der);

    return response_from_der;
}

//=================================================================================

GetEnergy::GetEnergy()
{
    // do nothing
}

GetEnergy::GetEnergy(CombinedHttpsClient *client, BaseReceiver *receiver)
    : BaseCommand(client, receiver)
{
    // do nothing
}

GetEnergy::~GetEnergy()
{
    // do nothing
}

std::string GetEnergy::Execute()
{
    std::string response_from_der = "der response not supported yet";
    std::cout << "  GetEnergy Command Executing... " << std::endl;

    //this is specific to a simulated receiver at this point, and not based on a particular resource.
    std::string msg_out = xml_writer_.WriteMsg("DCM", "DER", "GetNameplate", "na", "na");
    https_client_->Post("DTM", msg_out);
    response_from_der = receiver_->GetEnergy();
    if (response_from_der[0] == 'C') //if cta2045receiver
    {
        std::cout << "GetEnergy::Execute() response from der: " << response_from_der << std::endl;
    }
    std::string msg_in = xml_writer_.WriteMsg("DCM", "DER", "GetNameplate", "na", response_from_der);
    https_client_->Post("DTM", msg_in);
    return response_from_der;
}

//=================================================================================

GetNameplate::GetNameplate()
{
    // do nothing
}

GetNameplate::GetNameplate(CombinedHttpsClient *client, BaseReceiver *receiver)
    : BaseCommand(client, receiver)
{
    // do nothing
}

GetNameplate::~GetNameplate()
{
    // do nothing
}

std::string GetNameplate::Execute()
{
    std::string response_from_der = "der response not supported yet";
    std::cout << "  GetNameplate Command Executing... " << std::endl;

    //
    std::string msg_out = xml_writer_.WriteMsg("DCM", "DER", "GetNameplate", "na", "na");
    https_client_->Post("DTM", msg_out);
    response_from_der = receiver_->GetNameplate();
    std::string msg_in = xml_writer_.WriteMsg("DCM", "DER", "GetNameplate", "na", response_from_der);
    https_client_->Post("DTM", msg_in);

    return response_from_der;
}

//=================================================================================

Idle::Idle()
{
    // do nothing
}

Idle::Idle(CombinedHttpsClient *client, BaseReceiver *receiver)
    : BaseCommand(client, receiver)
{
    // do nothing
}

Idle::~Idle()
{
    // do nothing
}

std::string Idle::Execute()
{
    std::string response_from_der = "der response not supported yet";
    std::cout << "  Idle Command Executing... " << std::endl;

    //this is specific to a simulated receiver at this point, and not based on a particular resource.
    std::string msg_out = xml_writer_.ReturnCustomCommand("DER", "DCM", "Idle", "na", "na", "command");
    https_client_->Post("DTM", msg_out);

    response_from_der = receiver_->Idle();
    https_client_->Post("DTM", response_from_der);

    return response_from_der;
}

//=================================================================================

CriticalPeakEvent::CriticalPeakEvent()
{
    // do nothing
}

CriticalPeakEvent::CriticalPeakEvent(CombinedHttpsClient *client, BaseReceiver *receiver)
    : BaseCommand(client, receiver)
{
    // do nothing
}

CriticalPeakEvent::~CriticalPeakEvent()
{
    // do nothing
}

std::string CriticalPeakEvent::Execute()
{
    std::string response_from_der = "der response not supported yet";
    std::cout << "  CriticalPeakEvent Command Executing... " << std::endl;

    //this is specific to a simulated receiver at this point, and not based on a particular resource.
    std::string msg_out = xml_writer_.ReturnCustomCommand("DER", "DCM", "CriticalPeakEvent", "na", "na", "command");
    https_client_->Post("DTM", msg_out);
    response_from_der = receiver_->CriticalPeakEvent();
    https_client_->Post("DTM", response_from_der);

    return response_from_der;
}