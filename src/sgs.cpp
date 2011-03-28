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

#include <iostream>
#include <sys/wait.h>

#include "Simulation.h"

//void new_fork(simulation::Simulation & s, int i) {
//  pid_t child = fork();
//  if(child < 0) {
//    std::cout << "Error while forking number " << i << ".. Exit" << std::endl;
//  } else if (child == 0) {
//    child = getpid();
//    std::cout << "Fork with PID " << child << " started" << std::endl;
//    s.runSimulation(i);
//    exit(0);
//  }
//}

int main( int argc, char * argv[] ) {
  if(argc != 2) {
    std::cout << "Exit: please check the parameters:" << std::endl;
    std::cout << "  config file name" << std::endl;
//    std::cout << "  number of processes" << std::endl;
    return (-1);
  } else {
    time_t start;
//    int procNo, status;
//    pid_t pid;
//    std::stringstream convert;
//    convert << argv[2]; convert >> procNo; //convert.clear();

    start = time(NULL);

    std::cout << "Using config file '" << argv[1] << "'" << std::endl;
    simulation::Simulation s ( argv[1] );
    
//    std::cout << "Using " << procNo << " process(es)" << std::endl;
//    for(int i = 0; i < procNo; i++) {
//      new_fork(s, i);
//    }
//    for(int i = 0; i < procNo; i++) {
//      pid = wait(&status);
//      std::cout << "Fork with PID " << pid << " ended with status " << status << std::endl;
//    }
    s.runSimulation();

    std::cout << "Execution took " << time(NULL)-start << " seconds" << std::endl;
  }
  return 0;
}
