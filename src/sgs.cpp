
#include <iostream>
#include <sys/wait.h>

#include "Simulation.h"

void new_fork(simulation::Simulation & s, int i) {
  pid_t child = fork();
  if(child < 0) {
    std::cout << "Error while forking number " << i << ".. Exit" << std::endl;
  } else if (child == 0) {
    child = getpid();
    std::cout << "Fork with PID " << child << " started" << std::endl;
    s.runSimulation(i);
    exit(0);
  }
}

int main( int argc, char * argv[] ) {
  if(argc != 3) {
    std::cout << "Exit: please check the parameters:" << std::endl;
    std::cout << "  config file name" << std::endl;
    std::cout << "  number of processes" << std::endl;
    return (-1);
  } else {
    int procNo, status;
    pid_t pid;
    std::stringstream convert;
    convert << argv[2]; convert >> procNo; //convert.clear();

    std::cout << "Using config file '" << argv[1] << "'" << std::endl; //TODO check if file exists
    simulation::Simulation s ( argv[1], procNo );
    std::cout << "Using " << procNo << " process(es)" << std::endl;
    
    for(int i = 0; i < procNo; i++) {
      new_fork(s, i);
    }
    for(int i = 0; i < procNo; i++) {
      pid = wait(&status);
      std::cout << "Fork with PID " << pid << " ended with status " << status << std::endl;
    }
  }
  return 0;
}
