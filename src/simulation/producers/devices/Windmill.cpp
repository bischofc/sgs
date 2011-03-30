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

#include "Windmill.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace producer {

Windmill::Windmill(std::string producerId) : Producer(producerId) {
  if(!logger) logger = Logger::getInstance("windmill.log", Logger::CUSTOM);
  logger->custom("#hour\twattage");
}

std::vector<int> Windmill::getForecastCurve(int households) {           //TODO use real data here
  std::vector<int> tmp (24, 0);
  int duration = helper::RandomNumbers::getRandom(1, 4);
  int hour = helper::RandomNumbers::getRandom(0, 23);
  int wattage = helper::RandomNumbers::getRandom(300, 400);
  if(hour + duration > 24) duration = 24 - hour;

  for(int i = hour; i < hour + duration; i++) {
    tmp.at(i) = wattage;
  }
  //TODO sanity check

  for (int i = 0; i < tmp.size(); ++i) {
    logger->custom(Logger::toString(i) + "\t" + Logger::toString(tmp.at(i)*households));
  }
  return tmp;
}

}}} /* end of namespaces */
