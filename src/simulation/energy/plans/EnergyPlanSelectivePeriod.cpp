#include "EnergyPlanSelectivePeriod.h"
#include "Simulation.h"

namespace simulation {
namespace config {

boost::shared_ptr<Logger> EnergyPlanSelectivePeriod::logger;

EnergyPlanSelectivePeriod::EnergyPlanSelectivePeriod(Runtimes runtimes, TimeType ttype, int start, int time, int period, int highTime, double lowEnergy, double highEnergy, int maxStartVariation, int maxTimeVariation, int maxHighTimeVariation) {
  if(!logger) logger = Logger::getInstance("simulation.log");

  // sanity check
  if(highTime + maxHighTimeVariation/2 > period || highTime - maxHighTimeVariation/2 < 0) throw exception::EnergyException("maxHighTimeVariation too large: check device");
  //... TODO: mehr

  // setup
  this->runtimes = runtimes;
  this->ttype = ttype;
  this->start = start;
  this->time = time;
  this->period = period;
  this->highTime = highTime;
  this->lowEnergy = lowEnergy;
  this->highEnergy = highEnergy;
  this->maxStartVariation = maxStartVariation;
  this->maxTimeVariation = maxTimeVariation;
  this->maxHighTimeVariation = maxHighTimeVariation;

  this->currentEnergy = 0;
  this->startVariation = getVariation(maxStartVariation);
  this->highTimeVariation = getVariation(maxHighTimeVariation);
  this->timeVariation = getVariation(maxTimeVariation);
  this->nextEventTime = getTimeInWeekForDay(getFirstDayInRunTimes(runtimes)) + start + startVariation;
}

double EnergyPlanSelectivePeriod::getCurrentEnergy() {
  if(Simulation::getTime() == nextEventTime) {
    updateState();
  }
  return currentEnergy;
}

// update nextEventTime and currentEnergy
void EnergyPlanSelectivePeriod::updateState() {
  int simulationTime = Simulation::getTime();

  if(getDayOfTheWeek() & runtimes) {
    int currTime = getTimeOnCurrentDay();
    int localEnd = (ttype == EnergyPlan::Duration) ? start + startVariation + time + timeVariation : time + timeVariation;
    int nextEnd = (simulationTime - currTime) + localEnd;

    // at and after end
    if(currTime >= localEnd) {
      currentEnergy = 0;
      startVariation = getVariation(maxStartVariation);
      nextEventTime = getAbsTimeOfNextRuntimeDay(runtimes) + start + startVariation;
      timeVariation = getVariation(maxTimeVariation);

    // before start
    } else if(currTime < start + startVariation) {
      currentEnergy = 0;
      nextEventTime = (simulationTime - currTime) + start + startVariation;

    // at start or beginning of period
    } else {
      int periodTime = (currTime - start - startVariation) % period;
      int tmp;

      // at start or beginning of period
      if(periodTime < highTime + highTimeVariation) {
        currentEnergy = highEnergy;
        tmp = (simulationTime - periodTime) + highTime + highTimeVariation;

      // in period after highTime
      } else {
        currentEnergy = lowEnergy;
        tmp = (simulationTime - periodTime) + period;
        highTimeVariation = getVariation(maxHighTimeVariation);
      }
      nextEventTime = (nextEnd < tmp) ? nextEnd : tmp;
    }
  }
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
