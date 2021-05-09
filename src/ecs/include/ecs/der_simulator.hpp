#ifndef __DER_SIMULATOR_H__
#define __DER_SIMULATOR_H__

#include <flecs.h>
#include "der_sim_module.hpp"

namespace der
{
class DERSimulator 
{
    public:
        DERSimulator();
        ~DERSimulator();
        void TestRun();
        double PrintSimpleDERImportEnergy()
        {
            auto q = world_.query<der::der_simulator_module::SimpleDER>();
            q.each(
                [](flecs::entity e, der::der_simulator_module::SimpleDER& d)
                {
                    std::cout << d.available_import_energy;
                }
            ); 
        }
    protected:
        flecs::world world_;
};
} // namespace der
#endif //__DER_SIMULATOR_H__