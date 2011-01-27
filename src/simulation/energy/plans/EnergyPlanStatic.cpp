#include "EnergyPlanStatic.h"
#include "Simulation.h"

namespace simulation {
namespace config {

//TODO bei Konstruktoren sanity checks

EnergyPlanStatic::EnergyPlanStatic(double energy) {                             //TODO Energie variieren?
  init(Permanent, Off, -1, -1, -1, -1, 0, energy, 0, 0, 0);
  this->nextEventTime = 0;
}

EnergyPlanStatic::EnergyPlanStatic(int period, int highTime, double lowEnergy, double highEnergy, int maxHighTimeVariation) {
  init(Permanent, Off, -1, -1, period, highTime, lowEnergy, highEnergy, 0, 0, maxHighTimeVariation);
  this->nextEventTime = 0;

  // sanity check
  if(highTime + maxHighTimeVariation/2 >= period || highTime - maxHighTimeVariation/2 <= 0) throw exception::EnergyException("maxHighTimeVariation too large: check device");
  //... mehr
}

EnergyPlanStatic::EnergyPlanStatic(Runtimes runtimes, TimeType ttype, int start, int time, double energy, int maxStartVariation, int maxTimeVariation) {
  init(runtimes, ttype, start, time, -1, -1, 0, energy, maxStartVariation, maxTimeVariation, 0);
  this->startVariation = getVariation(maxStartVariation);
  this->nextEventTime = getTimeInWeekForDay(getFirstDayInRunTimes(runtimes)) + start + startVariation;

  // sanity check
  if(runtimes == Permanent) throw exception::EnergyException("Permanent not allowed here");
  //... mehr
}

EnergyPlanStatic::EnergyPlanStatic(Runtimes runtimes, TimeType ttype, int start, int time, int period, int highTime, double lowEnergy, double highEnergy, int maxStartVariation, int maxTimeVariation, int maxHighTimeVariation) {
  init(runtimes, ttype, start, time, period, highTime, lowEnergy, highEnergy, maxStartVariation, maxTimeVariation, maxHighTimeVariation);
  this->startVariation = getVariation(maxStartVariation);
  this->nextEventTime = getTimeInWeekForDay(getFirstDayInRunTimes(runtimes)) + start + startVariation;

  // sanity check
  if(runtimes == Permanent) throw exception::EnergyException("Permanent not allowed here");
  if(highTime + maxHighTimeVariation/2 >= period || highTime - maxHighTimeVariation/2 <= 0) throw exception::EnergyException("maxHighTimeVariation too large: check device");
  //... mehr
}

/*
 * Very first thing to be run in each constructor!
 */
void EnergyPlanStatic::init(Runtimes runtimes, TimeType ttype, int start, int time, int period, int highTime, double lowEnergy, double highEnergy, int msv, int mtv, int mhtv) {
  this->currentEnergy = 0;

  this->runtimes = runtimes;
  this->ttype = ttype;
  this->start = start;
  this->time = time;
  this->period = period;
  this->highTime = highTime;
  this->lowEnergy = lowEnergy;
  this->highEnergy = highEnergy;
  this->maxStartVariation = msv;
  this->maxTimeVariation = mtv;
  this->maxHighTimeVariation = mhtv;

  // some of these might be overwritten by the constructor
  this->startVariation = 0;
  this->highTimeVariation = getVariation(maxHighTimeVariation);
  this->timeVariation = getVariation(maxTimeVariation);
}

double EnergyPlanStatic::getCurrentEnergy() {
  if(Simulation::getTime() == nextEventTime) {
    updateState();
  }
  return currentEnergy;
}

// update nextEventTime and currentEnergy
void EnergyPlanStatic::updateState() {
  int simulationTime = Simulation::getTime();

  //// permanent
  if(runtimes == Permanent) {

    // non-periodical
    if(period <= 0) {
      currentEnergy = highEnergy;
      nextEventTime = -1;
    }

    // periodical
    else {
      int periodTime = simulationTime % period;
      if(periodTime < highTime + highTimeVariation) {
        currentEnergy = highEnergy;
        nextEventTime = simulationTime + highTime + highTimeVariation;
      } else {
        currentEnergy = lowEnergy;
        nextEventTime = simulationTime + (period - highTime - highTimeVariation);
        highTimeVariation = getVariation(maxHighTimeVariation);
      }
    }
  }

  //// non-permanent
  else {

    // non-periodical and periodical
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

        // non-periodical
        // start to right before end
        if(period <= 0) {
          currentEnergy = highEnergy;
          nextEventTime = nextEnd;
        }

        // periodical
        else {
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
  }
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
