#ifndef simulation_endpoint_consumer_boiler_high_h
#define simulation_endpoint_consumer_boiler_high_h

#include "energy/plans/EnergyPlanInfinitePeriod.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class BoilerHigh : public Consumer {

public:
  BoilerHigh(std::string consumerId) : Consumer(consumerId) {
    double energy = config::EnergyPlan::getEnergyFromWattage(2000);
    int period = config::EnergyPlan::convertTime(4);
    int duration = config::EnergyPlan::convertTime(0,30);
    int highTimeVariation = config::EnergyPlan::convertTime(0,10);

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanInfinitePeriod(period, duration, 0, energy, highTimeVariation)));
  }

  virtual ~BoilerHigh() {}
};

}}} /* End of namespaces */

#endif
