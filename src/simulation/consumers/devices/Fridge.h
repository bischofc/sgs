#ifndef simulation_endpoint_consumer_fridge_h
#define simulation_endpoint_consumer_fridge_h

#include "energy/plans/EnergyPlanInfinitePeriod.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Fridge : public Consumer {

public:
  Fridge(std::string consumerId) : Consumer(consumerId){
    double energy = 0;
    int intervall = config::EnergyPlan::convertTime(1);
    int runtime = config::EnergyPlan::convertTime(0,10);
    int runtimeVariation = config::EnergyPlan::convertTime(0,10);

    double rand = helper::RandomNumbers::getRandom();
    if(rand < 0.25) energy = config::EnergyPlan::getEnergyFromWattage(80);
    else if(rand < 0.8) energy = config::EnergyPlan::getEnergyFromWattage(100);
    else energy = config::EnergyPlan::getEnergyFromWattage(170);

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanInfinitePeriod(intervall, runtime, 0, energy, runtimeVariation)));
  }

  virtual ~Fridge() {}
};

}}} /* End of namespaces */

#endif
