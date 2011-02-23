#ifndef simulation_endpoint_consumer_dishwasher_mid_h
#define simulation_endpoint_consumer_dishwasher_mid_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class DishwasherMid : public Consumer {

public:
  DishwasherMid(std::string consumerId) : Consumer(consumerId) {
    int start;
    double energy = config::EnergyPlan::getEnergyFromWattage(300);
    int duration = config::EnergyPlan::convertTime(2,25);
    int startVariation = config::EnergyPlan::convertTime(2);
    int durationVariation = config::EnergyPlan::convertTime(0,30);
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;
    config::EnergyPlan::Runtimes day;

    double rand = helper::RandomNumbers::getRandom();
    if(rand < 0.5) start = config::EnergyPlan::convertTime(12);
    else start = config::EnergyPlan::convertTime(17,00);

    if(helper::RandomNumbers::getRandom(0, 1))
      day = (config::EnergyPlan::Runtimes) (config::EnergyPlan::Mon | config::EnergyPlan::Wed | config::EnergyPlan::Fri | config::EnergyPlan::Sun);
    else
      day = (config::EnergyPlan::Runtimes) (config::EnergyPlan::Tue | config::EnergyPlan::Thu | config::EnergyPlan::Sat);

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation, durationVariation)));
  }

  virtual ~DishwasherMid() {}
};

}}} /* End of namespaces */

#endif
