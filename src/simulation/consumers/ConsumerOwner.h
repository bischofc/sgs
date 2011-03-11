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

#ifndef simulation_endpoint_consumer_consumerOwner_h
#define simulation_endpoint_consumer_consumerOwner_h

#include "consumers/Consumer.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class ConsumerOwner {
  std::string id;
  std::vector< boost::shared_ptr<Consumer> > consumerList;

 public:
  ConsumerOwner(std::string ownerId);
  virtual ~ConsumerOwner() {}
  std::string getId();
  void dump(std::ostringstream&);
  void addConsumer(boost::shared_ptr<Consumer>);
  void adjustLoad(std::vector<double> adjustment);
  double getEnergy() throw (exception::EnergyException);
};

} /* End of namespace simulation::endpoint::consumer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */

#endif // simulation_endpoint_consumer_consumerOwner_h
