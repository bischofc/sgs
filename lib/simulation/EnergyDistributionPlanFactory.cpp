
#include <EnergyDistributionPlanFactory.h>

namespace simulation {
namespace config {

EnergyDistributionPlan * EnergyDistributionPlanFactory::getInstance(std::string type, std::map<std::string, std::string> params) throw (exception::NoSuchEnergyPlanException){
  if(type == "static") {
    std::map<std::string, std::string>::iterator it;
    std::stringstream s;
    int rate;

    it = params.find("rate");
    s << it->second;
    s >> rate;
    return new EnergyDistributionPlanStatic (rate);
  }
  if(type == "repeat") {
//    std::map<std::string, std::string>::iterator it;
//    std::stringstream s;
//    int rate;

//    it = params.find("rate");
//    s << it->second;
//    s >> rate;
    return new EnergyDistributionPlanRepeat (5, 3, 1, 10);  //todo richtige values
    }
  throw exception::NoSuchEnergyPlanException("The given type of energy plan is not implemented. Feel free to do so!");
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
