#ifndef simulation_endpoint_consumer_kettle_h
#define simulation_endpoint_consumer_kettle_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Kettle : public Consumer {

 public:
  Kettle(std::string consumerId) : Consumer(consumerId) {
    int start, end;
    double energy = config::EnergyPlan::getEnergyFromWattage(2000);

    start = config::EnergyPlan::convertTime(7);
    end = config::EnergyPlan::convertTime(7,3);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(start, end, energy)));

    start = config::EnergyPlan::convertTime(18,30);
    end = config::EnergyPlan::convertTime(18,33);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(start, end, energy)));
  }
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_kettle_h
