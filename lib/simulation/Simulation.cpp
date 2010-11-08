#include <Simulation.h>

namespace simulation {

int Simulation::currTime;

//TODO vehindern, dass producer und consumer negative werte zurückgeben

Simulation::Simulation( const char * configFileName ) {
  try {
    this->medium.reset(config::SimulationBuilder::buildSimulation(configFileName));
  } catch (exception::ParserException &e) {
    std::cout << e.what() << std::endl;
  }
}

void Simulation::dumpMedium() {
  std::ostringstream out (std::ostringstream::out);
  out << std::endl << "Dump start..." << std::endl;
  this->medium->dump(out);
  out << "Dump end." << std::endl;
  std::cout << out.str();
}

int Simulation::runSimulation() { // return error code
  int err = 0;
  for(currTime=0; currTime<10; currTime++) {
    try {
      err = this->medium->oneStep();
//      dumpMedium();
      if(err != 0) return (err);
    } catch (exception::EnergyException &e) {
      cout << e.what() << endl;
      return (-1);
    }
  }
  return (0);
}

int Simulation::getTime() {
  return currTime;
}

} /* End of namespace simulation */
