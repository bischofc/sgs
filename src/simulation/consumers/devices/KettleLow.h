#ifndef simulation_endpoint_consumer_kettle_low_h
#define simulation_endpoint_consumer_kettle_low_h

#include "energy/plans/EnergyPlanSelective.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class KettleLow : public Consumer {

 public:
  KettleLow(std::string consumerId) : Consumer(consumerId) {
    int start;
    double energy = config::EnergyPlan::getEnergyFromWattage(2000);
    int startVariation = config::EnergyPlan::convertTime(1);
    int duration = config::EnergyPlan::convertTime(0,4);
    int durationVariation = config::EnergyPlan::convertTime(0,4);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    for(int i=0; i<helper::RandomNumbers::getRandom(1,4); i++) {
      start = config::EnergyPlan::convertTime(helper::RandomNumbers::getRandom(7,22));
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation, durationVariation)));
    }
  }

  virtual ~KettleLow() {}
};

}}} /* End of namespaces */

#endif
