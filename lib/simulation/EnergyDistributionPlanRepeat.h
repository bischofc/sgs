
#ifndef simulation_config_EnergyDistributionPlanRepeat_h
#define simulation_config_EnergyDistributionPlanRepeat_h

#include "Simulation.h"
#include "RandomNumbers.h"

namespace simulation {
namespace config {

class EnergyDistributionPlanRepeat : public EnergyDistributionPlan {
  int period, highTime, lowEnergy, highEnergy;
  vector<float> highEnergyValues;

public:
  EnergyDistributionPlanRepeat(int, int, int, int, int, int);
  float getCurrentEnergy();
  virtual ~EnergyDistributionPlanRepeat() { };
};

}}

#endif /* simulation_config_EnergyDistributionPlanRepeat_h */
