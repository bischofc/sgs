#ifndef simulation_endpoint_consumer_computerMid_h
#define simulation_endpoint_consumer_computerMid_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class ComputerMid : public Consumer {

 public:
  ComputerMid(std::string consumerId) : Consumer(consumerId) {
    int start;
    double energy = config::EnergyPlan::getEnergyFromWattage(150);
    int duration = config::EnergyPlan::convertTime(1,30,30);

    start = config::EnergyPlan::convertTime(18);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(start, start+duration, energy)));
  }

  virtual ~ComputerMid() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_computerMid_h
