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

int Medium::oneStep() throw (exception::EnergyException) {
  int tmp = 0;
  std::vector< endpoint::MediumEndpoint * >::iterator it;
  for(it = this->endpointList.begin(); it != this->endpointList.end(); it++) {
    endpoint::MediumEndpoint * e = *it;
    tmp += e->getEnergy();
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

int Medium::getCurrentEnergy() {
  return energy;
}


} /* End of namespace simulation::medium */
} /* End of namespace simulation */
