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

    private:

        CombinedHttpsClient * https_client_;
        BaseReceiver * receiver_;

};

class ImportEnergy : public BaseCommand
{
    public:

        ImportEnergy() {}
        ImportEnergy(CombinedHttpsClient * c, BaseReceiver * r) : BaseCommand(c, r) 
        {std::cout << "ImportEnergy Command Constructed " << std::endl;}
        ~ImportEnergy() 
        {}
        std::string Execute() {}

    private:
};

class ExportEnergy : public BaseCommand
{
    public:

        ExportEnergy() {}
        ExportEnergy(CombinedHttpsClient * c, BaseReceiver * r) : BaseCommand(c, r) {}
        ~ExportEnergy() 
        {}
        std::string Execute() {}

    private:
};

class GetEnergy : public BaseCommand
{
    public:

        GetEnergy() {}
        GetEnergy(CombinedHttpsClient * c, BaseReceiver * r) : BaseCommand(c, r) {}
        ~GetEnergy() {}
        std::string Execute() {}

    private:
};

class GetNameplate : public BaseCommand
{
    public:

        GetNameplate() {}
        GetNameplate(CombinedHttpsClient * c, BaseReceiver * r) : BaseCommand(c, r) {}
        ~GetNameplate() {}
        std::string Execute() {}

    private:
};

class Idle : public BaseCommand
{
    public:

        Idle() {}
        Idle(CombinedHttpsClient * c, BaseReceiver * r) : BaseCommand(c, r) {}
        ~Idle() {}
        std::string Execute() {}

    private:
};

} // namespace dcm

#endif //__DCM_COMMANDS_H__