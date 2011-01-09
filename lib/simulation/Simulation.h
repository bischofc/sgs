#ifndef simulation_simulation_h
#define simulation_simulation_h

#include <iostream>
#include <fstream>
#include <memory>
#include <map>

#include "Medium.h"
#include "SimulationBuilder.h"

namespace simulation {

class Simulation {

private:
  static int currTime;
  static int duration;
  static int resolution; // in hours -> 1 means hour, 60 means min, 3600 means sec, ...
  boost::shared_ptr< medium::Medium > medium;
  std::ofstream logfile;

public:
  static int NUMBER_OF_CORES;
  static int getTime();
  static int getDuration();
  static int getResolution();

public:
  Simulation( const char * configFileName , int numberOfCores );
  virtual ~Simulation();
  void dumpMedium();
  void runSimulation(int pid);
};

} /* End of namespace simulation */

#endif // simulation_simulation_h
