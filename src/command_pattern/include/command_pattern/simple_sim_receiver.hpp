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
        virtual std::string Import() {}
        virtual std::string Export() {}
        virtual std::string GetEnergy() {}
        virtual std::string GetNameplate() {}
        virtual std::string Idle() {}

    private:


};
// This is a receiver class for interacting with a simulated DER
class SimpleSimulatorReceiver : public BaseReceiver
{
    public:

        SimpleSimulatorReceiver() 
        {
            std::cout << " SimpleSimulatorReceiver default constructor " << std::endl;
            sim_der_ = new der::DERSimulator;
        }
        ~SimpleSimulatorReceiver() 
        {
            delete sim_der_;
        }
        std::string Import() 
        {
            return sim_der_->ImportEnergy();
        }
        std::string Export() 
        {
            return sim_der_->ExportEnergy();
        }
        std::string GetEnergy() 
        {
            return sim_der_->GetEnergy();
        }
        std::string GetNameplate() 
        {
            return sim_der_->GetNameplate();
        }
        std::string Idle() 
        {
            return sim_der_->Idle();
        }
        void IncrementSimulatorProgress()
        {
            sim_der_->IncrementProgress();
        }

    private:

        der::DERSimulator* sim_der_;
};

} // namespace dcm

#endif //__SIMPLE_SIM_RECEIVER_H__