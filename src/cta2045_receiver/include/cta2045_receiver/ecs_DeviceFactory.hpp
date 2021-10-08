#ifndef ECS_DEVICEFACTORY_H_
#define ECS_DEVICEFACTORY_H_

#include "ecs_CEA2045DeviceUCM.hpp"
#include "cta2045_receiver.hpp"
#include <cea2045/communicationport/ICommunicationPort.h>


namespace dcm
{
using namespace cea2045;

class ECS_DeviceFactory
{
    public:
        ECS_DeviceFactory(std::string *comm, CombinedHttpsClient * cc);
        virtual ~ECS_DeviceFactory();
        cea2045::ICEA2045DeviceUCM *createUCM(ICommunicationPort *port, IUCM *ucm);
    
    private:
        std::string *comm_log_; //no data structure to simplify/avoid rquirement for memory/clearing old data
		CombinedHttpsClient *combined_client_;
};


} // namespace dcm

#endif // ECS_DEVICEFACTORY_H_ 
