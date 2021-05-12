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
            world_.import<der_simulator_module>();
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

            } 
        }
        void PrintSimpleDERImportEnergy()
        {
            auto q = world_.query<der::der_simulator_module::SimpleDER>();
            q.each(
                [](flecs::entity e, der::der_simulator_module::SimpleDER& d)
                {
                    std::cout << "available import energy: " << int(d.available_import_energy) << " Wh ";
                }
            ); 
        }
        std::string ImportEnergy()
        {
            //auto e = world_.lookup("m_sim_der_1");
            auto q = world_.query<der_simulator_module::DERSimulatorEntityTag, der_simulator_module::CurrentActiveCommand>();
            q.each(
                [](flecs::entity e, der_simulator_module::DERSimulatorEntityTag& t, der_simulator_module::CurrentActiveCommand& c)
                {
                    if (c != der_simulator_module::CurrentActiveCommand::kImportEnergyCommand)
                    {
                        c = der_simulator_module::CurrentActiveCommand::kImportEnergyCommand;
                        return "ImportEnergy Ack"
                    }
                    else
                    {
                        return "ImportEnergy Nack, already importing"
                    }
                }
            ); 
        }
        std::string ExportEnergy()
        {
            //auto e = world_.lookup("m_sim_der_1");
            auto q = world_.query<der_simulator_module::DERSimulatorEntityTag, der_simulator_module::CurrentActiveCommand>();
            q.each(
                [](flecs::entity e, der_simulator_module::DERSimulatorEntityTag& t, der_simulator_module::CurrentActiveCommand& c)
                {
                    if (c != der_simulator_module::CurrentActiveCommand::kExportEnergyCommand)
                    {
                        c = der_simulator_module::CurrentActiveCommand::kExportEnergyCommand;
                        return "ExportEnergy Ack"
                    }
                    else
                    {
                        return "ExportEnergy Nack, already exporting"
                    }
                }
            ); 
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
            auto q = world_.query<der::der_simulator_module::SimpleDER>();
            q.each(
                [&import_e, &export_e](flecs::entity e, der::der_simulator_module::SimpleDER& d)
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
            //
        }
        std::string Idle()
        {
            //auto e = world_.lookup("m_sim_der_1");
            auto q = world_.query<der_simulator_module::DERSimulatorEntityTag, der_simulator_module::CurrentActiveCommand>();
            q.each(
                [](flecs::entity e, der_simulator_module::DERSimulatorEntityTag& t, der_simulator_module::CurrentActiveCommand& c)
                {
                    if (c != der_simulator_module::CurrentActiveCommand::kNoCommand)
                    {
                        c = der_simulator_module::CurrentActiveCommand::kINoCommand;
                        return "Idle Ack"
                    }
                    else
                    {
                        return "Idle Nack, already idle"
                    }
                }
            ); 
        }

    protected:
        flecs::world world_;
};
} // namespace der
#endif //__DER_SIMULATOR_H__