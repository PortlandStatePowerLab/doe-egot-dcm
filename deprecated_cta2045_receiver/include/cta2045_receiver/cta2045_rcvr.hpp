#ifndef __CTA2045_RCVR_H__
#define __CTA2045_RCVR_H__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <command_pattern/simple_sim_receiver.hpp>
#include <cea2045/processmessage/IUCM.h>


namespace dcm
{

// This is a receiver class for interacting with a simulated DER
class CTA2045Receiver : public BaseReceiver
{
    public:

        CTA2045Receiver();
        ~CTA2045Receiver();
        std::string Import();
        std::string Export();
        std::string GetEnergy();
        std::string GetNameplate();
        std::string Idle();
    private:
        std::string response;
        xml::XMLCommandAdapter xml_writer_;
};

} // namespace dcm


#endif //__ECS_DCM_H__