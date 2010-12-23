
#include "EnergyPlanFactory.h"

namespace simulation {
namespace config {

// TODO: throw exceptions if params are not met

EnergyPlan * EnergyPlanFactory::getInstance(std::string type, std::map<std::string, int> params) throw (exception::NoSuchEnergyPlanException){
  if(type == "static" || type == "dynamic") {
    std::map<std::string, int>::iterator it;
    int start, end, period, highTime, lowEnergy, highEnergy;

    it = params.find("start"); start = it->second;
    it = params.find("end"); end = it->second;
    it = params.find("period"); period = it->second;
    it = params.find("highTime"); highTime = it->second;
    it = params.find("lowEnergy"); lowEnergy = it->second;
    it = params.find("highEnergy"); highEnergy = it->second;

    if(type == "static") return new EnergyPlanStatic (start, end, period, highTime, lowEnergy, highEnergy);
    if(type == "dynamic") return new EnergyPlanDynamic (start, end, period, highTime, lowEnergy, highEnergy);
    }
  throw exception::NoSuchEnergyPlanException("The given type of energy plan is not implemented. Feel free to do so!");
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
