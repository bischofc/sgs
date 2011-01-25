#ifndef simulation_endpoint_consumer_radio_h
#define simulation_endpoint_consumer_radio_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Radio : public Consumer {

 public:
  Radio(std::string consumerId) : Consumer(consumerId) {
    int start, duration;
    double energy = config::EnergyPlan::getEnergyFromWattage(30);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    start = config::EnergyPlan::convertTime(7,0);
    duration = config::EnergyPlan::convertTime(0,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, duration, energy, 15, 20)));

    start = config::EnergyPlan::convertTime(11,0);
    duration = config::EnergyPlan::convertTime(0,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, duration, energy, 15, 20)));
  }

  virtual ~Radio() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_radio_h
