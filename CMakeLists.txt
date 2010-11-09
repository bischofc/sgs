cmake_minimum_required (VERSION 2.6)

project (sgs)

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
