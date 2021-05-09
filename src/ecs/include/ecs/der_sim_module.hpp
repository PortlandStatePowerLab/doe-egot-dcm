#ifndef __DER_SIM_MODULE_H__
#define __DER_SIM_MODULE_H__
#include <iostream>
#include <flecs.h>

namespace der
{

class der_simulator_module 
{
    public:
        struct DERSimulatorEntityTag 
        {};

        struct SimpleDER
        {
            int available_import_energy, available_export_energy, loss_rate;
        };

        struct Energy
        {
            int watt_hours;

        };

        struct Power
        {
            int watts;

        };

        enum class Status : short
        {
            kImporting,
            kExporting,
            kIdle,
            kCustomerOverride
        };

        der_simulator_module(flecs::world& world_) 
        {
            der_import_high_ = 900;
            der_import_low_ = 0;
            /* Register module with world */
            world_.module<der_simulator_module>();

            /* Register components */
            world_.component<Status>();
            world_.component<Energy>();
            world_.component<Power>();
            world_.component<SimpleDER>();
            world_.component<DERSimulatorEntityTag>();

            //world_.set<DER>({1000, 4500, 0, 4500, 0});
            //create type for simulated der entities
            auto der_sim_type = world_.type("der_sim_type")
                .add<Status>()
                .add<Energy>()
                .add<Power>()
                .add<SimpleDER>()
                .add<DERSimulatorEntityTag>();
            //instantiate m_simulated_der memeber as an instance of that type
            m_simulated_der = world_.entity().add(der_sim_type).set<SimpleDER>({600, 1800, 60})
                                                            .set<Status>(Status::kIdle);

            //auto q = world_.query<Status, Energy, Power>("$DER");

            world_.system<DERSimulatorEntityTag, SimpleDER, Status>("UpdateSimDER")  
                .each([](flecs::entity e, DERSimulatorEntityTag& x, SimpleDER& d, Status& s)
                {
                    if (s != Status::kImporting)
                    {
                        if (s == Status::kIdle)
                        {
                            if (d.available_import_energy < 900) //see section 3 of leighton's thesis
                            { 
                                d.available_import_energy += d.loss_rate;
                                d.available_export_energy = 2100 - d.available_export_energy;
                                d.loss_rate = 22000 / ( d.available_import_energy + 215 );
                            }
                            else
                            {
                                s = Status::kImporting;
                            }
                        }
                    }
                    std::cout << "Available Import Energy: " << d.available_import_energy << "Wh" << std::endl;
                }
                );   
        }

        flecs::entity m_simulated_der;
        int der_import_low_;
        int der_import_high_;
        

};

} //namespace der
#endif //__DER_SIM_MODULE_H__