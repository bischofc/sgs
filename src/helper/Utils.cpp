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

#include <Utils.h>
#include <boost/foreach.hpp>

namespace helper {

std::vector<int> Utils::addIntVectors(std::vector<int> a, std::vector<int> b) {
  std::vector<int> tmp;
  unsigned s = a.size() < b.size() ? b.size() : a.size();
  for(unsigned i = 0; i < s; i++) {
    int x = a.size() > i ? a.at(i) : 0;
    int y = b.size() > i ? b.at(i) : 0;
    tmp.push_back(x+y);
  }
  return tmp;
}

std::pair<int, int> Utils::getLargestValue(std::map<int, int> &map) {
  std::pair<int, int> tmp (-1, -1);
  for(std::map<int, int>::iterator it = map.begin(); it != map.end(); it++) {
    if(it->second > tmp.second) tmp = *it;
  }
  return tmp;
}

std::pair<int, int> Utils::getLargestValue(std::vector<int> &vec) {
  std::pair<int, int> tmp (-1, -1);
  for(unsigned i = 0; i < vec.size(); i++) {
    if(vec.at(i) > tmp.second) {
      tmp.first = i;
      tmp.second = vec.at(i);
    }
  }
  return tmp;
}

std::pair<int, int> Utils::getSmallestValue(std::vector<int> &vec) {
  std::pair<int, int> tmp (vec.size(), INT_MAX);
  for(unsigned i = 0; i < vec.size(); i++) {
    if(vec.at(i) < tmp.second) {
      tmp.first = i;
      tmp.second = vec.at(i);
    }
  }
  return tmp;
}

double Utils::getMean(const std::vector<double> &values) {
  return getSum(values) / values.size();
}

double Utils::getSum(const std::vector<double> &values) {
  int tmp = 0;
  BOOST_FOREACH(double i, values) tmp += i;
  return tmp;
}

void Utils::vectorSubstract(std::vector<double> &vec, double sub) {
  for(std::vector<double>::iterator it = vec.begin(); it != vec.end(); it++) *it -= sub;
}

std::vector<double> Utils::vectorMult(const std::vector<double> &vec1, const std::vector<double> &vec2) {
  if(vec1.size() != vec2.size()) throw exception::DomainException("Vector sizes do not match!");
  std::vector<double> tmp = vec1;
  for(unsigned int i = 0; i < tmp.size(); i++) tmp.at(i) *= vec2.at(i);
  return tmp;
}


} /* end of namespace */
