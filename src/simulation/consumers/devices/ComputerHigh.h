#ifndef simulation_endpoint_consumer_computerHigh_h
#define simulation_endpoint_consumer_computerHigh_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class ComputerHigh : public Consumer {

 public:
  ComputerHigh(std::string consumerId) : Consumer(consumerId) {
    int start, end;
    double energy = config::EnergyPlan::getEnergyFromWattage(150);

    start = config::EnergyPlan::convertTime(12,30,15);
    end = config::EnergyPlan::convertTime(13,30,15);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(start, end, energy)));

    start = config::EnergyPlan::convertTime(17,0,15);
    end = config::EnergyPlan::convertTime(20,0,15);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(start, end, energy)));
  }

  virtual ~ComputerHigh() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_computerHigh_h
