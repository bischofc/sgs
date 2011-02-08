#ifndef simulation_endpoint_consumer_television_h
#define simulation_endpoint_consumer_television_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Television : public Consumer {

 public:
  Television(std::string consumerId) : Consumer(consumerId) {
    int start, end, variation;
    double energy = config::EnergyPlan::getEnergyFromWattage(100);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Endtime;

    start = config::EnergyPlan::convertTime(18,30);
    end = config::EnergyPlan::convertTime(22,30);
    variation = config::EnergyPlan::convertTime(0,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, end, energy, variation, variation)));
  }

  virtual ~Television() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_television_h
