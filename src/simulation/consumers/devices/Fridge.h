#ifndef simulation_endpoint_consumer_fridge_h
#define simulation_endpoint_consumer_fridge_h

#include "energy/plans/EnergyPlanStatic.h"

//TODO
#include <iostream>

namespace simulation {
namespace endpoint {
namespace consumer {

class Fridge : public Consumer {

public:
  Fridge(std::string consumerId) : Consumer(consumerId){
    double energy = config::EnergyPlan::getEnergyFromWattage(160);

    int intervall = config::EnergyPlan::convertTime(1);
    int runtime = config::EnergyPlan::convertTime(0,10);
    int runtimeVariation = config::EnergyPlan::convertTime(0,10);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(intervall, runtime, 0, energy, runtimeVariation)));
  }

  virtual ~Fridge() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_fridge_h
