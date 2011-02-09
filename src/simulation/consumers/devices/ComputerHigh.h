#ifndef simulation_endpoint_consumer_computerHigh_h
#define simulation_endpoint_consumer_computerHigh_h

#include "energy/plans/EnergyPlanSelective.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class ComputerHigh : public Consumer {

public:
  ComputerHigh(std::string consumerId) : Consumer(consumerId) {
    int start, end;
    double energy = config::EnergyPlan::getEnergyFromWattage(150);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Endtime;
    int variation = config::EnergyPlan::convertTime(3);

    start = config::EnergyPlan::convertTime(15,30);
    end = config::EnergyPlan::convertTime(19);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective(day, ttype, start, end, energy, variation, variation)));
  }

  virtual ~ComputerHigh() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_computerHigh_h
