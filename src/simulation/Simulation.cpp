#include "Simulation.h"

namespace simulation {

int Simulation::currTime;
int Simulation::resolution;
int Simulation::duration;

Simulation::Simulation( const char * configFileName ) {
  logger = Logger::getInstance("simulation.log", Logger::DEBUG);
  try {
    // build simulation
    medium = config::SimulationBuilder::buildSimulation(configFileName, duration, resolution);
  } catch (exception::ParserException &e) {
    std::cout << e.what() << std::endl;                                         //TODO hier müsste beendet werden!
  }
}

Simulation::~Simulation() {
  datafile.close();
}

void Simulation::dumpMedium() {
  std::ostringstream out (std::ostringstream::out);
  out << std::endl << "Dump start..." << std::endl;
  this->medium->dump(out);
  out << "Dump end." << std::endl;
  std::cout << out.str();
}

void Simulation::runSimulation() {
  int stepCounter = 0;

  // prepare simulation log file
  datafile.open("simulation.out");
  datafile << "#time\tenergy" << std::endl;

  logger->debug("Simulation started...");
  for(currTime=0; currTime<duration; currTime++) {
    try {
      this->medium->oneStep();
//      dumpMedium();
      datafile << currTime << "\t" << medium->getCurrentEnergy() << std::endl;

      // fancy progress output
      stepCounter++;
      if(stepCounter % 1000 == 0) {
        std::cout << "|\r\n";
        std::cout.flush();
      } else if(stepCounter % 100 == 0) {
        std::cout << "|";
        std::cout.flush();
      } else if(stepCounter % 50 == 0) {
        std::cout << ":";
        std::cout.flush();
      } else if(stepCounter % 10 == 0) {
        std::cout << ".";
        std::cout.flush();
      }
    } catch (exception::EnergyException &e) {
      std::cout << e.what() << std::endl;                                       //TODO hier beenden?
    }
  }
  std::cout << std::endl;
  logger->debug("Simulation finished");
}

int Simulation::getTime() {
  return currTime;
}

int Simulation::getResolution() {
  return resolution;
}

} /* End of namespace simulation */
