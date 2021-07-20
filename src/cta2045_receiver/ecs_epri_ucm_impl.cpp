#include <chrono>
#include <cea2045/util/MSTimer.h>
#include "include/cta2045_receiver/ecs_epri_ucm_impl.hpp"
#include "include/cta2045_receiver/easylogging++.h"

namespace dcm
{
using namespace std;

EPRI_UCM::EPRI_UCM() : comm_log_(nullptr)
{
	m_sgdMaxPayload = cea2045::MaxPayloadLengthCode::LENGTH2;
}

//======================================================================================

EPRI_UCM::EPRI_UCM(std::string *l, CombinedHttpsClient *c) : comm_log_(l), combined_client_(c)
{
	m_sgdMaxPayload = cea2045::MaxPayloadLengthCode::LENGTH2;
}

//======================================================================================

EPRI_UCM::~EPRI_UCM()
{
    if (comm_log_)
        delete comm_log_;
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
    std::string temp = " ";

	LOG(INFO) << "device info response received";

	LOG(INFO) << "    device type: " << message->getDeviceType();
	LOG(INFO) << "      vendor ID: " << message->getVendorID();

	LOG(INFO) << "  firmware date: "
			<< 2000 + (int)message->firmwareYear20xx << "-" << (int)message->firmwareMonth << "-" << (int)message->firmwareDay;

    temp += "device type: " + std::to_string((int)message->getDeviceType());
    temp += ", vendor ID: " + std::to_string((int)message->getVendorID());
    yr = 2000 + (int)message->firmwareYear20xx;
    mnth = (int)message->firmwareMonth;
    day = (int)message->firmwareDay;
    temp += ", firmware date: " + std::to_string(yr) + sep + std::to_string(mnth) + sep + std::to_string(day);
    std::cout << "EPRI_UCM::processDeviceInfoResponse COMM LOG: " << temp << std::endl;
    *comm_log_ = temp;
}

//======================================================================================

void EPRI_UCM::processCommodityResponse(cea2045::cea2045CommodityResponse* message)
{
    int code, cumltv, rate;
    std::string temp = " ";
	LOG(INFO) << "commodity response received.  count: " << message->getCommodityDataCount();

	int count = message->getCommodityDataCount();
	for (int x = 0; x < count; x++)
	{
		std::cout << "Commodity Response loop x: " << x << std::endl;
		cea2045::cea2045CommodityData *data = message->getCommodityData(x);

		LOG(INFO) << "commodity data: " << x;

        code = (int)data->commodityCode;
        cumltv = data->getCumulativeAmount();
        rate = data->getInstantaneousRate();

        temp += " commodity code: " + std::to_string(code) + ", cumulative amount: " + std::to_string(cumltv) + ", instantaneous rate: " + std::to_string(rate);
	}
    std::cout << "EPRI_UCM::processCommodityResponse COMMODITY RESPONSE: " << temp << std::endl;
    *comm_log_ = temp;
}

//======================================================================================

void EPRI_UCM::processAckReceived(cea2045::MessageCode messageCode)
{
	LOG(INFO) << "ack received: " << (int)messageCode;
	std::string outgoing = "Ack Received: ";

	switch (messageCode)
	{

	case cea2045::MessageCode::SUPPORT_DATALINK_MESSAGES:
		LOG(INFO) << "supports data link messages";
		outgoing += "supports data link messages";
		break;

	case cea2045::MessageCode::SUPPORT_INTERMEDIATE_MESSAGES:
		LOG(INFO) << "supports intermediate messages";
		outgoing += "supports intermediate messages";
		break;

	default:
		break;
	}
	combined_client_->Post("DTM", xml_writer_.WriteMsg("DCM", "DER", outgoing, "na", "na"));
}

//======================================================================================

void EPRI_UCM::processNakReceived(cea2045::LinkLayerNakCode nak, cea2045::MessageCode messageCode)
{
	LOG(WARNING) << "nak received";
	std::string outgoing = "Nak Received: ";

	if (nak == cea2045::LinkLayerNakCode::UNSUPPORTED_MESSAGE_TYPE)
	{
		switch (messageCode)
		{

		case cea2045::MessageCode::SUPPORT_DATALINK_MESSAGES:
			LOG(WARNING) << "does not support data link";
			outgoing += "does not support data link";
			break;

		case cea2045::MessageCode::SUPPORT_INTERMEDIATE_MESSAGES:
			LOG(WARNING) << "does not support intermediate";
			outgoing += "does not support intermediate";
			break;

		default:
			break;
		}
	}
	combined_client_->Post("DTM", xml_writer_.WriteMsg("DCM", "DER", outgoing, "na", "na"));
}

//======================================================================================

void EPRI_UCM::processOperationalStateReceived(cea2045::cea2045Basic *message)
{
	int op = (int)message->opCode2;
	LOG(INFO) << "operational state received " << op;
	std::string outgoing = "Op State Received: " + std::to_string(op);
	combined_client_->Post("DTM", xml_writer_.WriteMsg("DCM", "DER", outgoing, "na", "na"));
}

//======================================================================================

void EPRI_UCM::processAppAckReceived(cea2045::cea2045Basic* message)
{
	LOG(INFO) << "app ack received";
	combined_client_->Post("DTM", xml_writer_.WriteMsg("DCM", "DER", "App Ack Received", "na", "na"));
}

//======================================================================================

void EPRI_UCM::processAppNakReceived(cea2045::cea2045Basic* message)
{
	LOG(INFO) << "app nak received";
	combined_client_->Post("DTM", xml_writer_.WriteMsg("DCM", "DER", "App Nack Received", "na", "na"));
}

//======================================================================================

void EPRI_UCM::processAppCustomerOverride(cea2045::cea2045Basic* message)
{
	LOG(INFO) << "app cust override received: " << (int)message->opCode2;
	combined_client_->Post("DTM", xml_writer_.WriteMsg("DCM", "DER", "App Customer Override Received", "na", "na"));
}

//======================================================================================

void EPRI_UCM::processIncompleteMessage(const unsigned char *buffer, unsigned int numBytes)
{
	LOG(WARNING) << "incomplete message received: " << numBytes;
	combined_client_->Post("DTM", xml_writer_.WriteMsg("DCM", "DER", "Incomplete Msg Received", "na", "na"));
}

} //namespace dcm
