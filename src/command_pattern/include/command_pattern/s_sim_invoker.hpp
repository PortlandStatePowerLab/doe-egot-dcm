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
        ~BaseInvoker() {}
    
    protected:

        flecs::world * shared_world_ptr_;
        BaseCommand * import_;
        BaseCommand * export_;
        BaseCommand * get_energy_;
        BaseCommand * get_nameplate_;
};

class SimpleSimulatorInvoker : public BaseInvoker
{
    public:

        SimpleSimulatorInvoker(flecs::world * shared) : BaseInvoker(shared)
        {}
        ~SimpleSimulatorInvoker() {}
    
    private:
};

} //namespace dcm
#endif //__S_SIM_INVOKER_H__