#ifndef simulation_endpoint_consumer_washer_h
#define simulation_endpoint_consumer_washer_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Washer : public Consumer {

 public:
  Washer(std::string consumerId) : Consumer(consumerId) {
    int start, duration, period;
    double energy = config::EnergyPlan::getEnergyFromWattage(450);

    start = config::EnergyPlan::convertTime(134);                               // TODO Zur richtigen Zeit anschalten (momentan läuft es ab Beginn)
    duration = config::EnergyPlan::convertTime(2);
    period = config::EnergyPlan::convertTime(168);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(-1, -1, period, duration, 0, energy)));
  }

  virtual ~Washer() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_washer_h
