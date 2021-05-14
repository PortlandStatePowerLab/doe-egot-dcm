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
#include <ecs/der_simulator.hpp>
#include <ecs/der_components_module.hpp>
#include <ecs/dcm_components_module.hpp>
#include "s_sim_invoker.hpp"

namespace dcm
{

const std::string FLOW_RESERVATION_REQUEST = R"(<?xml version="1.0" encoding="utf-8"?>
<FlowReservationRequest href="http://uri1" xmlns="urn:ieee:std:2030.5:ns">
  <mRID>0FB7</mRID>
  <description>description1</description>
  <version>0</version>
  <creationTime>1</creationTime>
  <durationRequested>0</durationRequested>
  <energyRequested>
    <multiplier>1</multiplier>
    <value>-140737488355328</value>
  </energyRequested>
  <intervalRequested>
    <duration>0</duration>
    <start>1</start>
  </intervalRequested>
  <powerRequested>
    <multiplier>1</multiplier>
    <value>1</value>
  </powerRequested>
  <RequestStatus>
    <dateTime>1</dateTime>
    <requestStatus>0</requestStatus>
  </RequestStatus>
</FlowReservationRequest>)";

class ECS_DCM 
{
    public:

        ECS_DCM() : combined_client_(nullptr), receiver_(nullptr), 
                   import_energy_c_(nullptr),  export_energy_c_(nullptr),  
                   get_energy_c_(nullptr),  get_nameplate_c_(nullptr),  
                   idle_c_(nullptr)
        {
            //SetReceiver();
            //need a program path
        }
        ECS_DCM(const std::string& root) 
        {
            std::cout << " ECS_DCM root arg overload constructor " << std::endl;
            SetReceiver();
            combined_client_ = new CombinedHttpsClient(root, "localhost", "443", root, "host.docker.internal", "8886");
            import_energy_c_ = new ImportEnergy(combined_client_, receiver_);
            export_energy_c_ = new ExportEnergy(combined_client_, receiver_);
            get_energy_c_ = new GetEnergy(combined_client_, receiver_);
            get_nameplate_c_ = new GetNameplate(combined_client_, receiver_);
            idle_c_ = new Idle(combined_client_, receiver_);
            sim_invoker_ = new SimpleSimulatorInvoker(&dcm_world_, import_energy_c_, 
                                                        export_energy_c_, get_energy_c_, 
                                                        get_nameplate_c_, idle_c_);
            dcm_world_.import<dcm::dcm_components_module>();
        }
        ~ECS_DCM() 
        {
            std::cout << "  ECS_DCM Destructor" << std::endl;
            delete combined_client_;
            delete sim_invoker_;
            delete receiver_;
            delete import_energy_c_;
            delete export_energy_c_;
            delete get_energy_c_;
            delete get_nameplate_c_;
            delete idle_c_;
            
        }
        void SetReceiver()
        {
            std::cout << " ECS_DCM::SetReceiver() " << std::endl;
            // imaginary comms tests, or pre-defined binary init
            receiver_ = new SimpleSimulatorReceiver; //emulated DER
        }
        void RunSimulatorLoop();
        void AddFlowResRespEntity(sep::FlowReservationResponse & flowresresp);
        sep::FlowReservationResponse GetFlowResRespFromGSP(sep::FlowReservationRequest & freq);
    
    private:

        flecs::world dcm_world_;
        CombinedHttpsClient * combined_client_;
        BaseInvoker * sim_invoker_;
        BaseReceiver * receiver_;
        BaseCommand * import_energy_c_;
        BaseCommand * export_energy_c_;
        BaseCommand * get_energy_c_;
        BaseCommand * get_nameplate_c_;
        BaseCommand * idle_c_;
        

        //BaseInvoker * sim_invoker_;


};

} //namespace dcm
#endif //__ECS_DCM_H__