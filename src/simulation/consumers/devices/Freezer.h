#ifndef simulation_endpoint_consumer_freezer_h
#define simulation_endpoint_consumer_freezer_h

#include "energy/plans/EnergyPlanInfinitePeriod.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Freezer : public Consumer {

public:
  Freezer(std::string consumerId) : Consumer(consumerId) {
    double energy;
    int intervall = config::EnergyPlan::convertTime(1);
    int runtime = config::EnergyPlan::convertTime(0,8);
    int runtimeVariation = config::EnergyPlan::convertTime(0,8);

    double rand = helper::RandomNumbers::getRandom();
    if(rand < 0.25) energy = config::EnergyPlan::getEnergyFromWattage(90);
    else if(rand < 0.8) energy = config::EnergyPlan::getEnergyFromWattage(150);
    else energy = config::EnergyPlan::getEnergyFromWattage(210);

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanInfinitePeriod(intervall, runtime, 0, energy, runtimeVariation)));
  }

  virtual ~Freezer() {}
};

}}} /* End of namespaces */

#endif
