
#ifndef simulation_config_energyPlanInfinitePeriod_h
#define simulation_config_energyPlanInfinitePeriod_h

#include "energy/EnergyPlan.h"
#include "Logger.h"

namespace simulation {
namespace config {

class EnergyPlanInfinitePeriod : public EnergyPlan {
  static boost::shared_ptr<Logger> logger;
  int nextEventTime, period, highTime, offset, maxHighTimeVariation, highTimeVariation;
  double currentEnergy, lowEnergy, highEnergy;

private:
  void updateState();

public:
  EnergyPlanInfinitePeriod(int period, int highTime, double lowEnergy, double highEnergy,
                  int maxHighTimeVariation=0);
  double getCurrentEnergy();
  virtual ~EnergyPlanInfinitePeriod() { }
};

}} /* End of namespaces */

#endif
