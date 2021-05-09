#include <ecs/der_simulator.hpp>
#include <iostream>

using namespace der;

DERSimulator::DERSimulator()
{

}
DERSimulator::~DERSimulator()
{}
void DERSimulator::TestRun()
{
    world_.import<der_simulator_module>();
    int input = 0;
    std::cout << "DERSimulator::TestRun, type 1 to exit" << std::endl;
    
    world_.set_target_fps(1);
    while (!input) 
    {
        for (int i = 0; i < 5; i++)
        {
            world_.progress();
        }
        std::cin >> input;
        
    }
}
