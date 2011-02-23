#ifndef simulation_endpoint_consumer_oven_h
#define simulation_endpoint_consumer_oven_h

#include "energy/plans/EnergyPlanSelective.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Oven : public Consumer {

 public:
  Oven(std::string consumerId) : Consumer(consumerId) {
    double energy = config::EnergyPlan::getEnergyFromWattage(2000);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::getRandomDayOfWeek();
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;
    int startVariation = config::EnergyPlan::convertTime(2);
    int durationVariation = config::EnergyPlan::convertTime(0,45);
    int duration = config::EnergyPlan::convertTime(1,15);

    int start;
    if(helper::RandomNumbers::getRandom() < 0.5) start = config::EnergyPlan::convertTime(12);
    else start = config::EnergyPlan::convertTime(17);

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation, durationVariation)));
  }

  virtual ~Oven() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_oven_h
