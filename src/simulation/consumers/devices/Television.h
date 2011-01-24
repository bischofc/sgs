#ifndef simulation_endpoint_consumer_television_h
#define simulation_endpoint_consumer_television_h

#include "energy/plans/EnergyPlanStatic.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Television : public Consumer {

 public:
  Television(std::string consumerId) : Consumer(consumerId) {
    int start, end;
    double energy = config::EnergyPlan::getEnergyFromWattage(100);

    start = config::EnergyPlan::convertTime(18,30,30);
    end = config::EnergyPlan::convertTime(22,30,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(start, end, energy)));
  }

  virtual ~Television() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_television_h
