#include "include/cta2045_receiver/cta2045_rcvr.hpp"
#include <cea2045/device/DeviceFactory.h>
#include <cea2045/communicationport/CEA2045SerialPort.h>
namespace dcm 
{

CTA2045Receiver::CTA2045Receiver(): serial_port("/dev/ttyUSB0")
{
    
}
CTA2045Receiver::~CTA2045Receiver() {}

} // namespace dcm