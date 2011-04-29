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

#ifndef simulation_endpoint_consumer_consumer_h
#define simulation_endpoint_consumer_consumer_h

#include <sstream>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "Parsable.h"
#include "energy/EnergyPlan.h"
#include "exceptions/EnergyException.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Consumer : public Parsable {
protected:
  std::string id;
  std::vector< boost::shared_ptr<config::EnergyPlan> > energyPlans;
  bool movable;

protected:
  Consumer(std::string);
  void addEnergyPlan(boost::shared_ptr<config::EnergyPlan>);

public:
  int getCurrentWattage() throw (exception::EnergyException);
  void move(int fromHour, int toHour);
  bool isMovable();
  bool activeInHourOnCurrentDay(int hour);
  void resetEnergyPlans();
  virtual ~Consumer() { }
};

} /* End of namespace simulation::endpoint::consumer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_consumer_consumer_h
