#ifndef simulation_Simulation_h
#define simulation_Simulation_h

#include <SimulationBuilder.h>
#include <Medium.h>
#include <iostream>
#include <sstream>
#include <memory>

namespace simulation {

class Simulation {

public:
  Simulation( const char * configFileName );
  void dumpMedium();
  int runSimulation();
  static int getTime();

private:
  static int currTime;
  std::auto_ptr< medium::Medium > medium;
};

} /* End of namespace simulation */

#endif // simulation_Simulation_h
