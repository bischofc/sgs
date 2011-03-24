/*
Copyright (C) 2010 Christian Bischof (bischof.christian@gmail.com)
This file is part of "Smart Grid Simulator".

"Smart Grid Simulator" is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

"Smart Grid Simulator" is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with "Smart Grid Simulator".  If not, see <http://www.gnu.org/licenses/>.
*/

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

void Simulation::runSimulation() {
  int stepCounter = 0;

  // prepare simulation log file
  datafile.open("simulation.out");
  datafile << "#time\tenergy" << std::endl;

  logger->info("Simulation started...");
  for(currTime=0; currTime<duration; currTime++) {
    try {
      this->medium->oneStep();
//      dumpMedium();
      datafile << currTime << "\t" << medium->getCurrentWattage() << std::endl;

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
  logger->info("Simulation finished");
}

int Simulation::getTime() {
  return currTime;
}

int Simulation::getResolution() {
  return resolution;
}

} /* End of namespace simulation */
