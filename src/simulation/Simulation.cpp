#include "Simulation.h"

namespace simulation {

int Simulation::currTime;
int Simulation::resolution;
int Simulation::duration;

Simulation::Simulation( const char * configFileName, int numberOfCores, int duration, int resolution) {
  try {
    NUMBER_OF_CORES = numberOfCores;
    this->duration = duration;
    this->resolution = resolution;

    // build simulation
    medium = config::SimulationBuilder::buildSimulation(configFileName);
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

void Simulation::runSimulation(int pid) {
//  int stepCounter = 0;

  // prepare simulation log file
  stringstream a;
  string logFileName;
  a << "simulation_" << pid << ".log";
  a >> logFileName;
  logfile.open(logFileName.c_str());
  logfile << "#time\tenergy\tproduced\tbought\tconsumed" << endl;

  logfile << "#Simulation started..." << endl; //TODO ohne das wird die zweite Datei leer, warum?
  for(currTime=0; currTime<duration; currTime++) {
    try {
      double produced = 0;
      double consumed = 0;
      double bought = 0;
      this->medium->oneStep(pid, produced, consumed, bought); //TODO oneStep mit Parametern, oder doch anders?
//      dumpMedium();
      logfile << currTime << "\t" << medium->getCurrentEnergy() << "\t" << produced << "\t" << bought << "\t" << consumed << "\t" << std::endl;

/*
      // fancy progress output
      stepCounter++;
      if(stepCounter == 50) {
        std::cout << ":";
        std::cout.flush();
      } else if(stepCounter == 100) {
        std::cout << "|";
        std::cout.flush();
        stepCounter = 0;
      } else if(stepCounter % 10 == 0) {
        std::cout << ".";
        std::cout.flush();
      }
*/
    } catch (exception::EnergyException &e) {
      std::cout << e.what() << std::endl;
      //TODO hier beenden?
    }
  }
  logfile << "#Simulation finished" << endl;
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
