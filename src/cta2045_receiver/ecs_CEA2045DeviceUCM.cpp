#include <command_pattern/ecs_dcm.hpp>
#include "include/cta2045_receiver/easylogging++.h"


namespace dcm
{

using namespace cea2045;

ECS_CEA2045DeviceUCM::ECS_CEA2045DeviceUCM(std::unique_ptr<ILinkLayerComm> linkLayer, std::unique_ptr<IProcessMessage> processMessage,
        std::string * comm, CombinedHttpsClient *client) :
	CEA2045Device(std::move(linkLayer), std::move(processMessage)),
    comm_log_(comm), combined_client_(client)
{
}

ECS_CEA2045DeviceUCM::ECS_CEA2045DeviceUCM(ILinkLayerComm *linkLayer, IProcessMessage *processMessage,
        std::string * comm, CombinedHttpsClient *client) :
	CEA2045Device(linkLayer, processMessage),
    comm_log_(comm), combined_client_(client)
{
}

ECS_CEA2045DeviceUCM::~ECS_CEA2045DeviceUCM()
{

}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::intermediateGetDeviceInformation()
{
	return queueRequest(new Intermediate(MessageCode::DEVICE_INFORMATION_REQUEST,
			INFO_REQ, INFO_REQ));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::intermediateGetCommodity()
{
	return queueRequest(new Intermediate(MessageCode::GET_COMMODITY_REQUEST,
			COMMODITY_READ, CLEAR_OP_CODE2));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::intermediateGetTemperatureOffset()
{
	return queueRequest(new Intermediate(MessageCode::GET_TEMPERATURE_OFFSET,
			GET_SET, TEMP_OFFSET));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::intermediateGetSetPoint()
{
	return queueRequest(new Intermediate(MessageCode::GET_SETPOINTS_REQUEST,
			GET_SET, TEMP_SETPOINT));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::intermediateGetPresentTemperature()
{
	return queueRequest(new Intermediate(MessageCode::GET_PRESENT_TEMPERATURE_REQUEST,
			GET_SET, PRESENT_TEMPERATURE));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::intermediateSetTemperatureOffset(unsigned char temperatureOffset, TemperatureUnits units)
{
	return queueRequest(new SetTemperatureOffset(temperatureOffset, units));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::intermediateSetSetpoints(unsigned short deviceType, TemperatureUnits units, unsigned short setpoint1, unsigned short setpoint2)
{
	return queueRequest(new SetSetpoints(deviceType, units, setpoint1, setpoint2));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::intermediateSetEnergyPrice(unsigned short currentPrice, unsigned short currencyCode,
		unsigned char digitsAfterDecimalPoint, unsigned int expirationDatetimeUTC,
		unsigned short nextPrice)
{
	return queueRequest(new SetEnergyPrice(currentPrice, currencyCode, digitsAfterDecimalPoint, expirationDatetimeUTC,
			nextPrice));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::intermediateStartCycling(unsigned int eventID, unsigned int startTimeUTCSince2000, unsigned short durationInMinutes,
		unsigned char dutyCycle, unsigned char startRandomizationMinutes, unsigned char endRandomizationMintues,
		unsigned char criticality)
{
	return queueRequest(new StartCycling(eventID, startTimeUTCSince2000, durationInMinutes,
			dutyCycle, startRandomizationMinutes, endRandomizationMintues, criticality));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::intermediateTerminateCycling(unsigned int eventID, unsigned char endRandomizationInMinutes)
{
	return queueRequest(new TerminateCycling(eventID, endRandomizationInMinutes));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::basicCriticalPeakEvent(unsigned char eventDuration)
{
	return queueRequest(new Basic(MessageCode::BASIC_CRITICAL_PEAK_EVENT_REQUEST,
			CPP, eventDuration));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::basicEndShed(unsigned char durationToNextEvent)
{
	return queueRequest(new Basic(MessageCode::BASIC_END_SHED_REQUEST,
			END_SHED, durationToNextEvent));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::basicGridEmergency(unsigned char eventDuration)
{
	return queueRequest(new Basic(MessageCode::BASIC_GRID_EMERGENCY_REQUEST,
			GRID_EMERGENCY, eventDuration));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::basicLoadUp(unsigned char eventDuration)
{
	return queueRequest(new Basic(MessageCode::BASIC_LOAD_UP_REQUEST,
			LOADUP, eventDuration));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::basicOutsideCommConnectionStatus(OutsideCommuncatonStatusCode code)
{
	return queueRequest(new Basic(MessageCode::BASIC_OUTSIDE_COMM_CONNECTION_STATUS_MESSAGE,
			COMM_STATUS, (unsigned char)code));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::basicPresentRelativePrice(unsigned char relativePriceIndicator)
{
	return queueRequest(new Basic(MessageCode::BASIC_PRESENT_RELATIVE_PRICE_REQUEST,
			PRESENT_RELATIVE_PRICE, relativePriceIndicator));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::basicNextRelativePrice(unsigned char relativePriceIndicator)
{
	return queueRequest(new Basic(MessageCode::BASIC_NEXT_RELATIVE_PRICE_REQUEST,
			NEXT_RELATIVE_PRICE, relativePriceIndicator));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::basicQueryOperationalState()
{
	return queueRequest(new Basic(MessageCode::BASIC_QUERY_OPERATIONAL_STATE_REQUEST,
			OPER_STATE_REQ, CLEAR_OP_CODE2));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::basicShed(unsigned char eventDuration)
{
	return queueRequest(new Basic(MessageCode::BASIC_SHED_REQUEST,
			SHED, eventDuration));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::basicPowerLevel(unsigned char powerLevel)
{
	return queueRequest(new Basic(MessageCode::BASIC_POWER_LEVEL,
			POWER_LEVEL, powerLevel));
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::queryMaxPayload()
{
    combined_client_->Post("DTM", xml_writer_.WriteMsg("DCM", "DER", "QueryMaxPayload", "na", "querying max payload"));
	return CEA2045Device::queryMaxPayload();
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::queryMessageTypeSupported(MessageCode messageCode, unsigned char messageType1, unsigned char messageType2)
{
    combined_client_->Post("DTM", xml_writer_.WriteMsg("DCM", "DER", "QueryMsgTypeSupported", "na", "querying message type supported"));
	return CEA2045Device::queryMessageTypeSupported(messageCode, messageType1, messageType2);
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::querySuportDataLinkMessages()
{
    combined_client_->Post("DTM", xml_writer_.WriteMsg("DCM", "DER", "QuerySupportDataLinkMsgs", "na", "querying support of data link messages"));
	return CEA2045Device::querySuportDataLinkMessages();
}

//======================================================================================

std::future<ResponseCodes> ECS_CEA2045DeviceUCM::querySuportIntermediateMessages()
{
    combined_client_->Post("DTM", xml_writer_.WriteMsg("DCM", "DER", "QuerySupportIntermediateMsgs", "na", "querying support of intermediate messages"));
	return CEA2045Device::querySuportIntermediateMessages();
}

//======================================================================================

bool ECS_CEA2045DeviceUCM::start()
{
	return CEA2045Device::start();
}

//======================================================================================

void ECS_CEA2045DeviceUCM::shutDown()
{
	return CEA2045Device::shutDown();
}

} // namespace dcm