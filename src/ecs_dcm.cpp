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
boost::property_tree::ptree Treeify(const std::string &xml_str)
{
    // utility function to help translate strings to/from objects
    std::stringstream ss;
    ss << xml_str;
    boost::property_tree::ptree pt;
    boost::property_tree::xml_parser::read_xml(ss, pt);
    return pt;
};
void Parse(const std::string &xml_str, sep::FlowReservationRequest *fr_request)
{
    boost::property_tree::ptree pt = Treeify(xml_str);
    fr_request->href = pt.get<std::string>("FlowReservationRequest.<xmlattr>.href", "");
    fr_request->mrid = pt.get<std::string>("FlowReservationRequest.mRID", "");
    fr_request->description = pt.get<std::string>("FlowReservationRequest.description", "");
    fr_request->version = pt.get<uint16_t>("FlowReservationRequest.version", 0);
    fr_request->creation_time = pt.get<sep::TimeType>("FlowReservationRequest.creationTime", 0);
    fr_request->duration_requested = pt.get<uint16_t>("FlowReservationRequest.durationRequested", 0);
    fr_request->energy_requested.multiplier = pt.get<sep::PowerOfTenMultiplierType>("FlowReservationRequest.energyRequested.multiplier", 0);
    fr_request->energy_requested.value = pt.get<int64_t>("FlowReservationRequest.energyRequested.value", 0);
    fr_request->interval_requested.duration = pt.get<uint32_t>("FlowReservationRequest.intervalRequested.duration", 0);
    fr_request->interval_requested.start = pt.get<sep::TimeType>("FlowReservationRequest.intervalRequested.start", 0);
    fr_request->power_requested.multiplier =  pt.get<sep::PowerOfTenMultiplierType>("FlowReservationRequest.powerRequested.multiplier", 0);
    fr_request->power_requested.value =  pt.get<sep::PowerOfTenMultiplierType>("FlowReservationRequest.powerRequested.value", 0);
    fr_request->request_status.datetime =   pt.get<sep::TimeType>("FlowReservationRequest.RequestStatus.dateTime", 0);
    fr_request->request_status.status =  static_cast<sep::Status>(pt.get<uint8_t>("FlowReservationRequest.RequestStatus.requestStatus", 0));
}
void Parse(const std::string &xml_str, sep::FlowReservationResponse *fr_response) 
{
    boost::property_tree::ptree pt = Treeify(xml_str);
    fr_response->subscribable = static_cast<sep::SubscribableType>(
        pt.get<uint8_t>("FlowReservationResponse.<xmlattr>.subscribable", 0)
    );
    fr_response->reply_to = pt.get<std::string>("FlowReservationResponse.<xmlattr>.replyTo", "");
    fr_response->response_required = static_cast<sep::ResponseRequired>(
        Dehexify<uint8_t>(pt.get<std::string>("FlowReservationResponse.<xmlattr>.responseRequired", "00"))
    );
    fr_response->href = pt.get<std::string>("FlowReservationResponse.<xmlattr>.href", "");
    fr_response->mrid = pt.get<std::string>("FlowReservationResponse.mRID", "");
    fr_response->description = pt.get<std::string>("FlowReservationResponse.description", "");
    fr_response->version = pt.get<uint16_t>("FlowReservationResponse.version", 0);
    fr_response->creation_time = pt.get<uint16_t>("FlowReservationResponse.creationTime", 0);
    fr_response->event_status.current_status = static_cast<sep::CurrentStatus>(
        pt.get<uint8_t>("FlowReservationResponse.EventStatus.currentStatus", 0)
    );
    fr_response->event_status.date_time = pt.get<uint8_t>("FlowReservationResponse.EventStatus.dateTime", 0);
    fr_response->event_status.potentially_superseded = pt.get<bool>("FlowReservationResponse.EventStatus.potentiallySuperseded", false);
    fr_response->event_status.potentially_superseded_time = pt.get<sep::TimeType>("FlowReservationResponse.EventStatus.potentiallySupersededTime", 0);
    fr_response->event_status.reason = pt.get<std::string>("FlowReservationResponse.EventStatus.reason", "");
    fr_response->interval.duration = pt.get<uint32_t>("FlowReservationResponse.interval.duration", 0);
    fr_response->interval.start = pt.get<sep::TimeType>("FlowReservationResponse.interval.start", 0);
    fr_response->energy_available.multiplier = pt.get<uint8_t>("FlowReservationResponse.energyAvailable.multiplier", 0);
    fr_response->energy_available.value = pt.get<int64_t>("FlowReservationResponse.energyAvailable.value", 0);
    fr_response->power_available.multiplier = pt.get<uint8_t>("FlowReservationResponse.powerAvailable.multiplier", 0);
    fr_response->power_available.value = pt.get<int16_t>("FlowReservationResponse.powerAvailable.value", 0);
    fr_response->subject = pt.get<std::string>("FlowReservationResponse.subject", "");
}
template<typename T>
T Dehexify(const std::string hexidecimal) 
{
    T number;
    std::stringstream ss;
    ss << std::hex << hexidecimal;
    ss >> number;
    return number;
};
void ECS_DCM::RunSimulatorLoop()
{
    std::cout << "   ECS_DCM::RunSimulatorLoop() " << std::endl;

    std::cout << " SimpleDER component count: " << dcm_world_.count<der::der_components::SimpleDER>() << std::endl;
    import_energy_c_->Execute();
    export_energy_c_->Execute();
    get_energy_c_->Execute();
    get_nameplate_c_->Execute();
    idle_c_->Execute();

    std::cout << "   Now test adding FlowResResponse to the flecs world " << std::endl;
    sep::FlowReservationRequest temp;
    Parse(FLOW_RESERVATION_REQUEST, &temp);
    GetFlowResRespFromGSP(temp);
}
void ECS_DCM::AddFlowResRespEntity(sep::FlowReservationResponse & flowresresp)
{
    dcm_world_.entity()
        .add<sep::FlowReservationResponse>().set<sep::FlowReservationResponse>({flowresresp})
        .add<sep::DateTimeInterval>().set<sep::DateTimeInterval>({flowresresp.interval})
        .add<sep::CurrentStatus>().set<sep::CurrentStatus>(flowresresp.event_status.current_status);
}
sep::FlowReservationResponse ECS_DCM::GetFlowResRespFromGSP(sep::FlowReservationRequest & freq)
{
    auto res = combined_client_->Get("/freq", FLOW_RESERVATION_REQUEST);
    std::cout << res << std::endl;
    std::string s = boost::beast::buffers_to_string(res.body.data())

    sep::FlowReservationResponse temp;
    Parse(s, &temp);
    return temp;
}


} // namespace dcm