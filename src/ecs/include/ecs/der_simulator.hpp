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
    protected:
        flecs::world world_;
};
} // namespace der
#endif //__DER_SIMULATOR_H__