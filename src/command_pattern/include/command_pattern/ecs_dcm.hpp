#ifndef __ECS_DCM_H__
#define __ECS_DCM_H__
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <flecs.h>
#include <sstream>
#include <https/https_client.hpp>
#include <https/combined_client.hpp>
#include <sep/models.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include "s_sim_invoker.hpp"

namespace dcm
{

class ECS_DCM 
{
    public:

        ECS_DCM() {}
        ~ECS_DCM() 
        {
            
        }
        void SetReceiver()
        {
            // imaginary comms tests, or pre-defined binary init
            receiver_ = new SimpleSimulatorReceiver;
        }
    
    private:

        flecs::world dcm_world_;
        BaseReceiver * receiver_;
        //BaseInvoker * sim_invoker_;


};

} //namespace dcm
#endif //__ECS_DCM_H__