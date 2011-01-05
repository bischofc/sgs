#ifndef simulation_simulation_h
#define simulation_simulation_h

#include <iostream>
#include <fstream>
#include <memory>
#include <map>

#include "Medium.h"
#include "SimulationBuilder.h"

namespace simulation {

#define SIMULATION_EXIT 0
#define SIMULATION_FATAL_ERROR -1

class Simulation {

private:
  static int currTime;
  static int duration;
  static int resolution; // in hours -> 1 means hour, 60 means min, 3600 means sec, ...
  std::auto_ptr< medium::Medium > medium;
  std::ofstream logfile;

public:
  static int getTime();
  static int getDuration();
  static int getResolution();

public:
  Simulation( const char * configFileName );
  virtual ~Simulation();
  void dumpMedium();
  int runSimulation();
};

} /* End of namespace simulation */

#endif // simulation_simulation_h
