#ifndef __DCM_SYSTEMS_MODULE_H__
#define __DCM_SYSTEMS_MODULE_H__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <flecs.h>
#include "der_sim_module.hpp"
#include "der_components_module.hpp"
#include "dcm_components_module.hpp"

namespace dcm
{

class dcm_systems_module
{
    public:

        dcm_systems_module(flecs::world& world_) 
        {
            //Register module with world 
            world_.module<dcm_systems_module>();
            world_.import<dcm_components_module>();
        }
};


} // namespace dcm


#endif // __DCM_SYSTEMS_MODULE_H__
