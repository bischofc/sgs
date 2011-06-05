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
#include <sstream>
#include "ConfigBuilder.h"

int main( int argc, char * argv[] ) {
  if(argc != 4) {
    std::cout << "Exit: please check the parameters:" << std::endl;
    std::cout << "  outputFileName.xml (with '.xml')" << std::endl;
    std::cout << "  simulationDuration (in days)" << std::endl;
    std::cout << "  no. of consumers" << std::endl;
    return (-1);
  } else {
    int duration, cc;
    std::stringstream convert;
    convert << argv[2]; convert >> duration; convert.clear();
    convert << argv[3]; convert >> cc;
    std::cout << "Using file name '" << argv[1] << "'" << std::endl;
    builder::ConfigBuilder cb (argv[1], duration, cc);
    cb.buildConfig();
    return 0;
  }
}
