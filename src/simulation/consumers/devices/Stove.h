#ifndef simulation_endpoint_consumer_stove_h
#define simulation_endpoint_consumer_stove_h

#include "energy/plans/EnergyPlanStatic.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Stove : public Consumer {

 public:
  Stove(std::string consumerId) : Consumer(consumerId) {
    int start, timeVar;
    double energy = config::EnergyPlan::getEnergyFromWattage(2500);
    int duration = config::EnergyPlan::convertTime(0,30);
    int durationVariation = config::EnergyPlan::convertTime(0,10);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    if(helper::RandomNumbers::getRandom() > 0.75) {
      start = config::EnergyPlan::convertTime(12,0);
      timeVar = config::EnergyPlan::convertTime(0,30);
    } else {
      start = config::EnergyPlan::convertTime(18,0);
      timeVar = config::EnergyPlan::convertTime(0,15);
    }

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, duration, energy, timeVar, durationVariation)));
  }

  virtual ~Stove() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_stove_h
