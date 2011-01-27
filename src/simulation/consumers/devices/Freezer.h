#ifndef simulation_endpoint_consumer_freezer_h
#define simulation_endpoint_consumer_freezer_h

#include "energy/plans/EnergyPlanStatic.h"

//TODO
#include <iostream>

namespace simulation {
namespace endpoint {
namespace consumer {

class Freezer : public Consumer {

public:
  Freezer(std::string consumerId) : Consumer(consumerId){
    double energy = config::EnergyPlan::getEnergyFromWattage(160);

    int intervall = config::EnergyPlan::convertTime(1);
    int runtime = config::EnergyPlan::convertTime(0,8);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(intervall, runtime, 0, energy, 8)));
  }

  virtual ~Freezer() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_freezer_h
