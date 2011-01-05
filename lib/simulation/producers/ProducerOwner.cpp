#include "ProducerOwner.h"
#include "DeviceFactory.h"
#include "Simulation.h"

namespace simulation {
namespace endpoint {
namespace producer {

ProducerOwner::ProducerOwner(std::string ownerId) {
  this->nextPossibleStart = 0;
  this->id = ownerId;
  this->tooMuchEnergyCounter = 0;
}

std::string ProducerOwner::getId() {
  return 0;
}

double ProducerOwner::getEnergy() throw (exception::EnergyException) {
  double energy = 0.0;
  std::vector< Producer * >::iterator it;
  for(it = this->producerList.begin(); it != this->producerList.end(); it++) {
    energy += ((Producer *) *it)->getCurrentEnergy();
  }
  return energy;
}

void ProducerOwner::dump(std::ostringstream &out) {
  out << "    ProducerOwner-Id: " << this->id << std::endl;
  for(std::vector< Producer* >::iterator it = this->producerList.begin();
      it != this->producerList.end(); it++) {
    Producer * p = *it;
    p->dump(out);
  }
}

void ProducerOwner::addProducer(Producer * p) {
  this->producerList.push_back(p);
}

double ProducerOwner::notEnoughEnergyAction(double needed) {
  purchasedEnergy += needed;
  return needed;                                                                //TODO less or more or different?
}

void ProducerOwner::postStepAction(int energy) {
  if(energy > 40) tooMuchEnergyCounter++;                                       //TODO 40?
  else tooMuchEnergyCounter = 0;

  if(energy <= 0) addNewProducer();                                             //TODO <= x oder % oder ...

  if(producerList.size() > 1 &&
        tooMuchEnergyCounter > config::EnergyPlan::convertTime(0,30)) {         //TODO halbe stunde?
    removeProducer();
  }
}

void ProducerOwner::addNewProducer() {
  if(Simulation::getTime() > nextPossibleStart) {
    Producer * p = DeviceFactory::getProducerInstance("windmill", "asdf", false);
    addProducer(p);                                                             //TODO id generieren, muss zeit zum anlaufen berücksichtigen
    nextPossibleStart = Simulation::getTime() + p->getStartupTime();            //TODO flexibler gestalten: momentan nur ein startup gleichzeitig möglich
  }
}

void ProducerOwner::removeProducer() {
  if(producerList.size() > 1) producerList.pop_back();                          // cannot remove last producer
}

}}} /* End of namespaces */
