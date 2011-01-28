#ifndef simulation_simulation_h
#define simulation_simulation_h

#include <iostream>
#include <fstream>
#include <memory>

#include "Logger.h"
#include "Medium.h"
#include "SimulationBuilder.h"

namespace simulation {

class Simulation {

private:
  boost::shared_ptr<Logger> logger;
  static int currTime;
  static int duration;
  static int resolution;                                                        // in hours -> 1 means hour, 60 means min, 3600 means sec, 4 means 15 minutes, ...
  boost::shared_ptr< medium::Medium > medium;
  std::ofstream datafile;

public:
  static int getTime();
  static int getDuration();
  static int getResolution();

public:
  Simulation( const char * configFileName );
  virtual ~Simulation();
  void dumpMedium();
  void runSimulation();
};

} /* End of namespace simulation */

#endif // simulation_simulation_h
