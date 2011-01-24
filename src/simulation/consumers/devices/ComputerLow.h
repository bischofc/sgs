#ifndef simulation_endpoint_consumer_computerLow_h
#define simulation_endpoint_consumer_computerLow_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class ComputerLow : public Consumer {

 public:
  ComputerLow(std::string consumerId) : Consumer(consumerId) {
    int start;
    double energy = config::EnergyPlan::getEnergyFromWattage(150);
    int duration = config::EnergyPlan::convertTime(0,30,15);

    start = config::EnergyPlan::convertTime(18,30,60);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(start, start+duration, energy)));
  }

  virtual ~ComputerLow() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_computerLow_h
