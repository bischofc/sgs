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

namespace simulation {
namespace endpoint {
namespace consumer {

class ThresholdAccepting : public Strategy {
private:
  static const double thresholdFactor = 0.5;
  static const int outerSteps = 10;
  static const int innerSteps = 50;
  static boost::shared_ptr<Logger> logger;
  double threshold;
  int referenceCosts;

private:
  int getCosts(const std::vector<Move> &moves);
  std::vector<Move> getNeighbour(const std::vector<Move> &moves);
  std::vector<Move> getInitialState();
  std::vector<Move>::const_iterator findDeviceOfMoveInMoveList(const std::vector<Move> &vec, const Move &m);

public:
  ThresholdAccepting(const std::vector<int> &adjustment, const std::vector< boost::shared_ptr<Consumer> > &consumers);
  std::vector<Move> getMoves();
  virtual ~ThresholdAccepting() {}
};

}}} /* end of namespaces */

#endif
