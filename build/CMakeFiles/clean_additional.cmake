# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/real_time_plotter_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/real_time_plotter_autogen.dir/ParseCache.txt"
  "real_time_plotter_autogen"
  )
endif()
