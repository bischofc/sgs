#ifndef simulation_endpoint_consumer_vacuum_h
#define simulation_endpoint_consumer_vacuum_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Vacuum : public Consumer {

public:
  Vacuum(std::string consumerId) : Consumer(consumerId) {
    double energy = config::EnergyPlan::getEnergyFromWattage(helper::RandomNumbers::getRandom(300,2200));
    config::EnergyPlan::TimeType type = config::EnergyPlan::Duration;
    config::EnergyPlan::Runtimes day = config::EnergyPlan::getRandomDayOfWeek();
    int start = config::EnergyPlan::convertTime(12);
    int startVariation = config::EnergyPlan::convertTime(10);
    int duration = config::EnergyPlan::convertTime(1,5);
    int durationVariation = config::EnergyPlan::convertTime(1,50);

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, type, start, duration, energy, startVariation, durationVariation)));
  }

  virtual ~Vacuum() {}
};

}}} /* End of namespaces */

#endif
