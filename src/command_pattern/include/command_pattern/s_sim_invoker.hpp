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
    
    protected:

        flecs::world * shared_world_ptr_;
        BaseCommand * import_;
        BaseCommand * export_;
        BaseCommand * get_energy_;
        BaseCommand * get_nameplate_;
        BaseCommand * idle_;
};

class SimpleSimulatorInvoker : public BaseInvoker
{
    public:

        SimpleSimulatorInvoker(flecs::world * shared, BaseCommand* imp, BaseCommand* exp, BaseCommand* get_e, BaseCommand* get_n, BaseCommand * idle) 
                                : BaseInvoker(shared, imp, exp, get_e, get_n, idle)
        {std::cout<<"SimpleSimulatorInvoker"<<std::endl;}
        ~SimpleSimulatorInvoker() {}
    
    private:
};

} //namespace dcm
#endif //__S_SIM_INVOKER_H__