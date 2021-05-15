#ifndef __DER_SIMULATOR_H__
#define __DER_SIMULATOR_H__

#include <flecs.h>
#include "der_sim_module.hpp"

namespace der
{

class DERSimulator 
{
    public:

        DERSimulator()
        {
            std::cout << "DERSimulator Default Constructor... importing der sim module..." << std::endl;
            world_.import<der_simulator_module>();
            world_.progress();
        }

        ~DERSimulator() {}

        void TestRun()
        {
            int mins = 0;
            std::cout << "DERSimulator::TestRun" << std::endl;
            std::cout << "How many minutes would you like to simulate?" << std::endl;
            std::cin >> mins;
            srand(mins); //seed rand() generator 

            //world_.set_target_fps(1);
            for (int i = 0; i < mins; i++)
            {
                for (int i = 0; i < 60; i++)
                {
                    world_.progress();
                } 
                if (i % 5 == 0) //only print incrementally
                {
                    std::cout <<" Minute " << i << ": ";
                    //PrintSimpleDERImportEnergy();
                    std::cout << GetEnergy() << std::endl;
                    std::cout << std::endl;
                }
                if (i == 250)
                {

                    ExportEnergy();
                }
                if (i == 500)
                {
                    ImportEnergy();
                }
            } 
        }

        void PrintSimpleDERImportEnergy()
        {
            auto q = world_.query<der::der_components::SimpleDER>();
            q.each(
                [](flecs::entity e, der::der_components::SimpleDER& d)
                {
                    std::cout << "available import energy: " << int(d.available_import_energy) << " Wh ";
                }
            ); 
        }

        std::string ImportEnergy()
        {
            std::string response = " der simulator error ";
            auto q = world_.query<der_components::DERSimulatorEntityTag, der_components::CurrentActiveCommand>();
            q.each(
                [&response](flecs::entity e, der_components::DERSimulatorEntityTag& t, der_components::CurrentActiveCommand& c)
                {
                    if (c != der_components::CurrentActiveCommand::kImportEnergyCommand)
                    {
                        c = der_components::CurrentActiveCommand::kImportEnergyCommand;
                        response =  "Ack";
                    }
                    else
                    {
                        response =  "Nack";
                    }
                }
            ); 
            return response;
        }

        std::string ExportEnergy()
        {
            std::string response;
            auto q = world_.query<der_components::DERSimulatorEntityTag, der_components::CurrentActiveCommand>();
            q.each(
                [&response](flecs::entity e, der_components::DERSimulatorEntityTag& t, der_components::CurrentActiveCommand& c)
                {
                    if (c != der_components::CurrentActiveCommand::kExportEnergyCommand)
                    {
                        c = der_components::CurrentActiveCommand::kExportEnergyCommand;
                        response =  "ExportEnergy Ack";
                    }
                    else
                    {
                        response =  "ExportEnergy Nack, already exporting";
                    }
                }
            ); 
            return response;
        }

        std::string GetPower()
        {
            return "import: 4500 Wh";
        }

        std::string GetEnergy()
        {
            /*
            auto e = world_.lookup("m_sim_der_1");
            const der_simulator_module::SimpleDER* der = e.get<der_simulator_module::SimpleDER>();
            double import = der->available_import_energy;
            std::string response = "Available import energy: ";
            response += std::to_string(import) + " Wh";
            return response;
            */
            double import_e, export_e;
            auto q = world_.query<der::der_components::SimpleDER>();
            q.each(
                [&import_e, &export_e](flecs::entity e, der::der_components::SimpleDER& d)
                {
                    import_e = d.available_import_energy;
                    export_e = d.available_export_energy;
                }
            ); 
            std::string response = "import: ";
            response += std::to_string( int(import_e) ) + " Wh, export: " + std::to_string( int(export_e) ) + " Wh";
            return response;
        }

        std::string GetNameplate()
        {
            //whatever lol
            return "Power 4500 Watts, Max Export Energy 2100 Wh, Max Import Energy 4500 Wh ";
        }

        std::string Idle()
        {
            std::string response;
            auto q = world_.query<der_components::DERSimulatorEntityTag, der_components::CurrentActiveCommand>();
            q.each(
                [&response](flecs::entity e, der_components::DERSimulatorEntityTag& t, der_components::CurrentActiveCommand& c)
                {
                    if (c != der_components::CurrentActiveCommand::kNoCommand)
                    {
                        c = der_components::CurrentActiveCommand::kNoCommand;
                        response =  "Idle Ack";
                    }
                    else
                    {
                        response =  "Idle Nack, already idle";
                    }
                }
            ); 
            return response;
        }
        // This function to allow synchronization with another flecs::world
        void IncrementProgress()
        {
            world_.progress(); 
        }
        
    protected:

        flecs::world world_;
};

} // namespace der
#endif //__DER_SIMULATOR_H__