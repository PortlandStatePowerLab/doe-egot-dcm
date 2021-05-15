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
#include <dtm_msg_writer/announce_xml.h>

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
            std::string response = sim_der_->ImportEnergy();
            return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
        }
        std::string Export() 
        {
            std::string response = sim_der_->ExportEnergy();
            return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
        }
        std::string GetEnergy() 
        {
            std::string response = sim_der_->GetEnergy();
            return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
        }
        std::string GetNameplate() 
        {
            std::string response = sim_der_->GetNameplate();
            return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
        }
        std::string Idle() 
        {
            std::string response = sim_der_->Idle();
            return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
        }
        void IncrementSimulatorProgress()
        {
            sim_der_->IncrementProgress();
        }

    private:
        xml::XMLCommandAdapter xml_writer_;
        der::DERSimulator* sim_der_;
};

} // namespace dcm

#endif //__SIMPLE_SIM_RECEIVER_H__