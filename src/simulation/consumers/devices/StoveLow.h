#ifndef simulation_endpoint_consumer_stove_low_h
#define simulation_endpoint_consumer_stove_low_h

#include "energy/plans/EnergyPlanSelective.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class StoveLow : public Consumer {

 public:
  StoveLow(std::string consumerId) : Consumer(consumerId) {
    int start, timeVar;
    double energy = config::EnergyPlan::getEnergyFromWattage(2500);
    int duration = config::EnergyPlan::convertTime(0,27);
    int durationVariation = config::EnergyPlan::convertTime(0,15);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    double rand = helper::RandomNumbers::getRandom();
    if(rand < 0.75) {
      start = config::EnergyPlan::convertTime(18,30);
      timeVar = config::EnergyPlan::convertTime(4);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, timeVar, durationVariation)));
    }
    if(rand > 0.5) {
      start = config::EnergyPlan::convertTime(13);
      timeVar = config::EnergyPlan::convertTime(3);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, timeVar, durationVariation)));
    }
  }

  virtual ~StoveLow() {}
};

}}} /* End of namespaces */

#endif
