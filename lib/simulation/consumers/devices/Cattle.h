#ifndef simulation_endpoint_consumer_cattle_h
#define simulation_endpoint_consumer_cattle_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Cattle : public Consumer {

 public:
  Cattle(std::string consumerId) : Consumer(consumerId) {
    int start, end;
    double energy = config::EnergyPlan::getEnergyFromWattage(2000);

    start = config::EnergyPlan::convertTime(7);
    end = config::EnergyPlan::convertTime(7,3);
    addEnergyPlan(new config::EnergyPlanStatic(start, end, energy));

    start = config::EnergyPlan::convertTime(18,30);
    end = config::EnergyPlan::convertTime(18,33);
    addEnergyPlan(new config::EnergyPlanStatic(start, end, energy));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_cattle_h
