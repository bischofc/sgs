#ifndef simulation_endpoint_consumer_kettle_h
#define simulation_endpoint_consumer_kettle_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Kettle : public Consumer {

 public:
  Kettle(std::string consumerId) : Consumer(consumerId) {
    int start, startVariation;
    double energy = config::EnergyPlan::getEnergyFromWattage(2000);
    int duration = config::EnergyPlan::convertTime(0,3);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    start = config::EnergyPlan::convertTime(7,0);
    startVariation = config::EnergyPlan::convertTime(0,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation)));

    start = config::EnergyPlan::convertTime(18,30);
    startVariation = config::EnergyPlan::convertTime(1);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation)));
  }

  virtual ~Kettle() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_kettle_h
