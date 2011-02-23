#ifndef simulation_endpoint_consumer_coffeemachine_low_h
#define simulation_endpoint_consumer_coffeemachine_low_h

#include "energy/plans/EnergyPlanSelective.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class CoffeemachineLow : public Consumer {

public:
  CoffeemachineLow(std::string consumerId) : Consumer(consumerId) {
    int start;
    double energy = config::EnergyPlan::getEnergyFromWattage(1000);
    int duration = config::EnergyPlan::convertTime(0,5);
    int startVariation = config::EnergyPlan::convertTime(1,30);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    start = config::EnergyPlan::convertTime(5);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation)));

    // in 20% of all households
    if(helper::RandomNumbers::getRandom() < 0.2) {
      start = config::EnergyPlan::convertTime(13,00);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation)));
    }

    // in 80% of all households
    if(helper::RandomNumbers::getRandom() < 0.8) {
      start = config::EnergyPlan::convertTime(17,00);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation)));
    }
  }

  virtual ~CoffeemachineLow() {}
};

}}} /* End of namespaces */

#endif
