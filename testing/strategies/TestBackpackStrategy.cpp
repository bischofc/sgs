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

#include <vector>
#include "TestBackpackStrategy.h"
#include "consumers/strategies/BackpackStrategy.h"
#include "RandomNumbers.h"
#include "Utils.h"

bool TestBackpackStrategy::test() {

  std::vector<int> adjustment (24, 0);
  std::vector<int> profits (24, 0);

  for(int i = 0; i < helper::RandomNumbers::getRandom(3,5); i++) {
    int from, to;
    do {
      from = helper::RandomNumbers::getRandom(0,23);
      to = helper::RandomNumbers::getRandom(0,23);
    } while(from == to);
    int wattage = helper::RandomNumbers::getRandom(1,9);
    int profit = helper::RandomNumbers::getRandom(1,9);

    adjustment.at(from) -= wattage;
    adjustment.at(to) += wattage;
    profits.at(from) += profit;
  }

  int maxProfit;
  std::vector<simulation::endpoint::consumer::BackpackElement> backpack;

  simulation::endpoint::consumer::BackpackStrategy::getMoves(adjustment, profits, maxProfit, backpack);

  int tmp = 0;
  for(std::vector<simulation::endpoint::consumer::BackpackElement>::iterator it = backpack.begin();
      it != backpack.end(); it++) tmp += (*it).profit;
  return(tmp == maxProfit);
}
