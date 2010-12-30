#include "Medium.h"

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

int Medium::oneStep(double & produced, double & consumed) throw (exception::EnergyException) {
  double tmp = 0;
  std::vector< endpoint::MediumEndpoint * >::iterator it;
  for(it = this->endpointList.begin(); it != this->endpointList.end(); it++) {
    endpoint::MediumEndpoint * e = *it;
    double energy = e->getEnergy();
    if(energy > 0) produced += energy;
    if(energy < 0) consumed -= energy;
    tmp += energy;
  }
  energy = tmp;
  if(tmp < 0) throw exception::EnergyException("Not enough power available. Add producers or remove consumers!");
  return SIMULATION_EXIT;
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
