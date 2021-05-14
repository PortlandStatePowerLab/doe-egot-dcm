#ifndef __DCM_COMPONENTS_MODULE_H__
#define __DCM_COMPONENTS_MODULE_H__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <flecs.h>
#include <sep/models.hpp>
#include <command_pattern/dcm_commands.hpp>
#include "der_sim_module.hpp"
#include "der_components_module.hpp"

namespace dcm
{
class dcm_components_module
{
    public:

        enum class DERPrevCommand : short // command last sent to DER
        {
            kImportEnergy, 
            kExportEnergy, 
            kGetEnergy, 
            kGetNameplate, 
            kIdle,
            kNone
        };

        enum class DERMostRecentResponse : short // last response received from the DER
        {
            kAck, 
            kNack,
            kAvailableEnergy, 
            kNameplate, 
            kCustomerHasOveridden,
            kNone, 
            kError
        };

        enum class ECSResourceStatus : short // last response received from the DER
        {
            kNew, 
            kCurrentlyActive, 
            kAlreadyEnacted, 
            kAwaitingProcessing, 
            kProcessed,
            kScheduled,
            kObsolete
        };

        enum class ResourceType : short // last response received from the DER
        {
            kFlowReservationResponse,
            kSelfDevice, 
            kEndDevice, 
            kDeviceCapability
        };
        struct DERMirror
        {
            double available_import_energy, available_export_energy;

        };

        struct PollRate
        {
            int poll_rate;
        };



        dcm_components_module(flecs::world& world) 
        {
            //Register module with world 
            world.module<dcm_components_module>();
            
            // register IEEE resources as components
            world.component<sep::SelfDevice>();
            world.component<sep::EndDevice>();
            world.component<sep::DeviceCapability>();
            world.component<sep::Time>();
            world.component<sep::ActivePower>();
            world.component<sep::DateTimeInterval>();
            world.component<sep::FlowReservationRequest>();
            world.component<sep::FlowReservationResponse>();
            world.component<sep::CurrentStatus>();
            world.component<ECSResourceStatus>();
            world.component<ResourceType>();
            world.component<PollRate>();

            // register DER state tracking singletons
            world.set<DERMirror>({600, 1500});
            world.set<DERMostRecentResponse>({DERMostRecentResponse::kNone});
            world.set<DERPrevCommand>({DERPrevCommand::kNone});

            auto flowres_resp_type = world.type("FlowResRespEntity")
                .add<sep::FlowReservationResponse>()
                .add<sep::CurrentStatus>()
                .add<sep::DateTimeInterval>();
            
            auto self_device = world.type("SelfDeviceEntity")
                .add<sep::SelfDevice>()
                .add<PollRate>();
            
            auto end_device = world.type("EndDeviceEntity")
                .add<sep::EndDevice>()
                .add<PollRate>();

            auto device_capability = world.type("DeviceCapabilityEntity")
                .add<sep::DeviceCapability>()
                .add<PollRate>();

        }
};


} // namespace dcm


#endif // __DCM_COMPONENTS_MODULE_H__
