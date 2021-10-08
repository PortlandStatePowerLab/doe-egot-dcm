#include <command_pattern/ecs_dcm.hpp>
#include <cea2045/processmessage/ProcessMessageUCM.h>
#include <cea2045/linklayer/LinkLayerCommImpl.h>
#include <cta2045_receiver/ecs_DeviceFactory.hpp>
//#include "cta2045_receiver.hpp"

namespace dcm
{
using namespace cea2045;

ECS_DeviceFactory::ECS_DeviceFactory(std::string *comm, CombinedHttpsClient * cc) :
    comm_log_(comm), combined_client_(cc)
{
}

//======================================================================================

ECS_DeviceFactory::~ECS_DeviceFactory()
{
    comm_log_ = nullptr;
    combined_client_ = nullptr;
}

//======================================================================================

ICEA2045DeviceUCM *ECS_DeviceFactory::createUCM(ICommunicationPort *port, IUCM *ucm)
{
	std::unique_ptr<ProcessMessageUCM> processMessage = std::unique_ptr<ProcessMessageUCM>(new ProcessMessageUCM(ucm));
	std::unique_ptr<LinkLayerCommImpl> linkLayerImpl = std::unique_ptr<LinkLayerCommImpl>(new LinkLayerCommImpl(port));

	ECS_CEA2045DeviceUCM *device = new ECS_CEA2045DeviceUCM(std::move(linkLayerImpl), std::move(processMessage), comm_log_, combined_client_);

	return device;
}

} // namespace dcm