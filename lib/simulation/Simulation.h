#ifndef simulation_simulation_h
#define simulation_simulation_h

#include <iostream>
#include <fstream>
#include <memory>
#include <map>

#include "Medium.h"

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

#endif // simulation_simulation_h
