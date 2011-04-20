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
#include "strategies/TestBackpackStrategy.h"

int main( int, char** ) {
  bool allGood = true;
  std::cout << "Start testing" << std::endl << std::endl;

  std::cout << "  Testing 'BackpackStrategy' (1000x) ...\n";
  for(int i = 0; i < 1000; i++) {
    if(!TestBackpackStrategy::test()) {
      std::cout << "    Test failed at " << i+1 << ". run\n";
      allGood = false;
      break;
    }
  }
  std::cout << "  Testing BackpackStrategy completed" << std::endl << std::endl;

  std::cout << "Finished testing\n";
  if(allGood) std::cout << "  All tests were completed successfully. Congratz!";
  else std::cout << "  At least one test failed. Good luck fixing the problem!";
  std::cout << std::endl;
}
