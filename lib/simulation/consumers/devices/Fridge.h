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
    int intervall = config::EnergyPlan::convertTime(1);
    int runtime = config::EnergyPlan::convertTime(0,10);

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(-1, -1, intervall, runtime, 0, energy)));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_fridge_h
