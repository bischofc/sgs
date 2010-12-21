
#include <EnergyDistributionPlanFactory.h>

namespace simulation {
namespace config {

// TODO: throw exceptions if params are not met

EnergyDistributionPlan * EnergyDistributionPlanFactory::getInstance(std::string type, std::map<std::string, std::string> params) throw (exception::NoSuchEnergyPlanException){
  if(type == "static") {
    std::map<std::string, std::string>::iterator it;
    std::stringstream s;
    int start, end, rate;

    it = params.find("start"); s << it->second; s >> start; s.clear();
    it = params.find("end"); s << it->second; s >> end; s.clear();
    it = params.find("rate"); s << it->second; s >> rate; s.clear();
    return new EnergyDistributionPlanStatic (start, end, rate);
  }
  if(type == "repeat") {
    std::map<std::string, std::string>::iterator it;
    std::stringstream s;
    int start, end, period, highTime, lowEnergy, highEnergy;

    it = params.find("start"); s << it->second; s >> start; s.clear();
    it = params.find("end"); s << it->second; s >> end; s.clear();
    it = params.find("period"); s << it->second; s >> period; s.clear();
    it = params.find("highTime"); s << it->second; s >> highTime; s.clear();
    it = params.find("lowEnergy"); s << it->second; s >> lowEnergy; s.clear();
    it = params.find("highEnergy"); s << it->second; s >> highEnergy;
    return new EnergyDistributionPlanRepeat (start, end, period, highTime, lowEnergy, highEnergy);
    }
  throw exception::NoSuchEnergyPlanException("The given type of energy plan is not implemented. Feel free to do so!");
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
