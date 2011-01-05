#include "Medium.h"
#include "producers/ProducerOwner.h"
#include "consumers/ConsumerOwner.h"

namespace simulation {
namespace medium {

int SIMULATION_EXIT;
int SIMULATION_FATAL_ERROR;

Medium::Medium(std::string name) {
  this->energy = 0;
  this->name = name;
}

void Medium::registerEndpoint(endpoint::MediumEndpoint * endpoint) {
  this->endpointList.push_back(endpoint);
}

void Medium::oneStep(double & produced, double & consumed) throw (exception::EnergyException) {
                                                                                //TODO ram can be saved here!
                                                                                //TODO clean up code after review (some things are not necessary and can be deleted)
  double tmp = 0;
  std::vector< endpoint::MediumEndpoint * >::iterator it;
  endpoint::producer::ProducerOwner * producer;

  // check each producer's production and consumer's consumption
  // save producer (as long as there is only one) -> otherwise.. other concept needed
  for(it = this->endpointList.begin(); it != this->endpointList.end(); it++) {
    endpoint::MediumEndpoint * e = *it;
    double energy = e->getEnergy();
//    if(energy > 0) produced += energy;
//    if(energy < 0) consumed -= energy;
                                                                                //TODO dauert vllt zu lange: wieder den alten code (drüber) benutzen
    endpoint::producer::ProducerOwner * po = dynamic_cast<endpoint::producer::ProducerOwner *>(e);
    if(po != 0) {
      produced += energy;
      producer = po;
    }
    endpoint::consumer::ConsumerOwner * co = dynamic_cast<endpoint::consumer::ConsumerOwner *>(e);
    if(co != 0) consumed -= energy;
                                                                                // TODO end-of-todo
    tmp += energy;
  }

  // make sure a producer exists
  if(producer == 0) throw exception::EnergyException("No producer present! Add one");

  // if energy < 0 "buy energy" and count it as produced
  if(tmp < 0) {
    produced -= tmp;
    //tmp +=                                                                    //TODO eingekaufte energie wird nicht in die bilanz eingerechnet -> kann negativ werden -> siehe exception weiter unten
    producer->notEnoughEnergyAction(-tmp);
  }

  // post-action for ProducerOwner (e.g. to check if any Producer should/can be switched on/off)
  producer->postStepAction(tmp);

  energy = tmp;
//  if(tmp < 0) throw exception::EnergyException("Not enough power available. Add producers or remove consumers! Bug?"); //TODO vllt raus nehmen (wenn weg kann man energiebilanz besser sehen)
}

void Medium::dump(std::ostringstream &out) {
  out << "  Medium (" << this->name << ") start..." << std::endl;
  for(std::vector< endpoint::MediumEndpoint* >::iterator it = this->endpointList.begin();
      it != this->endpointList.end(); it++) {
    endpoint::MediumEndpoint * me = *it;
    me->dump(out);
  }
  out << "  Medium end." << std::endl;
}

double Medium::getCurrentEnergy() {
  return energy;
}


} /* End of namespace simulation::medium */
} /* End of namespace simulation */
