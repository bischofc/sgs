#include "Simulation.h"

namespace simulation {

int Simulation::currTime;
int Simulation::resolution;
int Simulation::duration;

Simulation::Simulation( const char * configFileName ) {
  try {
    // prepare simulation log file
    logfile.open("simulation.log");
    logfile << "#time\tenergy\tproduced\tconsumed" << endl;

    // build configuration and assign variables
    std::map<std::string, std::string> simulationAttribues;
    std::map<std::string, std::string>::iterator it;
    std::stringstream s1, s2;

    simulationAttribues = config::SimulationBuilder::buildConfiguration(configFileName);
    it = simulationAttribues.find("duration"); s1 << it->second; s1 >> duration;
    it = simulationAttribues.find("resolution"); s2 << it->second; s2 >> resolution;

    // build simulation
    this->medium.reset(config::SimulationBuilder::buildSimulation(configFileName));
  } catch (exception::ParserException &e) {
    std::cout << e.what() << std::endl;
    //TODO hier müsste beendet werden!
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

void Simulation::runSimulation() {
  std::cout << "Simulation started..." << std::endl;
  for(currTime=0; currTime<duration; currTime++) {
    try {
      double produced = 0;
      double consumed = 0;
      this->medium->oneStep(produced, consumed); //TODO oneStep mit Parametern, oder doch anders?
//      dumpMedium();
//      cout << "Energy on medium: " << medium->getCurrentEnergy() << endl;
      logfile << currTime << "\t" << medium->getCurrentEnergy() << "\t" << produced << "\t" << consumed << std::endl;
    } catch (exception::EnergyException &e) {
      std::cout << e.what() << std::endl;
      //TODO hier beenden?
    }
  }
  std::cout << "Simulation finished" << std::endl;
}

int Simulation::getTime() {
  return currTime;
}

int Simulation::getDuration() {
  return duration;
}

int Simulation::getResolution() {
  return resolution;
}

} /* End of namespace simulation */
