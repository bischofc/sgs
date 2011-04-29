file (GLOB all_testing_files
    *.cpp
    other/*.cpp
    strategies/*.cpp
)
                                
set (testing_files ${all_testing_files})

add_library(Testing ${testing_files})