#ifndef simulation_endpoint_consumer_standby_h
#define simulation_endpoint_consumer_standby_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class StandBy : public Consumer {

 public:
  StandBy(std::string consumerId) : Consumer(consumerId) {
    double energy = config::EnergyPlan::getEnergyFromWattage(45);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(energy)));
  }

  virtual ~StandBy() {}
};

}}} /* End of namespaces */

#endif
