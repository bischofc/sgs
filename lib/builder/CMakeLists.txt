file (GLOB all_builder_files *.cpp *.h)
set (builder_files ${all_builder_files})

add_library(Builder ${builder_files})
