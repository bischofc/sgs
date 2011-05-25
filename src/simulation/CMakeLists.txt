file (GLOB all_simulation_files
    *.cpp
    consumers/*.cpp
    consumers/strategies/*.cpp
    producers/*.cpp
    producers/devices/*.cpp
    energy/*.cpp
    energy/plans/*.cpp
)
                                
set (simulation_files ${all_simulation_files})
  
add_library(Simulation ${simulation_files})

target_link_libraries(Simulation Helper Tinyxpath LSF)
