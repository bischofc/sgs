
#include <iostream>

#include "Simulation.h"

int main( int argc, char * argv[] ) {
  if(argc != 2) {
    std::cout << "Exit: please check the parameters" << std::endl;
    return (-1);
  } else {
    std::cout << "Using config file '" << argv[1] << "'" << std::endl; //TODO check if file exists
    simulation::Simulation s ( argv[1] );
    s.runSimulation();
    return 0;
  }
}
