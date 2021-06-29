#ifndef __CTA2045_RECEIVER_H__
#define __CTA2045_RECEIVER_H__

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
#include <ecs/der_components_module.hpp>
#include <ecs/dcm_components_module.hpp>
#include <command_pattern/simple_sim_receiver.hpp>
#include <cea2045/processmessage/IUCM.h>

namespace dcm
{

// This is a receiver class for interacting with a simulated DER
class CTA2045Receiver : public BaseReceiver
{
    public:

        CTA2045Receiver() 
        {
            std::cout << " CTA2045Receiver default constructor " << std::endl;
        }
        ~CTA2045Receiver() 
        {
            
        }
        std::string Import() 
        {
            
            return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
        }
        std::string Export() 
        {
            
            return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
        }
        std::string GetEnergy() 
        {
            
            return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
        }
        std::string GetNameplate() 
        {
          
            return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
        }
        std::string Idle() 
        {
         
            return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
        }

    private:
        xml::XMLCommandAdapter xml_writer_;
};

} // namespace dcm


#endif //__ECS_DCM_H__