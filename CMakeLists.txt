cmake_minimum_required (VERSION 2.4)

project (sgs)

#SET(CMAKE_CXX_FLAGS "-g -Wall -Wextra -pg")
SET(CMAKE_CXX_FLAGS "-g -Wall -Wextra")


###
## includes and subdirectories
#

include_directories (
  ${CMAKE_SOURCE_DIR}/contrib/tinyxpath
  ${CMAKE_SOURCE_DIR}/contrib/LSF
  ${CMAKE_SOURCE_DIR}/src/helper
  ${CMAKE_SOURCE_DIR}/src/simulation
  ${CMAKE_SOURCE_DIR}/src/builder
  ${CMAKE_SOURCE_DIR}/testing
  )

add_subdirectory (${CMAKE_SOURCE_DIR}/contrib/tinyxpath)
add_subdirectory (${CMAKE_SOURCE_DIR}/contrib/LSF)
add_subdirectory (${CMAKE_SOURCE_DIR}/src/helper)
add_subdirectory (${CMAKE_SOURCE_DIR}/src/simulation)
add_subdirectory (${CMAKE_SOURCE_DIR}/src/builder)
add_subdirectory (${CMAKE_SOURCE_DIR}/testing)


###
## executables and linking
#

add_executable (smgsim src/sgs.cpp)
target_link_libraries (smgsim Simulation)

add_executable (cbuilder src/cb.cpp)
target_link_libraries (cbuilder Builder)

add_executable (test testing/testing.cpp)
target_link_libraries (test Testing Helper Simulation)

###
## install
#

IF(${CMAKE_INSTALL_PREFIX} MATCHES /usr/local)
  SET(CMAKE_INSTALL_PREFIX "$ENV{HOME}/tmp/sgs")
ENDIF(${CMAKE_INSTALL_PREFIX} MATCHES /usr/local)

install(TARGETS smgsim DESTINATION bin)
install(TARGETS cbuilder DESTINATION bin)
install(TARGETS test DESTINATION bin)
#install (FILES etc/config.dtd DESTINATION etc)
install(FILES etc/exec.sh DESTINATION . PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
install(FILES etc/plotGraphs DESTINATION etc PERMISSIONS)
install(FILES etc/data/expectedLoad
#  etc/data/springWindIsFactor.txt   etc/data/springSolarIsFactor.txt
  etc/data/summerWindIsFactor.txt   etc/data/summerSolarIsFactor.txt
#  etc/data/fallWindIsFactor.txt     etc/data/fallSolarIsFactor.txt
#  etc/data/winterWindIsFactor.txt   etc/data/winterSolarIsFactor.txt
#  etc/data/springWindPlanFactor.txt etc/data/springSolarPlanFactor.txt
  etc/data/summerWindPlanFactor.txt etc/data/summerSolarPlanFactor.txt
#  etc/data/fallWindPlanFactor.txt   etc/data/fallSolarPlanFactor.txt
#  etc/data/winterWindPlanFactor.txt etc/data/winterSolarPlanFactor.txt
  DESTINATION etc/data PERMISSIONS)
