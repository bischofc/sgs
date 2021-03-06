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
  boost::shared_ptr<Logger> datafile;
  static int currTime;
  static int duration;
  const static int resolution = 60;                                             // in hours -> 1 means hour, 60 means min, 3600 means sec, 4 means 15 minutes, ...
  boost::shared_ptr< medium::Medium > medium;

public:
  static int getTime();
  static int getDuration();
  static int getResolution();

public:
  Simulation( const char * configFileName );
  virtual ~Simulation();
  void runSimulation();
};

} /* End of namespace simulation */

#endif // simulation_simulation_h
