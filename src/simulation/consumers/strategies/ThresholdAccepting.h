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

#ifndef simulation_endpoint_consumer_strategies_threshold_accepting_h
#define simulation_endpoint_consumer_strategies_threshold_accepting_h

#include <vector>
#include "Strategy.h"
#include "BasicStrategy.h" //TODO initiale Konfiguration
#include "BackpackStrategy.h" //TODO "beste Strategie"

namespace simulation {
namespace endpoint {
namespace consumer {

class ThresholdAccepting : public Strategy {
private:
  static const double thresholdFactor = 0.5;
  static const int outerSteps = 10;
  static const int innerSteps = 100;
  const std::vector< boost::shared_ptr<Consumer> > consumers;
  double threshold;
  int knapsackCosts;

private:
  int getCosts(const std::multimap<int, int> &moves);
  std::multimap<int, int> getNeighbour(const std::multimap<int, int> &moves);
  std::multimap<int, int> getInitialState();

public:
  ThresholdAccepting(const std::vector<int> &adjustment, const std::vector< boost::shared_ptr<Consumer> > &consumers);
  std::multimap<int, int> getMoves();
  virtual ~ThresholdAccepting() {}
};

}}} /* end of namespaces */

#endif
