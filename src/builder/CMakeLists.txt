file (GLOB all_builder_files *.cpp)
set (builder_files ${all_builder_files})

link_libraries(Builder Helper)

add_library(Builder ${builder_files})
