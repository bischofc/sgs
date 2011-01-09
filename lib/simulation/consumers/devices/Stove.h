#ifndef simulation_endpoint_consumer_stove_h
#define simulation_endpoint_consumer_stove_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Stove : public Consumer {

 public:
  Stove(std::string consumerId) : Consumer(consumerId) {
    int start, end;
    double energy = config::EnergyPlan::getEnergyFromWattage(3500);

    start = config::EnergyPlan::convertTime(11);
    end = config::EnergyPlan::convertTime(11,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(start, end, energy)));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_stove_h
