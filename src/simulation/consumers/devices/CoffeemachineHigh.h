#ifndef simulation_endpoint_consumer_coffeemachine_high_h
#define simulation_endpoint_consumer_coffeemachine_high_h

#include "energy/plans/EnergyPlanSelective.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class CoffeemachineHigh : public Consumer {

public:
  CoffeemachineHigh(std::string consumerId) : Consumer(consumerId) {
    int start;
    double energy = config::EnergyPlan::getEnergyFromWattage(1000);
    int duration = config::EnergyPlan::convertTime(0,7);
    int startVariation = config::EnergyPlan::convertTime(3);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    start = config::EnergyPlan::convertTime(3,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation)));

    start = config::EnergyPlan::convertTime(5);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation)));

    // in 15% of all households
    if(helper::RandomNumbers::getRandom() < 0.15) {
      start = config::EnergyPlan::convertTime(13);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation)));
    }

    start = config::EnergyPlan::convertTime(17,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation)));
  }

  virtual ~CoffeemachineHigh() {}
};

}}} /* End of namespaces */

#endif
