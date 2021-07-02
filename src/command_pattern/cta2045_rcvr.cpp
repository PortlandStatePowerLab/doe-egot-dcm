#include "include/command_pattern/cta2045_rcvr.hpp"
#include <cea2045/device/DeviceFactory.h>
#include <cea2045/communicationport/CEA2045SerialPort.h>
namespace dcm 
{

CTA2045Receiver::CTA2045Receiver(): serial_port("/dev/ttyUSB0"), shutdown(false)
{
    if (!serial_port.open())
	{
		LOG(ERROR) << "failed to open serial port: " << strerror(errno);
	}

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
CTA2045Receiver::~CTA2045Receiver() {}

} // namespace dcm