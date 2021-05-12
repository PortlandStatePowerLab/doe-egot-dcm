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
#include <ecs/sim_module.hpp>

class BaseInvoker
{
    public:

        BaseInvoker() {}
        ~BaseInvoker() {}
    
    private:
};

class SimpleSimulatorInvoker : public BaseInvoker
{
    public:

        SimpleSimulatorInvoker() {}
        ~SimpleSimulatorInvoker() {}
    
    private:
};
#endif //__S_SIM_INVOKER_H__