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

#ifndef simulation_endpoint_producer_producerOwner_h
#define simulation_endpoint_producer_producerOwner_h

#include <map>
#include "boost/shared_ptr.hpp"
#include "Producer.h"
#include "Logger.h"

namespace simulation {
namespace endpoint {
namespace producer {

class ProducerOwner {
  boost::shared_ptr<Logger> logger;
  boost::shared_ptr<Logger> logger2;
  std::string id;
  std::vector< boost::shared_ptr<Producer> > producerList;
  int referenceLoadCurves[7][24];

private:
  std::vector<int> getForecastLoadCurve(int households);
  void addBestDeficits(const std::vector<int> &reference, std::vector<int> &adjustment);

public:
  ProducerOwner(std::string ownerId);
  virtual ~ProducerOwner() {}
  std::string getId();
  void addProducer(boost::shared_ptr<Producer>);
  std::vector<int> getLoadAdjustment(int households);
};

}}} /* End of namespaces */

#endif // simulation_endpoint_producer_producerOwner_h
