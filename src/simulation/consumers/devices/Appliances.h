#ifndef simulation_endpoint_appliances_h
#define simulation_endpoint_appliances_h

#include "energy/plans/EnergyPlanSelective.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Appliances : public Consumer {

public:
  Appliances(std::string consumerId) : Consumer(consumerId) {
    int start;
    double energy = config::EnergyPlan::getEnergyFromWattage(helper::RandomNumbers::getRandom(500,2500));
    config::EnergyPlan::TimeType type = config::EnergyPlan::Duration;
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    int startVariation = config::EnergyPlan::convertTime(2,30);
    int duration = config::EnergyPlan::convertTime(3,15);
    int durationVariation = config::EnergyPlan::convertTime(4);

    // 25% do nothing, 25% only in the morning, 25% only in the evening and 25% in the morning and evening
    double rand = helper::RandomNumbers::getRandom();
    if(rand > 0.25) {
      if(rand < 0.75) {
        start = config::EnergyPlan::convertTime(8,45);
        addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, type, start, duration, energy, startVariation, durationVariation)));
      } else if(rand > 0.5) {
        start = config::EnergyPlan::convertTime(15,45);
        addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, type, start, duration, energy, startVariation, durationVariation)));
      }
    }
  }

  virtual ~Appliances() {}
};

}}} /* End of namespaces */

#endif
