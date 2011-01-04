#ifndef simulation_endpoint_consumer_cattle_h
#define simulation_endpoint_consumer_cattle_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Cattle : public Consumer {

 public:
  Cattle(std::string consumerId) : Consumer(consumerId) {
    double energy = config::EnergyPlan::getEnergyFromWattage(2000);

    addEnergyPlan(new config::EnergyPlanStatic(420, 423, energy));
    addEnergyPlan(new config::EnergyPlanStatic(1110, 1113, energy));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_cattle_h
