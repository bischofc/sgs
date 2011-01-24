#ifndef simulation_endpoint_consumer_tumbler_h
#define simulation_endpoint_consumer_tumbler_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Tumbler : public Consumer {

 public:
  Tumbler(std::string consumerId) : Consumer(consumerId) {
    int start, duration, period;
    double energy = config::EnergyPlan::getEnergyFromWattage(900);

    start = config::EnergyPlan::convertTime(136);                               // TODO Zur richtigen Zeit anschalten (momentan läuft es ab Beginn)
    duration = config::EnergyPlan::convertTime(3);
    period = config::EnergyPlan::convertTime(168);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(-1, -1, period, duration, 0, energy)));
  }

  virtual ~Tumbler() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_tumbler_h
