#ifndef __DCM_COMMANDS_H__
#define __DCM_COMMANDS_H__

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
#include "simple_sim_receiver.hpp"
#include <dtm_msg_writer/announce_xml.h>

namespace dcm
{

class BaseCommand 
{
    public:

        BaseCommand() : https_client_(nullptr), receiver_(nullptr) {}
        BaseCommand(CombinedHttpsClient * c, BaseReceiver * r) : https_client_(c), receiver_(r)
        {}
        ~BaseCommand() 
        {
            https_client_ = nullptr;
            receiver_ = nullptr;
        }
        virtual std::string Execute() = 0;

    protected:

        CombinedHttpsClient * https_client_;
        BaseReceiver * receiver_;
        xml::XMLCommandAdapter xml_writer_;

};

class ImportEnergy : public BaseCommand
{
    public:

        ImportEnergy() {}
        ImportEnergy(CombinedHttpsClient * c, BaseReceiver * r) : BaseCommand(c, r) 
        {std::cout << "ImportEnergy Command Constructed " << std::endl;}
        ~ImportEnergy() {}
        std::string Execute() 
        {
            std::string response_from_der = "der response not supported yet";
            std::cout << "  ImportEnergy Command Executing... " << std::endl;
            
            //this is specific to a simulated receiver at this point, and not based on a particular resource. 
            std::string msg_out =  xml_writer_.ReturnCustomCommand("DER", "DCM", "ImportEnergy", "na", "na", "command");
            https_client_->PostDTM(msg_out);

            response_from_der = receiver_->Import();
            https_client_->PostDTM(response_from_der);
            
            //std::cout << "response from DER was: " << response_from_der << std::endl;
            //std::string msg_in =  xml_writer_.ReturnCustomCommand("DCM", "DER", response_from_der, "na", "na", "response");
            //https_client_->PostDTM(msg_in);

            return response_from_der;
        }

    private:
};

class ExportEnergy : public BaseCommand
{
    public:

        ExportEnergy() {}
        ExportEnergy(CombinedHttpsClient * c, BaseReceiver * r) : BaseCommand(c, r) {}
        ~ExportEnergy() {}
        std::string Execute() 
        {
            std::string response_from_der = "der response not supported yet";
            std::cout << "  ExportEnergy Command Executing... " << std::endl;
            
            //this is specific to a simulated receiver at this point, and not based on a particular resource. 
            std::string msg_out =  xml_writer_.ReturnCustomCommand("DER", "DCM", "ExportEnergy", "na", "na", "command");
            https_client_->PostDTM(msg_out);

            response_from_der = receiver_->Export();
            https_client_->PostDTM(response_from_der);

            return response_from_der;
        }

    private:
};

class GetEnergy : public BaseCommand
{
    public:

        GetEnergy() {}
        GetEnergy(CombinedHttpsClient * c, BaseReceiver * r) : BaseCommand(c, r) {}
        ~GetEnergy() {}
        std::string Execute() 
        {
            std::string response_from_der = "der response not supported yet";
            std::cout << "  GetEnergy Command Executing... " << std::endl;
            
            //this is specific to a simulated receiver at this point, and not based on a particular resource. 
            std::string msg_out =  xml_writer_.ReturnCustomCommand("DER", "DCM", "GetEnergy", "na", "na", "command");
            https_client_->PostDTM(msg_out);

            response_from_der = receiver_->GetEnergy();
            https_client_->PostDTM(response_from_der);

            return response_from_der;
        }

    private:
};

class GetNameplate : public BaseCommand
{
    public:

        GetNameplate() {}
        GetNameplate(CombinedHttpsClient * c, BaseReceiver * r) : BaseCommand(c, r) {}
        ~GetNameplate() {}
        std::string Execute() 
        {
            std::string response_from_der = "der response not supported yet";
            std::cout << "  GetNameplate Command Executing... " << std::endl;
            
            //this is specific to a simulated receiver at this point, and not based on a particular resource. 
            std::string msg_out =  xml_writer_.ReturnCustomCommand("DER", "DCM", "GetNameplate", "na", "na", "command");
            https_client_->PostDTM(msg_out);

            response_from_der = receiver_->GetNameplate();
            https_client_->PostDTM(response_from_der);

            return response_from_der;
        }

    private:
};

class Idle : public BaseCommand
{
    public:

        Idle() {}
        Idle(CombinedHttpsClient * c, BaseReceiver * r) : BaseCommand(c, r) {}
        ~Idle() {}
        std::string Execute() 
        {
            std::string response_from_der = "der response not supported yet";
            std::cout << "  Idle Command Executing... " << std::endl;
            
            //this is specific to a simulated receiver at this point, and not based on a particular resource. 
            std::string msg_out =  xml_writer_.ReturnCustomCommand("DER", "DCM", "Idle", "na", "na", "command");
            https_client_->PostDTM(msg_out);

            response_from_der = receiver_->Idle();
            https_client_->PostDTM(response_from_der);

            return response_from_der;
        }

    private:
};

} // namespace dcm

#endif //__DCM_COMMANDS_H__