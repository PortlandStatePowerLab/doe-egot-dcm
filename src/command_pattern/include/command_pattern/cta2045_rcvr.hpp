#ifndef __CTA2045_RCVR_H__
#define __CTA2045_RCVR_H__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <command_pattern/simple_sim_receiver.hpp>
#include <cea2045/device/DeviceFactory.h>
#include <cea2045/communicationport/CEA2045SerialPort.h>
#include <cea2045/util/MSTimer.h>
#include "UCMImpl.h"
#include "easylogging++.h"

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
        UCMImpl epri_ucm;
        cea2045::CEA2045SerialPort serial_port;
        cea2045::ResponseCodes responseCodes;
        cea2045::MSTimer timer;
        bool shutdown;
        cea2045::ICEA2045DeviceUCM * device;
};

} // namespace dcm


#endif //__ECS_DCM_H__