#ifndef simulation_endpoint_consumer_radio_h
#define simulation_endpoint_consumer_radio_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Radio : public Consumer {

 public:
  Radio(std::string consumerId) : Consumer(consumerId) {
    int start, duration, startVariation, durationVariation;
    double energy = config::EnergyPlan::getEnergyFromWattage(3);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;
    startVariation = config::EnergyPlan::convertTime(0,15);
    durationVariation = config::EnergyPlan::convertTime(0,20);

    start = config::EnergyPlan::convertTime(7,0);
    duration = config::EnergyPlan::convertTime(0,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation, durationVariation)));

    start = config::EnergyPlan::convertTime(11,0);
    duration = config::EnergyPlan::convertTime(1,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, duration, energy, startVariation, durationVariation)));
  }

  virtual ~Radio() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_radio_h
