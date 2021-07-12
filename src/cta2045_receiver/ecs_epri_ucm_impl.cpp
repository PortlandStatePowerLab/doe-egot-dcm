#include <chrono>
#include <cea2045/util/MSTimer.h>
#include "include/cta2045_receiver/ecs_epri_ucm_impl.hpp"
#include "include/cta2045_receiver/easylogging++.h"

namespace dcm
{
using namespace std;

EPRI_UCM::EPRI_UCM() : comm_log_("VOID")
{
	m_sgdMaxPayload = cea2045::MaxPayloadLengthCode::LENGTH2;
}

//======================================================================================

EPRI_UCM::~EPRI_UCM()
{
}

//======================================================================================

std::string EPRI_UCM::commLog()
{
    std::string temp = comm_log_;
    comm_log_.erase(); //erase the log during each access
    return temp;
}

//======================================================================================

bool EPRI_UCM::isMessageTypeSupported(cea2045::MessageTypeCode messageType)
{
	LOG(INFO) << "message type supported received: " << (int)messageType;

	if (messageType == cea2045::MessageTypeCode::NONE)
		return false;

	return true;
}

//======================================================================================

cea2045::MaxPayloadLengthCode EPRI_UCM::getMaxPayload()
{
	LOG(INFO) << "max payload request received";

	return cea2045::MaxPayloadLengthCode::LENGTH4096;
}

//======================================================================================

void EPRI_UCM::processMaxPayloadResponse(cea2045::MaxPayloadLengthCode maxPayload)
{
	LOG(INFO) << "max payload response received";

	m_sgdMaxPayload = maxPayload;
}

//======================================================================================

void EPRI_UCM::processDeviceInfoResponse(cea2045::cea2045DeviceInfoResponse* message)
{
    int yr, mnth, day;
    std::string sep = "-";

	LOG(INFO) << "device info response received";

	LOG(INFO) << "    device type: " << message->getDeviceType();
	LOG(INFO) << "      vendor ID: " << message->getVendorID();

	LOG(INFO) << "  firmware date: "
			<< 2000 + (int)message->firmwareYear20xx << "-" << (int)message->firmwareMonth << "-" << (int)message->firmwareDay;

    comm_log_ += "device type: " + message->getDeviceType();
    comm_log_ += ", vendor ID: " + message->getVendorID();
    yr = 2000 + (int)message->firmwareYear20xx;
    mnth = (int)message->firmwareMonth;
    day = (int)message->firmwareDay;
    comm_log_ += ", firmware date: " + std::to_string(yr) + sep + std::to_string(mnth) + sep + std::to_string(day);
    std::cout << "COMM LOG: " << comm_log_ << std::endl;
}

//======================================================================================

void EPRI_UCM::processCommodityResponse(cea2045::cea2045CommodityResponse* message)
{
	LOG(INFO) << "commodity response received.  count: " << message->getCommodityDataCount();

	int count = message->getCommodityDataCount();
	std::cout << "Commodity Response count: " << count << std::endl;
	for (int x = 0; x < count; x++)
	{
		std::cout << "Commodity Response loop x: " << x << std::endl;
		cea2045::cea2045CommodityData *data = message->getCommodityData(x);

		LOG(INFO) << "commodity data: " << x;

		LOG(INFO) << "        code: " << (int)data->commodityCode;
		LOG(INFO) << "  cumulative: " << data->getCumulativeAmount();
		LOG(INFO) << "   inst rate: " << data->getInstantaneousRate();
	}
}

//======================================================================================

void EPRI_UCM::processAckReceived(cea2045::MessageCode messageCode)
{
	LOG(INFO) << "ack received: " << (int)messageCode;

	switch (messageCode)
	{

	case cea2045::MessageCode::SUPPORT_DATALINK_MESSAGES:
		LOG(INFO) << "supports data link messages";
		break;

	case cea2045::MessageCode::SUPPORT_INTERMEDIATE_MESSAGES:
		LOG(INFO) << "supports intermediate messages";
		break;

	default:
		break;
	}
}

//======================================================================================

void EPRI_UCM::processNakReceived(cea2045::LinkLayerNakCode nak, cea2045::MessageCode messageCode)
{
	LOG(WARNING) << "nak received";

	if (nak == cea2045::LinkLayerNakCode::UNSUPPORTED_MESSAGE_TYPE)
	{
		switch (messageCode)
		{

		case cea2045::MessageCode::SUPPORT_DATALINK_MESSAGES:
			LOG(WARNING) << "does not support data link";
			break;

		case cea2045::MessageCode::SUPPORT_INTERMEDIATE_MESSAGES:
			LOG(WARNING) << "does not support intermediate";
			break;

		default:
			break;
		}
	}
}

//======================================================================================

void EPRI_UCM::processOperationalStateReceived(cea2045::cea2045Basic *message)
{
	LOG(INFO) << "operational state received " << (int)message->opCode2;
}

//======================================================================================

void EPRI_UCM::processAppAckReceived(cea2045::cea2045Basic* message)
{
	LOG(INFO) << "app ack received";
}

//======================================================================================

void EPRI_UCM::processAppNakReceived(cea2045::cea2045Basic* message)
{
	LOG(INFO) << "app nak received";
}

//======================================================================================

void EPRI_UCM::processAppCustomerOverride(cea2045::cea2045Basic* message)
{
	LOG(INFO) << "app cust override received: " << (int)message->opCode2;
}

//======================================================================================

void EPRI_UCM::processIncompleteMessage(const unsigned char *buffer, unsigned int numBytes)
{
	LOG(WARNING) << "incomplete message received: " << numBytes;
}

} //namespace dcm
