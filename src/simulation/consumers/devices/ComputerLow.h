#ifndef simulation_endpoint_consumer_computerLow_h
#define simulation_endpoint_consumer_computerLow_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class ComputerLow : public Consumer {

public:
  ComputerLow(std::string consumerId) : Consumer(consumerId) {
    int start, duration, startVariation, durationVariation;
    double energy = config::EnergyPlan::getEnergyFromWattage(160);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    start = config::EnergyPlan::convertTime(13,30);
    startVariation = config::EnergyPlan::convertTime(2);
    duration = config::EnergyPlan::convertTime(3);
    durationVariation = config::EnergyPlan::convertTime(1,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation, durationVariation)));

    start = config::EnergyPlan::convertTime(19);
    startVariation = config::EnergyPlan::convertTime(4);
    duration = config::EnergyPlan::convertTime(1,30);
    durationVariation = config::EnergyPlan::convertTime(1,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation, durationVariation)));
  }

  virtual ~ComputerLow() {}
};

}}} /* End of namespaces */

#endif
