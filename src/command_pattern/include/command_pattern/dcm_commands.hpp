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
#include <ecs/sim_module.hpp>

class BaseCommand
{
    public:

        BaseCommand() {}
        ~BaseCommand() {}
        virtual std::string Execute() = 0;

    private:
};

class ImportEnergy : public BaseCommand
{
    public:
    
        ImportEnergy() {}
        ~ImportEnergy() {}
        std::string Execute() {}

    private:
};

class ExportEnergy : public BaseCommand
{
    public:

        ExportEnergy() {}
        ~ExportEnergy() {}
        std::string Execute() {}

    private:
};

class GetEnergy : public BaseCommand
{
    public:

        GetEnergy() {}
        ~GetEnergy() {}
        std::string Execute() {}

    private:
};

class GetNameplate : public BaseCommand
{
    public:

        GetNameplate() {}
        ~GetNameplate() {}
        std::string Execute() {}

    private:
};

#endif //__DCM_COMMANDS_H__