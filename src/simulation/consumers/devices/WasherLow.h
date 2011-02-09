#ifndef simulation_endpoint_consumer_washer_low_h
#define simulation_endpoint_consumer_washer_low_h

#include "energy/plans/EnergyPlanSelective.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class WasherLow : public Consumer {

 public:
  WasherLow(std::string consumerId) : Consumer(consumerId) {
    double energy = config::EnergyPlan::getEnergyFromWattage(450);
    int start = config::EnergyPlan::convertTime(12);
    int startVariation = config::EnergyPlan::convertTime(8);
    int duration = config::EnergyPlan::convertTime(3);
    int durationVariation = config::EnergyPlan::convertTime(1);
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    config::EnergyPlan::Runtimes day;

    if(helper::RandomNumbers::getRandom() < 0.5) day = config::EnergyPlan::Sat;
    else day = config::EnergyPlan::Sun;
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation, durationVariation)));
  }

  virtual ~WasherLow() {}
};

}}} /* End of namespaces */

#endif
