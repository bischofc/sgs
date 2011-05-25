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
install(FILES etc/plotGraphs
  etc/springWindIsFactor.txt   etc/springSolarIsFactor.txt
  etc/summerWindIsFactor.txt   etc/summerSolarIsFactor.txt
  etc/fallWindIsFactor.txt     etc/fallSolarIsFactor.txt
  etc/winterWindIsFactor.txt   etc/winterSolarIsFactor.txt
#  etc/springWindPlanFactor.txt etc/springSolarPlanFactor.txt
#  etc/summerWindPlanFactor.txt etc/summerSolarPlanFactor.txt
#  etc/fallWindPlanFactor.txt   etc/fallSolarPlanFactor.txt
#  etc/winterWindPlanFactor.txt etc/winterSolarPlanFactor.txt
  etc/expectedLoad
  DESTINATION etc PERMISSIONS)
