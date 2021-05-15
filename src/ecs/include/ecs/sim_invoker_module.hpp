#ifndef __SIM_INVOKER_MODULE_H__
#define __SIM_INVOKER_MODULE_H__
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <flecs.h>
#include "der_sim_module.hpp"
#include "der_components_module.hpp"

namespace dcm
{

class sim_invoker_module
{
    
    public:

        sim_invoker_module(flecs::world& world_) 
        {
            //Register module with world 
            world_.module<sim_invoker_module>();
            //world_.import<der::der_components>();
        }
};

} //namespace dcm


#endif //__SIM_INVOKER_MODULE_H__