#include "Simulation.h"

//TODO remove
#include "Sizes.h"

namespace simulation {

int Simulation::currTime;
int Simulation::resolution;
int Simulation::duration;

Simulation::Simulation( const char * configFileName ) {
  try {
    // build simulation
    medium = config::SimulationBuilder::buildSimulation(configFileName, duration, resolution);
  } catch (exception::ParserException &e) {
    std::cout << e.what() << std::endl;                                         //TODO hier müsste beendet werden!
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
  int stepCounter = 0;
  int numCons = medium->getNumberOfConsumers();
  std::cout << "Expected Memory Usage with " << numCons << " consumers: " << Sizes::getSize(numCons)/1000000 << " MB" << std::endl;//TODO remove

  // prepare simulation log file
  logfile.open("simulation.log");
  logfile << "#time\tenergy\tproduced\tbought\tconsumed" << endl;

  logfile << "#Simulation started..." << endl;                                  //TODO ohne das wird die zweite Datei leer, warum?
  for(currTime=0; currTime<duration; currTime++) {
    try {
      double produced = 0;
      double consumed = 0;
      double bought = 0;
      this->medium->oneStep(produced, consumed, bought);                        //TODO oneStep mit Parametern, oder doch anders?
//      dumpMedium();
      logfile << currTime << "\t" << medium->getCurrentEnergy() << "\t" << produced << "\t" << bought << "\t" << consumed << "\t" << std::endl;

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
    } catch (exception::EnergyException &e) {
      std::cout << e.what() << std::endl;                                       //TODO hier beenden?
    }
  }
  std::cout << endl;
  logfile << "#Simulation finished" << endl;
}

int Simulation::getTime() {
  return currTime;
}

int Simulation::getResolution() {
  return resolution;
}

} /* End of namespace simulation */
