#ifndef simulation_Simulation_h
#define simulation_Simulation_h

#include <Medium.h>
#include <SimulationBuilder.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <map>

namespace simulation {

#define SIMULATION_EXIT 0
#define SIMULATION_FATAL_ERROR -1

class Simulation {

public:
  Simulation( const char * configFileName );
  virtual ~Simulation();
  void dumpMedium();
  int runSimulation();
  static int getTime();

private:
  static int currTime;
  std::map<std::string, std::string> simulationAttribues;
  std::auto_ptr< medium::Medium > medium;
  std::ofstream logfile;
};

} /* End of namespace simulation */

#endif // simulation_Simulation_h
