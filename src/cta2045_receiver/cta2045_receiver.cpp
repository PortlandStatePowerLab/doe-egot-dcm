#include "include/cta2045_receiver/cta2045_receiver.hpp"



namespace dcm
{
using namespace cea2045;
CTA2045Receiver::CTA2045Receiver(): serial_port("/dev/ttyAMA0"), shutdown(false)
{
    
    std::cout << "CTA2045 Receiver Default Constructor" << std::endl;
    if (!serial_port.open())
	{
		LOG(ERROR) << "failed to open serial port: " << strerror(errno);
	}
    else
    {
        device = cea2045::DeviceFactory::createUCM(&serial_port, &epri_ucm);
        device->start();
        timer.reset();
        responseCodes = device->querySuportDataLinkMessages().get();
        LOG(INFO) << "  query data link elapsed time: " << timer.getElapsedMS();
        timer.reset();
        responseCodes = device->queryMaxPayload().get();
        LOG(INFO) << "  query max payload elapsed time: " << timer.getElapsedMS();
        timer.reset();
        responseCodes = device->querySuportIntermediateMessages().get();
        LOG(INFO) << "  query intermediate elapsed time: " << timer.getElapsedMS();
        timer.reset();
        responseCodes = device->intermediateGetDeviceInformation().get();
        LOG(INFO) << "  device info elapsed time: " << timer.getElapsedMS();
        LOG(INFO) << "startup complete";
    }
}

CTA2045Receiver::~CTA2045Receiver() 
{
    device->shutDown();
    delete device;
}

std::string CTA2045Receiver::Import() 
{
    
    return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
}

std::string CTA2045Receiver::Export() 
{
    
    return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
}

std::string CTA2045Receiver::GetEnergy() 
{
    
    return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
}

std::string CTA2045Receiver::GetNameplate() 
{
    
    return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
}

std::string CTA2045Receiver::Idle() 
{
    
    return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
}
    
} // namespace dcm

