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

#ifndef simulation_endpoint_consumer_strategies_basic_strategy_h
#define simulation_endpoint_consumer_strategies_basic_strategy_h

#include <vector>
#include <map>

namespace simulation {
namespace endpoint {
namespace consumer {

struct largeToSmallComperator {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs>rhs;}
};

class BasicStrategy {
private:
  BasicStrategy() {}

public:
  static std::multimap<int, int> getMoves(const std::vector<int> &adjustment);
  virtual ~BasicStrategy() {}
};

}}} /* end of namespaces */

#endif
