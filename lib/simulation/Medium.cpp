#include <Medium.h>

namespace simulation {
namespace medium {

Medium::Medium(std::string name) {
  this->name = name;
}

void Medium::registerEndpoint(endpoint::MediumEndpoint * endpoint) {
  std::vector< endpoint::MediumEndpoint* >::iterator it;
  it = this->endpointList.end();
  it = this->endpointList.insert(it, endpoint);
}

int Medium::oneStep() throw (exception::EnergyException) {
  try {
    int energy = 0;

    std::vector< endpoint::MediumEndpoint * >::iterator it;
    for(it = this->endpointList.begin(); it != this->endpointList.end(); it++) {
      endpoint::MediumEndpoint * e = *it;
      energy += e->getEnergy();
    }

    //todo remove cout
    std::cout << "Energy on medium: " << energy << std::endl;
    if(energy < 0) throw exception::EnergyException("Not enough power available. Add producers or remove consumers!");
    return 0;
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }
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


} /* End of namespace simulation::medium */
} /* End of namespace simulation */
