
#include <iostream>
#include <sstream>

#include "ConfigBuilder.h"

int main( int argc, char * argv[] ) {
  if(argc != 5) {
    std::cout << "Exit: please check the parameters:" << std::endl;
    std::cout << "  outputFileName.xml (with '.xml')" << std::endl;
    std::cout << "  simulationDuration (in seconds)" << std::endl;
    std::cout << "  simulationResolution (1 for hour, 60 for minute, 3600 for second)" << std::endl;
    std::cout << "  no. of consumers" << std::endl;
    return (-1);
  } else {
    int duration, cc, res;
    std::stringstream convert;
    convert << argv[2]; convert >> duration; convert.clear();
    convert << argv[3]; convert >> res; convert.clear();
    convert << argv[4]; convert >> cc;
    std::cout << "Using file name '" << argv[1] << "'" << std::endl;
    builder::ConfigBuilder cb (argv[1], duration, res, cc);
    cb.buildConfig();
    return 0;
  }
}
