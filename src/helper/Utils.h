
#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <stdio.h>

namespace helper {

class Utils {
  Utils();

public:
  virtual ~Utils();

public:
  template <class C>
  static std::vector<C> arrayToVector(C array[], int size) {
    std::vector<C> tmp;
    for(unsigned i=0; i<size; i++) {
      tmp.push_back(array[i]);
    }
    return tmp;
  }

};

}

#endif /* UTILS_H_ */
