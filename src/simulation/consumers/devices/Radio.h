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

    start = config::EnergyPlan::convertTime(7,0,15);
    duration = config::EnergyPlan::convertTime(0,30,20);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(start, start+duration, energy)));

    start = config::EnergyPlan::convertTime(11,0,15);
    duration = config::EnergyPlan::convertTime(0,30,20);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(start, start+duration, energy)));
  }

  virtual ~Radio() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_radio_h
