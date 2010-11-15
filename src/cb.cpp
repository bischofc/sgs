#include <ConfigBuilder.h>
#include <iostream>
#include <sstream>

int main( int argc, char * argv[] ) {
  if(argc != 5) {
    std::cout << "Exit: please check the parameters" << std::endl;
    return (-1);
  } else {
    int pc, pp, cc;
    std::stringstream convert;
    convert << argv[2]; convert >> pc; convert.clear();
    convert << argv[3]; convert >> pp; convert.clear();
    convert << argv[4]; convert >> cc;
    std::cout << "Using file name '" << argv[1] << "'" << std::endl;
    builder::ConfigBuilder cb (argv[1], pc, pp, cc, "bra");
    cb.buildConfig();
    return 0;
  }
}
