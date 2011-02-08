
#ifndef simulation_config_energyPlanSelectivePeriod_h
#define simulation_config_energyPlanSelectivePeriod_h

#include "energy/EnergyPlan.h"
#include "Logger.h"

namespace simulation {
namespace config {

class EnergyPlanSelectivePeriod : public EnergyPlan {
  static boost::shared_ptr<Logger> logger;
  int nextEventTime, start, time, period, highTime, maxStartVariation, maxTimeVariation, maxHighTimeVariation;
  int startVariation, timeVariation, highTimeVariation;
  double currentEnergy, lowEnergy, highEnergy;
  Runtimes runtimes;
  TimeType ttype;

private:
  void updateState();

public:
  EnergyPlanSelectivePeriod(Runtimes runtimes, TimeType ttype, int start, int time, int period, int highTime, double lowEnergy, double highEnergy,
                  int maxStartVariation=0, int maxTimeVariation=0, int maxHighTimeVariation=0);
  double getCurrentEnergy();
  virtual ~EnergyPlanSelectivePeriod() { }
};

}} /* End of namespaces */

#endif
