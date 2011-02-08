#ifndef simulation_endpoint_consumer_dishwasher_high_h
#define simulation_endpoint_consumer_dishwasher_high_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class DishwasherHigh : public Consumer {

public:
  DishwasherHigh(std::string consumerId) : Consumer(consumerId) {
    int start;
    double energy = config::EnergyPlan::getEnergyFromWattage(300);
    int duration = config::EnergyPlan::convertTime(2,30);
    int startVariation = config::EnergyPlan::convertTime(1);
    int durationVariation = config::EnergyPlan::convertTime(0,30);
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;

    double rand = helper::RandomNumbers::getRandom();
    if(rand < 0.5) start = config::EnergyPlan::convertTime(13);
    else start = config::EnergyPlan::convertTime(19,00);

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation, durationVariation)));
  }

  virtual ~DishwasherHigh() {}
};

}}} /* End of namespaces */

#endif
