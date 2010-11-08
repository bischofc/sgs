file (GLOB all_tinyxml_files *.cpp *.h)
set (tinyxml_files ${all_tinyxml_files})

add_library(TinyXML ${tinyxml_files})
