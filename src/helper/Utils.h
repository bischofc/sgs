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

#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <map>
#include <iostream>

namespace helper {

std::vector<int> addIntVectors(std::vector<int> a, std::vector<int> b) {
  std::vector<int> tmp;
  unsigned s = a.size() < b.size() ? b.size() : a.size();
  for(unsigned i = 0; i < s; i++) {
    int x = a.size() > i ? a.at(i) : 0;
    int y = b.size() > i ? b.at(i) : 0;
    tmp.push_back(x+y);
  }
  return tmp;
}

std::pair<int, int> getLargestValue(std::map<int, int> &map) {
  std::pair<int, int> tmp (-1, -1);
  for(std::map<int, int>::iterator it = map.begin(); it != map.end(); it++) {
    if(it->second > tmp.second) tmp = *it;
  }
  return tmp;
}

std::pair<int, int> getLargestValue(std::vector<int> &vec) {
  std::pair<int, int> tmp (-1, -1);
  for(unsigned i = 0; i < vec.size(); i++) {
    if(vec.at(i) > tmp.second) {
      tmp.first = i;
      tmp.second = vec.at(i);
    }
  }
  return tmp;
}

template <typename T>
void printVector(const std::vector<T> &vec) {
  std::cout << "\n";
  typedef typename std::vector<T>::const_iterator vec_it;
  for(vec_it it = vec.begin(); it != vec.end(); it++) {
    std::cout << *it << ", ";
  }
  std::cout << "\n";
}

template <typename K, typename V>
void printMap(const std::map<K, V> &map) {
  std::cout << "\n";
  typedef typename std::map<K, V>::const_iterator map_it;
  for(map_it it = map.begin(); it != map.end(); it++) {
    std::cout << it->first << ": " << it->second << ", ";
  }
  std::cout << "\n";
}

template <typename C>
std::vector<C> arrayToVector(C array[], int size) {
  std::vector<C> tmp;
  for(int i=0; i<size; i++) {
    tmp.push_back(array[i]);
  }
  return tmp;
}

} /* end of namespace */

#endif
