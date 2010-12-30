#include "Simulation.h"

namespace simulation {

int Simulation::currTime;

Simulation::Simulation( const char * configFileName ) {
  try {
    logfile.open("simulation.log");
    logfile << "#time\tenergy\tproduced\tconsumed" << endl;
    this->medium.reset(config::SimulationBuilder::buildSimulation(configFileName, simulationAttribues));
  } catch (exception::ParserException &e) {
    std::cout << e.what() << std::endl;
  }
}

Simulation::~Simulation() {
  logfile.close();
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
  std::map<std::string, std::string>::iterator it;
  std::stringstream ss;

  it = simulationAttribues.find("duration");
  ss << it->second;
  ss >> duration;

  std::cout << "Simulation started..." << std::endl;
  for(currTime=0; currTime<duration; currTime++) {
    try {
      double produced = 0;
      double consumed = 0;
      err = this->medium->oneStep(produced, consumed); //TODO oneStep mit Parametern, oder doch anders?
      if(err != SIMULATION_EXIT) return (err);
//      dumpMedium();
//      cout << "Energy on medium: " << medium->getCurrentEnergy() << endl;
      logfile << currTime << "\t" << medium->getCurrentEnergy() << "\t" << produced << "\t" << consumed << std::endl;
    } catch (exception::EnergyException &e) {
      std::cout << e.what() << std::endl;
      return (-1);
    }
  }
  std::cout << "Simulation finished" << std::endl;
  return (0);
}

int Simulation::getTime() {
  return currTime;
}

} /* End of namespace simulation */
