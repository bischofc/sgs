#ifndef simulation_endpoint_consumer_microwave_low_h
#define simulation_endpoint_consumer_microwave_low_h

#include "energy/plans/EnergyPlanSelective.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class MicrowaveLow : public Consumer {

 public:
  MicrowaveLow(std::string consumerId) : Consumer(consumerId) {
    int start, duration, startVariation, durationVariation;
    double energy = config::EnergyPlan::getEnergyFromWattage(1000);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    startVariation = config::EnergyPlan::convertTime(2);
    duration = config::EnergyPlan::convertTime(0,4);
    durationVariation = config::EnergyPlan::convertTime(0,4);

    if(helper::RandomNumbers::getRandom() < 0.5) start = config::EnergyPlan::convertTime(12);
    else start = config::EnergyPlan::convertTime(18);

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation, durationVariation)));
  }

  virtual ~MicrowaveLow() {}
};

}}} /* End of namespaces */

#endif
