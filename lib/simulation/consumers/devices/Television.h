#ifndef simulation_endpoint_consumer_television_h
#define simulation_endpoint_consumer_television_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Television : public Consumer {

 public:
  Television(std::string consumerId) : Consumer(consumerId) {
    int start, end;
    double energy = config::EnergyPlan::getEnergyFromWattage(200);

    start = config::EnergyPlan::convertTime(18,30);
    end = config::EnergyPlan::convertTime(22,30);
    addEnergyPlan(new config::EnergyPlanStatic(start, end, energy));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_television_h
