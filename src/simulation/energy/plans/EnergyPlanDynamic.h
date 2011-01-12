
#ifndef simulation_config_energyPlanDynamic_h
#define simulation_config_energyPlanDynamic_h

#include "energy/EnergyPlan.h"
#include "RandomNumbers.h"

namespace simulation {
namespace config {

class EnergyPlanDynamic : public EnergyPlan {
  int start, end, period, highTime;
  double lowEnergy, highEnergy;
  vector<double> highEnergyValues;

public:
  EnergyPlanDynamic(int, int, int, int, double, double);
  double getCurrentEnergy();
};

}}

#endif /* simulation_config_energyPlanDynamic_h */
