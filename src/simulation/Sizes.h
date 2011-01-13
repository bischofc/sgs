#include <iostream>

#include "Medium.h"

#include "producers/ProducerOwner.h"
#include "producers/devices/Windmill.h"
#include "consumers/ConsumerOwner.h"
#include "consumers/devices/Fridge.h"
#include "consumers/devices/Kettle.h"
#include "consumers/devices/Light.h"
#include "consumers/devices/Radio.h"
#include "consumers/devices/Stove.h"
#include "consumers/devices/Television.h"
#include "consumers/devices/Ventilator.h"
#include "energy/plans/EnergyPlanStatic.h"

using namespace std;
using namespace simulation;
using namespace simulation::medium;
using namespace simulation::config;
using namespace simulation::endpoint;
using namespace simulation::endpoint::consumer;
using namespace simulation::endpoint::producer;

class Sizes {

private:
  Sizes() {}

public:
  static double getSize(int consumers) {
    double po, co, w, f, k, l, r, s, t, v, e;
    double producers = 1;
    double mem;

    po = sizeof(ProducerOwner);
    co = sizeof(ConsumerOwner);
    w = sizeof(Windmill);
    f = sizeof(Fridge);
    k = sizeof(Kettle);
    l = sizeof(Light);
    r = sizeof(Radio);
    s = sizeof(Stove);
    t = sizeof(Television);
    v = sizeof(Ventilator);
    e = sizeof(EnergyPlanStatic);


    mem =
                    producers * po +
                    producers * w +
                    producers * e +

                    consumers * co +
                    consumers * (f + k + l + r + s + t + v) +
                    consumers * 10 * e;

    return mem;
  }

  ~Sizes() {}

};
