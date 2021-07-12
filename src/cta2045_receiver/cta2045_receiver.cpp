#include "include/cta2045_receiver/cta2045_receiver.hpp"



namespace dcm
{
using namespace cea2045;
CTA2045Receiver::CTA2045Receiver() : epri_ucm_(&response_), serial_port_("/dev/ttyAMA0"), shutdown_(false)
{
    std::cout << "CTA2045 Receiver Default Constructor" << std::endl;
    if (!serial_port_.open())
	{
		LOG(ERROR) << "failed to open serial port: " << strerror(errno);
	}
    else
    {
        device_ = cea2045::DeviceFactory::createUCM(&serial_port_, &epri_ucm_);
        device_->start();
        timer_.reset();
        responseCodes_ = device_->querySuportDataLinkMessages().get();
        LOG(INFO) << "  query data link elapsed time: " << timer_.getElapsedMS();
        timer_.reset();
        responseCodes_ = device_->queryMaxPayload().get();
        LOG(INFO) << "  query max payload elapsed time: " << timer_.getElapsedMS();
        timer_.reset();
        responseCodes_ = device_->querySuportIntermediateMessages().get();
        LOG(INFO) << "  query intermediate elapsed time: " << timer_.getElapsedMS();
        timer_.reset();
        responseCodes_ = device_->intermediateGetDeviceInformation().get();
        LOG(INFO) << "  device info elapsed time: " << timer_.getElapsedMS();
        LOG(INFO) << "startup complete";
    }
}

CTA2045Receiver::~CTA2045Receiver() 
{
    std::cout << "cta2045receiver destructor" << std::endl;
    device_->shutDown();
    delete (device_);
}

std::string CTA2045Receiver::Import() 
{
    
    return xml_writer_.ReturnCustomCommand("DCM", "DER", response_, "na", "na", "response");
}

std::string CTA2045Receiver::Export() 
{
    
    return xml_writer_.ReturnCustomCommand("DCM", "DER", response_, "na", "na", "response");
}

std::string CTA2045Receiver::GetEnergy() 
{
    unsigned long elapsed = 0;
    std::string log;
    std::cout << "cta2045receiver GetEnergy() " << std::endl;
    std::string nothing = "nothing";

    timer_.reset();
    device_->intermediateGetCommodity().get();
    elapsed = timer_.getElapsedMS();

    log = response_;
    response_.erase();
    std::cout << " cta2045receiver getenergy() log: " << log << std::endl;

    return log;
}
std::string CTA2045Receiver::GetNameplate() 
{
    std::cout << "cta2045receiver GetNameplate() " << std::endl;
    std::string nothing = "nothing";
    device_->intermediateGetDeviceInformation().get();
    return nothing;
    //return xml_writer_.ReturnCustomCommand("DCM", "DER", response, "na", "na", "response");
}

std::string CTA2045Receiver::Idle() 
{
    
    return xml_writer_.ReturnCustomCommand("DCM", "DER", response_, "na", "na", "response");
}
    
} // namespace dcm

