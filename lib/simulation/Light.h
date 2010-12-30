#ifndef simulation_endpoint_consumer_light_h
#define simulation_endpoint_consumer_light_h

#include "EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Light : public Consumer {

public:
  Light(std::string consumerId) : Consumer(consumerId) {
    double energy = config::EnergyPlan::getEnergyFromWattage(1000); //realistisch 200

    addEnergyPlan(new config::EnergyPlanStatic(390, 450, energy));
    addEnergyPlan(new config::EnergyPlanStatic(1020, 1350, energy));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_light_h
