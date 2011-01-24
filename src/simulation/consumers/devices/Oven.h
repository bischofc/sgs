#ifndef simulation_endpoint_consumer_oven_h
#define simulation_endpoint_consumer_oven_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Oven : public Consumer {

 public:
  Oven(std::string consumerId) : Consumer(consumerId) {
    int start, duration, period;
    double energy = config::EnergyPlan::getEnergyFromWattage(2000);

    start = config::EnergyPlan::convertTime(132);                               // TODO Zur richtigen Zeit anschalten (momentan läuft es ab Beginn)
    duration = config::EnergyPlan::convertTime(0,30);
    period = config::EnergyPlan::convertTime(168);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(-1, -1, period, duration, 0, energy)));
  }

  virtual ~Oven() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_oven_h
