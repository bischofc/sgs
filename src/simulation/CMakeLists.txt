file (GLOB all_simulation_files
    *.cpp
    consumers/*.cpp
    producers/*.cpp
    producers/devices/*.cpp
    energy/*.cpp
    energy/plans/*.cpp
)
                                
set (simulation_files ${all_simulation_files})

link_libraries(Simulation
  Helper
  Tinyxpath
  )
  
add_library(Simulation ${simulation_files})
