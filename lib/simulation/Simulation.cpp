#include <Simulation.h>

namespace simulation {

int Simulation::currTime;

Simulation::Simulation( const char * configFileName ) {
  try {
    this->medium.reset(config::SimulationBuilder::buildSimulation(configFileName, simulationAttribues));
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
  int err = SIMULATION_EXIT;
  int duration;
  std::ostringstream out (std::ostringstream::out);
  std::map<string, string>::iterator it;
  std::stringstream ss;

  it = simulationAttribues.find("duration");
  ss << it->second;
  ss >> duration;
  for(currTime=0; currTime<duration; currTime++) {
    try {
      err = this->medium->oneStep();
      if(err != SIMULATION_EXIT) return (err);
//      dumpMedium();
      cout << "Energy on medium: " << medium->getCurrentEnergy() << endl;
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
