#include "EnergyPlanSelective.h"
#include "Simulation.h"

namespace simulation {
namespace config {

boost::shared_ptr<Logger> EnergyPlanSelective::logger;

EnergyPlanSelective::EnergyPlanSelective(Runtimes runtimes, TimeType ttype, int start, int time, double energy, int maxStartVariation, int maxTimeVariation) {
  if(!logger) logger = Logger::getInstance("simulation.log");

  // sanity check
  //if(runtimes == Permanent) throw exception::EnergyException("Permanent not allowed here");
  //... TODO mehr

  // setup
  this->runtimes = runtimes;
  this->ttype = ttype;
  this->start = start;
  this->time = time;
  this->highEnergy = energy;
  this->maxStartVariation = maxStartVariation;
  this->maxTimeVariation = maxTimeVariation;

  this->currentEnergy = 0;
  this->startVariation = getVariation(maxStartVariation);
  this->timeVariation = getVariation(maxTimeVariation);

  this->nextEventTime = getTimeInWeekForDay(getFirstDayInRunTimes(runtimes)) + start + startVariation;
}

double EnergyPlanSelective::getCurrentEnergy() {
  if(Simulation::getTime() == nextEventTime) {
    updateState();
  }
  return currentEnergy;
}

// update nextEventTime and currentEnergy
void EnergyPlanSelective::updateState() {
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

    // at start to right before end
    } else {
      currentEnergy = highEnergy;
      nextEventTime = nextEnd;
    }
  }
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
