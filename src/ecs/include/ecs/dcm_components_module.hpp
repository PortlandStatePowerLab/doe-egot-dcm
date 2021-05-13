#ifndef __DCM_COMPONENTS_MODULE_H__
#define __DCM_COMPONENTS_MODULE_H__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <flecs.h>
#include "der_sim_module.hpp"
#include "der_components_module.hpp"

namespace dcm
{
class dcm_components_module
{
    public:

        dcm_components_module(flecs::world& world_) 
        {
            //Register module with world 
            world_.module<dcm_components_module>();
            world_.import<der::der_components>();
        }
};


} // namespace dcm


#endif // __DCM_COMPONENTS_MODULE_H__
