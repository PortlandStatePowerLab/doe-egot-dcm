#include <ecs/der_simulator.hpp>
#include <iostream>

using namespace der;

DERSimulator::DERSimulator()
{
    world_.import<der_simulator_module>();
}
DERSimulator::~DERSimulator()
{}
void DERSimulator::TestRun()
{
    int mins = 0;
    std::cout << "DERSimulator::TestRun" << std::endl;
    std::cout << "How many minutes would you like to simulate?" << std::endl;
    std::cin >> mins;
  
    

    //world_.set_target_fps(1);
    for (int i = 0; i < mins; i++)
    {
        for (int i = 0; i < 60; i++)
        {
            world_.progress();
        } 
        std::cout <<" Minute " << i << ": ";
        PrintSimpleDERImportEnergy();
        std::cout << std::endl;

        
    
    }  
}
