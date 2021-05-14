#ifndef __S_SIM_INVOKER_H__
#define __S_SIM_INVOKER_H__
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <flecs.h>
#include <sstream>
#include <https/https_client.hpp>
#include <https/combined_client.hpp>
#include <sep/models.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <ecs/sim_invoker_module.hpp>
#include "dcm_commands.hpp"

namespace dcm
{

class BaseInvoker 
{
    public:

        BaseInvoker(flecs::world * shared) : shared_world_ptr_(shared)
        {}
        BaseInvoker(flecs::world * shared, BaseCommand* imp, BaseCommand* exp, 
                    BaseCommand* get_e, BaseCommand* get_n, BaseCommand* idle) 
                        : shared_world_ptr_(shared), 
                        import_(imp), export_(exp), get_energy_(get_e), 
                        get_nameplate_(get_n), idle_(idle)
        {
            shared_world_ptr_->import<sim_invoker_module>();
        }
        ~BaseInvoker() {}
        virtual void ProcessResource(flecs::entity * e) {}
    
    protected:

        flecs::world * shared_world_ptr_;
        BaseCommand * import_;
        BaseCommand * export_;
        BaseCommand * get_energy_;
        BaseCommand * get_nameplate_;
        BaseCommand * idle_;
};

class SimpleSimulatorFlowResInvoker : public BaseInvoker
{
    public:

        SimpleSimulatorFlowResInvoker(flecs::world * shared, BaseCommand* imp, BaseCommand* exp, BaseCommand* get_e, BaseCommand* get_n, BaseCommand * idle) 
                                : BaseInvoker(shared, imp, exp, get_e, get_n, idle)
        {std::cout<<"SimpleSimulatorFlowResInvoker"<<std::endl;}
        ~SimpleSimulatorFlowResInvoker() {}
        void ProcessResource(flecs::entity * e)
        {
            std::cout << "SSFRI ProcessResource method called" << std::endl;
            if ( e->has<sep::FlowReservationResponse>() )
            {
                std::cout << "entity has flowreservation response" << std::endl;
                sep::FlowReservationResponse* flowres_ptr = e->get_mut<sep::FlowReservationResponse>();
                sep::CurrentStatus* c_status_ptr = e->get_mut<sep::CurrentStatus>();

                // Hook to change entity's status components based on contents of flowresresp component
                // also, we can actually sent commands, though I don't know the specifics of how that logic should work
                // Now we can look at the data in the flowres_ptr and call a command or something 

                // demo of commands
                if ( *c_status_ptr == sep::CurrentStatus::kActive )
                {
                    std::cout << "flowres entity currentStatus is Active " << std::endl;
                    import_->Execute();
                    shared_world_ptr_->set<dcm_components_module::DERPrevCommand>({dcm_components_module::DERPrevCommand::kImportEnergy});
                }


            
            }
        }
    
    private:
};

} //namespace dcm
#endif //__S_SIM_INVOKER_H__