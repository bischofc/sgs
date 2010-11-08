cmake_minimum_required (VERSION 2.6)

project (sgs)

include_directories (
  ${CMAKE_SOURCE_DIR}/contrib/tinyxml
  ${CMAKE_SOURCE_DIR}/lib/helper
  ${CMAKE_SOURCE_DIR}/lib/simulation
  )

add_subdirectory (${CMAKE_SOURCE_DIR}/contrib/tinyxml)
add_subdirectory (${CMAKE_SOURCE_DIR}/lib/helper)
add_subdirectory (${CMAKE_SOURCE_DIR}/lib/simulation)

link_libraries (Simulation)
add_executable (smgsim src/sgs.cpp)
