file (GLOB all_testing_files
    *.cpp
    strategies/*.cpp
)
                                
set (testing_files ${all_testing_files})

link_libraries(Simulation
  Helper)
  
add_library(Testing ${testing_files})
