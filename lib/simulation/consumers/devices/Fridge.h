#ifndef simulation_endpoint_consumer_fridge_h
#define simulation_endpoint_consumer_fridge_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Fridge : public Consumer {
//  void addEnergyPlan(config::EnergyPlan *);

public:
  Fridge(std::string consumerId) : Consumer(consumerId){
    double energy = config::EnergyPlan::getEnergyFromWattage(160);

    addEnergyPlan(new config::EnergyPlanStatic(-1, -1, 60, 10, 0, energy));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_fridge_h
