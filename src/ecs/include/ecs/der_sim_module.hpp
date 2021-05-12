#ifndef __DER_SIM_MODULE_H__
#define __DER_SIM_MODULE_H__
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
        }
};

class der_simulator_module 
{
    public:
/*
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
*/
        der_simulator_module(flecs::world& world_) 
        {
            //Register module with world 
            world_.module<der_simulator_module>();
            world_.import<der_components>();
/*
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
            //instantiate m_simulated_der memeber as an instance of that type
            m_simulated_der = world_.entity("m_sim_der_1").add(der_sim_type).set<SimpleDER>({600, 1800, 0.166, 60, 0, 900, 0, 0})
                                                            .set<Status>(Status::kIdle)
                                                            .set<CurrentActiveCommand>(CurrentActiveCommand::kNoCommand);
            */
            //auto q = world_.query<der::der_simulator_module::SimpleDER>();

            world_.system<der_components::DERSimulatorEntityTag, der_components::SimpleDER, der_components::CurrentActiveCommand, der_components::Status>("UpdateSimDER")  
                .each([this](flecs::entity e, der_components::DERSimulatorEntityTag& x, der_components::SimpleDER& d, der_components::CurrentActiveCommand& c, der_components::Status& s)
                {
                    ++d.secs_since_epoch;

                    if ( c != der_components::CurrentActiveCommand::kNoCommand )
                    {
                        ++d.secs_since_command;
                        if (!d.secs_since_command)
                        {
                            switch (c) 
                            {
                                case der_components::CurrentActiveCommand::kImportEnergyCommand:
                                {
                                    d.import_high = 300;
                                    d.import_low = 0;
                                    break;
                                }
                                case der_components::CurrentActiveCommand::kExportEnergyCommand:
                                {
                                    d.import_high = 2100;
                                    d.import_low = 1725;
                                    break;
                                }
                                case der_components::CurrentActiveCommand::kCustomerHasOverriddenCommands:
                                {
                                    d.import_high = 900;
                                    d.import_low = 0;
                                    break;
                                }
                            }
                        }
                    }
                    else if ( ( c == der_components::CurrentActiveCommand::kNoCommand ) && ( d.secs_since_command > 0 ) )
                    {
                        d.secs_since_command = 0;
                        d.import_high = 900;
                        d.import_low = 0;
                    }

                    if (s != der_components::Status::kImporting)
                    {
                        if (s == der_components::Status::kIdle)
                        {
                            //std::cout << ( d.import_high - ((d.import_high - d.import_low) / 2)) << std::endl;
                            if (d.available_import_energy < d.import_high) //see section 3 of leighton's thesis
                            { 
                                d.available_import_energy += d.loss_per_second;
                                d.available_export_energy = 2100 - d.available_import_energy;
                                UpdateSimpleLossRates(&d);
                            }
                            else
                            {
                                s = der_components::Status::kImporting;
                                std::cout << "     DER Status changed: Importing   " << std::endl;
                            }
                        }
                    }
                    else if (s == der_components::Status::kImporting)
                    {
                        if (d.available_import_energy > ( d.import_high - ((d.import_high - d.import_low) / 2 )))
                        {
                            d.available_import_energy -= 0.55; //approx Wh of available import energy lost per second during import for EWH
                            d.available_export_energy = 2100 - d.available_import_energy;
                            UpdateSimpleLossRates(&d);
                        }
                        else
                        {
                            s = der_components::Status::kIdle;
                            std::cout << "     DER Status changed: Idle   " << std::endl;
                        }
                    }
                    //std::cout << "Available Import Energy: " << d.available_import_energy << "Wh" << std::endl;
                }
                );   

            world_.system<der_components::DERSimulatorEntityTag, der_components::SimpleDER>("SimulateDraw")  
                .each([](flecs::entity e, der_components::DERSimulatorEntityTag& x, der_components::SimpleDER& d)
                {
                    int random = ( rand() % 7200 );
                    //std::cout << "random " << random << " " << std::endl;
                    if (random == 30)
                    {
                        double delta = ( rand() % int( ( 4500 - d.available_import_energy ) ) );
                        double draw = d.available_import_energy + delta;
                        if (delta > 1000)
                        {
                            if ( !( rand() % 3 == 0 ) )
                            {
                                std::cout << " (x) ";
                                draw -= 1000;
                            }
                                
                        }
                        std::cout << "    Random draw. Prev import Wh: " << d.available_import_energy << std::endl;
                        std::cout << "    delta import Wh: " << delta << std::endl;
                        std::cout << "    new import Wh: " << draw << std::endl;
                        d.available_import_energy = draw;

                        if (d.available_import_energy > 2100)
                        {
                            d.available_export_energy = 0;
                        }
                        else
                        {
                            d.available_export_energy = 2100 - d.available_import_energy;
                        }
                    }
                }
                );   
        }

        void UpdateSimpleLossRates(der_components::SimpleDER * der) //remember to pass the pointer
        {
            der->loss_rate =  22000 / ( der->available_import_energy + 215 );
            der->loss_per_second = double( double(der->loss_rate) / 3600 );
            //std::cout << "loss rate updates: " << der->loss_rate << "  " << der->loss_per_second << " " << der->available_import_energy << std::endl;
        }
        
        flecs::entity m_simulated_der;
};

} //namespace der
#endif //__DER_SIM_MODULE_H__