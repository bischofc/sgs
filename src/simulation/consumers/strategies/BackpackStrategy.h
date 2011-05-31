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

#ifndef simulation_endpoint_consumer_strategies_backpack_strategy_h
#define simulation_endpoint_consumer_strategies_backpack_strategy_h

#include <vector>
#include <map>
#include "Strategy.h"

namespace simulation {
namespace endpoint {
namespace consumer {

struct BackpackElement {
  int hour, weight, profit;

  BackpackElement(int hour, int weight, int profit) {
    this->hour = hour;
    this->weight = weight;
    this->profit = profit;
  }
};

class BackpackStrategy : public Strategy {
public:
  BackpackStrategy(const std::vector<int> &adjustment, const std::vector< boost::shared_ptr<Consumer> > &consumers);
  std::vector<Move> getMoves();
  virtual ~BackpackStrategy() {}
};

}}} /* end of namespaces */

#endif
