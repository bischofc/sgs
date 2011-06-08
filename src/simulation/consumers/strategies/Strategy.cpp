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

#include "Strategy.h"

namespace simulation {
namespace endpoint {
namespace consumer {

Strategy::Strategy(std::vector<int> adjustment,
    std::vector< boost::shared_ptr<Consumer> > consumers
    ) : consumers(consumers), adjustment(adjustment) {
}

bool Strategy::isEnergyBalancePositive(const std::vector<int> &adjustment, int from, int to, int runtime, int wattage) {
  return getEnergyBalance(adjustment, from, to, runtime, wattage) > 0;
}

int Strategy::getEnergyBalance(const std::vector<int> &adjustment, int from, int to, int runtime, int wattage) {
  int balance = 0;
  double factor = 0.3;                                                          //TODO factor should be set to 1.0;

  // check "from" time
  for(int i = from; i < from + runtime && i < 24; i++) {
    if(adjustment[i] >= 0) balance -= factor*wattage;
    else balance += (wattage <= -adjustment[i]) ? wattage : -2*adjustment[i] - factor*wattage;
  }

  // check "to" time
  for(int i = to; i < to + runtime && i < 24; i++) {
    if(adjustment[i] <= 0) balance -= factor*wattage;
    else balance += (wattage <= adjustment[i]) ? wattage : 2*adjustment[i] - factor*wattage;
  }

  return balance;
}

void Strategy::updateAdjustment(std::vector<int> &adjustment, int from, int to, int runtime, int wattage) {
  // update "from"
  for(int i = from; i < from + runtime && i < 24; i++) adjustment[i] += wattage;
  // update "to"
  for(int i = to; i < to + runtime && i < 24; i++) adjustment[i] -= wattage;
}

}}}
