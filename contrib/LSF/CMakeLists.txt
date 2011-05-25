file (GLOB all_lsf_files *.cpp)
set (lsf_files ${all_lsf_files})
add_library(LSF ${lsf_files})
