
#include <iostream>
#include <sstream>

#include "ConfigBuilder.h"

int main( int argc, char * argv[] ) {
  if(argc != 4) {
    std::cout << "Exit: please check the parameters:" << std::endl;
    std::cout << "  outputFileName.xml (with '.xml')" << std::endl;
    std::cout << "  simulationDuration (in seconds)" << std::endl;
//    std::cout << "  no. of producers" << std::endl;
    std::cout << "  no. of consumers" << std::endl;
    return (-1);
  } else {
    int duration, pc, pp, cc;
    std::stringstream convert;
    convert << argv[2]; convert >> duration; convert.clear();
//    convert << argv[3]; convert >> pc; convert.clear();
    convert << argv[3]; convert >> cc;
    std::cout << "Using file name '" << argv[1] << "'" << std::endl;
    builder::ConfigBuilder cb (argv[1], duration, cc);
    cb.buildConfig();
    return 0;
  }
}
