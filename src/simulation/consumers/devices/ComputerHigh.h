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
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Endtime;
    int variation = config::EnergyPlan::convertTime(0,15);

    start = config::EnergyPlan::convertTime(12,30);
    end = config::EnergyPlan::convertTime(13,30);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, end, energy, variation, variation)));

    start = config::EnergyPlan::convertTime(17,0);
    end = config::EnergyPlan::convertTime(20,0);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(day, ttype, start, end, energy, variation, variation)));
  }

  virtual ~ComputerHigh() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_computerHigh_h
