#ifndef __SIMPLE_SIM_RECEIVER_H__
#define __SIMPLE_SIM_RECEIVER_H__
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

class BaseReceiver
{
    public:

        BaseReceiver() {}
        ~BaseReceiver() {}
        virtual void Polymorphism(void) {}

    private:
};

class SimpleSimulatorReceiver : public BaseReceiver
{
    public:

        SimpleSimulatorReceiver() {}
        ~SimpleSimulatorReceiver() {}
        void Polymorphism() {}

    private:
};


#endif //__SIMPLE_SIM_RECEIVER_H__