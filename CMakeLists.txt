cmake_minimum_required (VERSION 2.4)

project (sgs)

set(CMAKE_CXX_FLAGS "-g -Wall -Wextra")

include_directories (
  ${CMAKE_SOURCE_DIR}/contrib/tinyxml
  ${CMAKE_SOURCE_DIR}/lib/helper
  ${CMAKE_SOURCE_DIR}/lib/simulation
  ${CMAKE_SOURCE_DIR}/lib/builder
  )

add_subdirectory (${CMAKE_SOURCE_DIR}/contrib/tinyxml)
add_subdirectory (${CMAKE_SOURCE_DIR}/lib/helper)
add_subdirectory (${CMAKE_SOURCE_DIR}/lib/simulation)
add_subdirectory (${CMAKE_SOURCE_DIR}/lib/builder)

add_executable (smgsim src/sgs.cpp)
target_link_libraries (smgsim Simulation)

add_executable (cbuilder src/cb.cpp)
target_link_libraries (cbuilder Builder)


###
## install
#
IF(${CMAKE_INSTALL_PREFIX} MATCHES /usr/local)
  SET(CMAKE_INSTALL_PREFIX "$ENV{HOME}/tmp/sgs")
ENDIF()

install(TARGETS smgsim DESTINATION bin)
install(TARGETS cbuilder DESTINATION bin)
#install (FILES etc/config.dtd DESTINATION etc)
install(FILES etc/exec.sh DESTINATION . PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
install(FILES etc/rscript DESTINATION . PERMISSIONS)
