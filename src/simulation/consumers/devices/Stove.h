#ifndef simulation_endpoint_consumer_stove_h
#define simulation_endpoint_consumer_stove_h

#include "energy/plans/EnergyPlanStatic.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Stove : public Consumer {

 public:
  Stove(std::string consumerId) : Consumer(consumerId) {
    int start;
    double energy = config::EnergyPlan::getEnergyFromWattage(2500);
    int duration = config::EnergyPlan::convertTime(0,30,10);

    if(helper::RandomNumbers::getRandom() > 0.75) {
      start = config::EnergyPlan::convertTime(12,0,30);
    } else {
      start = config::EnergyPlan::convertTime(18,0,15);
    }

    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanStatic(start, start+duration, energy)));
  }

  virtual ~Stove() {}
};

}}} /* End of namespaces */

#endif // simulation_endpoint_consumer_stove_h
