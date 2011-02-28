#ifndef simulation_endpoint_consumer_dishwasher_low_h
#define simulation_endpoint_consumer_dishwasher_low_h

#include "energy/plans/EnergyPlanSelective.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class DishwasherLow : public Consumer {

public:
  DishwasherLow(std::string consumerId) : Consumer(consumerId) {
    int start;
    double energy = config::EnergyPlan::getEnergyFromWattage(300);
    int duration = config::EnergyPlan::convertTime(3);
    int startVariation = config::EnergyPlan::convertTime(2);
    int durationVariation = config::EnergyPlan::convertTime(0,30);
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    double rand = helper::RandomNumbers::getRandom();
    if(rand < 0.5) start = config::EnergyPlan::convertTime(13);
    else start = config::EnergyPlan::convertTime(19,00);

    config::EnergyPlan::Runtimes firstDay = config::EnergyPlan::shiftDay(config::EnergyPlan::Mon, helper::RandomNumbers::getRandom(0, 2));
    config::EnergyPlan::Runtimes secondDay = config::EnergyPlan::shiftDay(config::EnergyPlan::Mon, helper::RandomNumbers::getRandom(2, 4));
    config::EnergyPlan::Runtimes day = (config::EnergyPlan::Runtimes) (firstDay | secondDay);

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation, durationVariation)));
  }

  virtual ~DishwasherLow() {}
};

}}} /* End of namespaces */

#endif
