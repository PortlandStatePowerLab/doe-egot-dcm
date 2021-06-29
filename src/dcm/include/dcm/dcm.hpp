#ifndef __DCM_H__
#define __DCM_H__
#include <memory>

#include <https/combined_client.hpp>
#include <sep/models.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <ecs/sim_module.hpp>
#include 


class DCM
{
public:
    DCM(/* args */);
    ~DCM();
private:
    std::shared_ptr<flecs::world> ecs_;
    std::shared_ptr<CombinedHttpsClient> https_;
    std::
};

#endif // __DCM_H__