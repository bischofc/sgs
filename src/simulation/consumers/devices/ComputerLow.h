#ifndef simulation_endpoint_consumer_computerLow_h
#define simulation_endpoint_consumer_computerLow_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class ComputerLow : public Consumer {

public:
  ComputerLow(std::string consumerId) : Consumer(consumerId) {
    int start, startVariation, durationVariation;
    double energy = config::EnergyPlan::getEnergyFromWattage(150);
    int duration = config::EnergyPlan::convertTime(1);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    start = config::EnergyPlan::convertTime(17);
    startVariation = config::EnergyPlan::convertTime(4);
    durationVariation = config::EnergyPlan::convertTime(1,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation, durationVariation)));
  }

  virtual ~ComputerLow() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_computerLow_h
