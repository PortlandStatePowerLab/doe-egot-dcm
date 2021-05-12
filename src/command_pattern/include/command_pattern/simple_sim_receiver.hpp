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
#include <ecs/der_simulator.hpp>

namespace dcm
{

class BaseReceiver
{
    public:

        BaseReceiver() {}
        ~BaseReceiver() {}
        virtual void Polymorphism(void) {}

    private:


};
// This is a receiver class for interacting with a simulated DER
class SimpleSimulatorReceiver : public BaseReceiver
{
    public:

        SimpleSimulatorReceiver() 
        {
            sim_der_ = new der::DERSimulator;
        }
        ~SimpleSimulatorReceiver() 
        {
            delete sim_der_;
        }
        void Polymorphism() {}

    private:

        der::DERSimulator* sim_der_;
};

} // namespace dcm

#endif //__SIMPLE_SIM_RECEIVER_H__