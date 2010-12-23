#ifndef simulation_endpoint_consumer_television_h
#define simulation_endpoint_consumer_television_h

#include "EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Television : public Consumer {

 public:
  Television(std::string consumerId) : Consumer(consumerId) {
    int energy = config::EnergyPlan::getEnergyFromWattage(200);

    addEnergyPlan(new config::EnergyPlanStatic(1110, 1350, energy));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_television_h
