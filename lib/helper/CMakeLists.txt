file (GLOB all_helper_files *.cpp *.h)
set (helper_files ${all_helper_files})

add_library(Helper ${helper_files})
