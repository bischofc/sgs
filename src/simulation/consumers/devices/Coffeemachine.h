#ifndef simulation_endpoint_consumer_coffeemachine_h
#define simulation_endpoint_consumer_coffeemachine_h

#include "energy/plans/EnergyPlanStatic.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Coffeemachine : public Consumer {

 public:
  Coffeemachine(std::string consumerId) : Consumer(consumerId) {
    int start;
    double energy = config::EnergyPlan::getEnergyFromWattage(1000);
    int duration = config::EnergyPlan::convertTime(0,5);
    int maxVariation = config::EnergyPlan::convertTime(0,30);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    start = config::EnergyPlan::convertTime(7);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, duration, energy, maxVariation)));

    start = config::EnergyPlan::convertTime(17,00);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, duration, energy, maxVariation)));

    // in 20% of all households
    if(helper::RandomNumbers::getRandom() > 0.8) {
      start = config::EnergyPlan::convertTime(13,00);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, duration, energy, maxVariation)));
    }
  }

  virtual ~Coffeemachine() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_coffeemachine_h
