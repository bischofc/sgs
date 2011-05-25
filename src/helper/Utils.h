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

#ifndef helpers_utils_h
#define helpers_utils_h

#include <vector>
#include <map>
#include <iostream>
#include <limits.h>
#include "DomainException.h"

namespace helper {

class Utils {
public:
  struct largeToSmallComperator {
    bool operator() (const char& lhs, const char& rhs) const
    {return lhs>rhs;}
  };

public:
  static std::vector<int> addIntVectors(std::vector<int> a, std::vector<int> b);
  static std::pair<int, int> getLargestValue(std::map<int, int> &map);
  static std::pair<int, int> getLargestValue(std::vector<int> &vec);
  static std::pair<int, int> getSmallestValue(std::vector<int> &vec);
  static double getMean(const std::vector<double> &values);
  static double getSum(const std::vector<double> &values);
  static void vectorSubstract(std::vector<double> &vec, double sub);
  static std::vector<double> vectorMult(const std::vector<double> &vec1, const std::vector<double> &vec2);
  static std::vector<int> linearRegression(const std::vector<int> &vec);

public:
  template <typename T>
  static void print(T string) {
    std::cout << string << " ";
  }

  template <typename T>
  static void println(T string) {
    std::cout << std::endl << string << std::endl;
  }

  template <typename T>
  static void printVector(const std::vector<T> &vec) {
    std::cout << "\n";
    typedef typename std::vector<T>::const_iterator vec_it;
    for(vec_it it = vec.begin(); it != vec.end(); it++) {
      std::cout << *it << ", ";
    }
    std::cout << "\n";
  }

  template <typename K, typename V>
  static void printMap(const std::map<K, V> &map) {
    std::cout << "\n";
    typedef typename std::map<K, V>::const_iterator map_it;
    for(map_it it = map.begin(); it != map.end(); it++) {
      std::cout << it->first << ": " << it->second << ", ";
    }
    std::cout << "\n";
  }

  template <typename K, typename V>
  static void printMultiMap(const std::multimap<K, V> &map) {
    std::cout << "\n";
    typedef typename std::multimap<K, V>::const_iterator map_it;
    for(map_it it = map.begin(); it != map.end(); it++) {
      std::cout << it->first << ": " << it->second << ", ";
    }
    std::cout << "\n";
  }

  template <typename C>
  static std::vector<C> arrayToVector(C array[], int size) {
    std::vector<C> tmp;
    for(int i=0; i<size; i++) {
      tmp.push_back(array[i]);
    }
    return tmp;
  }

};

}

#endif
