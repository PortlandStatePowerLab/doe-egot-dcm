#include "include/cta2045_receiver/cta2045_receiver.hpp"

namespace dcm
{

CTA2045Receiver::CTA2045Receiver() 
{
    std::cout << " CTA2045Receiver default constructor " << std::endl;
}

CTA2045Receiver::~CTA2045Receiver() 
{
    
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

