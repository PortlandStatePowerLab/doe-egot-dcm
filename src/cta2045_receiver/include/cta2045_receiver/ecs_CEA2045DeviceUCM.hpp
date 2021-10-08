#ifndef ECS_CEA2045DEVICEUCM_H_
#define ECS_CEA2045DEVICEUCM_H_

#include "cta2045_receiver.hpp"

namespace dcm
{

using namespace cea2045;

class ECS_CEA2045DeviceUCM : public CEA2045Device, public ICEA2045DeviceUCM
{
	public:
		ECS_CEA2045DeviceUCM(std::unique_ptr<ILinkLayerComm> linkLyer, std::unique_ptr<IProcessMessage> processMessage, 
				std::string * comm, CombinedHttpsClient *client);
		ECS_CEA2045DeviceUCM(ILinkLayerComm *linkLyer, IProcessMessage *processMessage,
				std::string * comm, CombinedHttpsClient *client);

		virtual ~ECS_CEA2045DeviceUCM();

		std::future<ResponseCodes> intermediateGetDeviceInformation();
		std::future<ResponseCodes> intermediateGetCommodity();
		std::future<ResponseCodes> intermediateGetTemperatureOffset();
		std::future<ResponseCodes> intermediateGetSetPoint();
		std::future<ResponseCodes> intermediateGetPresentTemperature();

		std::future<ResponseCodes> intermediateSetTemperatureOffset(unsigned char temperatureOffset, TemperatureUnits units);
		std::future<ResponseCodes> intermediateSetSetpoints(unsigned short deviceType, TemperatureUnits units, unsigned short setpoint1, unsigned short setpoint2);
		std::future<ResponseCodes> intermediateSetEnergyPrice(unsigned short currentPrice, unsigned short currencyCode,
				unsigned char digitsAfterDecimalPoint, unsigned int expirationDatetimeUTC,
				unsigned short nextPrice);
		std::future<ResponseCodes> intermediateStartCycling(unsigned int eventID, unsigned int startTimeUTCSince2000, unsigned short durationInMinutes,
				unsigned char dutyCycle, unsigned char startRandomizationMinutes, unsigned char endRandomizationMintues,
				unsigned char criticality);
		std::future<ResponseCodes> intermediateTerminateCycling(unsigned int eventID, unsigned char endRandomizationInMinutes);

		std::future<ResponseCodes> basicCriticalPeakEvent(unsigned char eventDuration);
		std::future<ResponseCodes> basicEndShed(unsigned char durationToNextEvent);
		std::future<ResponseCodes> basicGridEmergency(unsigned char eventDuration);
		std::future<ResponseCodes> basicLoadUp(unsigned char eventDuration);
		std::future<ResponseCodes> basicOutsideCommConnectionStatus(OutsideCommuncatonStatusCode code);
		std::future<ResponseCodes> basicPresentRelativePrice(unsigned char relativePriceIndicator);
		std::future<ResponseCodes> basicNextRelativePrice(unsigned char relativePriceIndicator);
		std::future<ResponseCodes> basicQueryOperationalState();
		std::future<ResponseCodes> basicShed(unsigned char eventDuration);
		std::future<ResponseCodes> basicPowerLevel(unsigned char powerLevel);

		std::future<ResponseCodes> queryMaxPayload();

		std::future<ResponseCodes> queryMessageTypeSupported(MessageCode messageCode, unsigned char messageType1, unsigned char messageType2);

		std::future<ResponseCodes> querySuportDataLinkMessages();
		std::future<ResponseCodes> querySuportIntermediateMessages();

		bool start();
		void shutDown();

	private:
		cea2045::MaxPayloadLengthCode m_sgdMaxPayload;
		std::string *comm_log_; //no data structure to simplify/avoid rquirement for memory/clearing old data
		CombinedHttpsClient *combined_client_;
		xml::XMLCommandAdapter xml_writer_;
};


} // namespace dcm

#endif // ECS_CEA2045DEVICEUCM_H_