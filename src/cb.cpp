#include <ConfigBuilder.h>
#include <iostream>

int main( int argc, char * argv[] ) {
  if(argc != 2) {
    std::cout << "Exit: please check the parameters" << std::endl;
    return (-1);
  } else {
    std::cout << "Using file name '" << argv[1] << "'" << std::endl;
    builder::ConfigBuilder cb (argv[1], "cable", 1, 12, 1);
    cb.buildConfig();
    return 0;
  }
}
