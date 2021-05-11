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
                    PrintSimpleDERImportEnergy();
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

        }
        std::string ExportEnergy()
        {

        }
        std::string GetPower()
        {
            
        }
        std::string GetEnergy()
        {
           
        }
        std::string GetNameplate()
        {
            //
        }

    protected:
        flecs::world world_;
};
} // namespace der
#endif //__DER_SIMULATOR_H__