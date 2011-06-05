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

#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <vector>
#include <map>
#include "../Consumer.h"

namespace simulation {
namespace endpoint {
namespace consumer {

struct Move {
  boost::shared_ptr<Consumer> device;
  int from;
  int to;
  int starttime;
  int runtime;
  int connectedLoad;

  Move(boost::shared_ptr<Consumer> device, int from, int to, int st, int rt, int cl) {
    this->device = device;
    this->from = from;
    this->to = to;
    starttime = st;
    runtime = rt;
    connectedLoad = cl;
  }

  Move(boost::shared_ptr<Consumer> device, int from, int to) {
    this->device = device;
    this->from = from;
    this->to = to;
    starttime = 0;
    runtime = 0;
    connectedLoad = 0;
  }
};

class Strategy {
protected:
  std::vector<int> adjustment;
  std::vector< boost::shared_ptr<Consumer> > consumers;

public:
  virtual std::vector<Move> getMoves() =0;
  virtual ~Strategy() {}

protected:
  Strategy(std::vector<int> adjustment, std::vector< boost::shared_ptr<Consumer> > consumers);
  bool isEnergyBalancePositive(int from, int to, int runtime, int wattage);
  void updateAdjustment(int from, int to, int runtime, int wattage);
};

}}}

#endif
