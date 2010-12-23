#ifndef simulation_endpoint_consumer_light_h
#define simulation_endpoint_consumer_light_h

#include "EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Light : public Consumer {

public:
  Light(std::string consumerId) : Consumer(consumerId) {
    int energy = config::EnergyPlan::getEnergyFromWattage(2000);

    addEnergyPlan(new config::EnergyPlanStatic(390, 450, energy));
    addEnergyPlan(new config::EnergyPlanStatic(1020, 1350, energy));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_light_h
