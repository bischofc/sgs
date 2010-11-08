
#ifndef ENERGYDISTRIBUTIONPLANREPEAT_H_
#define ENERGYDISTRIBUTIONPLANREPEAT_H_

#include <Simulation.h>
#include <EnergyDistributionPlan.h>
#include <RandomNumbers.h>

namespace simulation {
namespace config {

class EnergyDistributionPlanRepeat : public EnergyDistributionPlan {
  int period, highTime, lowEnergy, highEnergy;
  vector<float> highEnergyValues;

public:
  EnergyDistributionPlanRepeat(int, int, int, int);
  float getCurrentEnergy();
  virtual ~EnergyDistributionPlanRepeat() { };
};

}}

#endif /* ENERGYDISTRIBUTIONPLANREPEAT_H_ */
