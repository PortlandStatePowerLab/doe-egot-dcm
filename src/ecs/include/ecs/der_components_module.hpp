#ifndef __DER_COMPONENTS_MODULE_H__
#define __DER_COMPONENTS_MODULE_H__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <flecs.h>

namespace der
{

class der_components
{
    public:
        struct DERSimulatorEntityTag 
        {};

        struct SimpleDER
        {
            double available_import_energy, available_export_energy, loss_per_second;
            int loss_rate, import_low, import_high, secs_since_epoch, secs_since_command;
        };

        enum class CurrentActiveCommand : short //change this enum value to simulate commands
        {
            kNoCommand,
            kImportEnergyCommand,
            kExportEnergyCommand,
            kCustomerHasOverriddenCommands
        };

        enum class Status : short
        {
            kImporting,
            kExporting,
            kIdle,
            kCustomerOverride
        };

        der_components(flecs::world& world_) 
        {
            world_.module<der_components>();
            // Register components 
            world_.component<Status>();
            world_.component<SimpleDER>();
            world_.component<CurrentActiveCommand>();
            world_.component<DERSimulatorEntityTag>();
            
            //world_.set<DER>({1000, 4500, 0, 4500, 0});
            //create type for simulated der entities
            auto der_sim_type = world_.type("der_sim_type")
                .add<Status>()
                .add<SimpleDER>()
                .add<CurrentActiveCommand>()
                .add<DERSimulatorEntityTag>();

            auto simulated_der_entity = world_.entity("simulated_der_entity")
                                        .add(der_sim_type)
                                        .set<CurrentActiveCommand>(CurrentActiveCommand::kNoCommand)
                                        .set<SimpleDER>({600, 1500, 0.01, 25, 0, 900, 0, 0});
        }
};

} // namespace der


#endif // __DER_COMPONENTS_MODULE_H__
