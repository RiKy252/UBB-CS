# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Equations_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Equations_autogen.dir\\ParseCache.txt"
  "Equations_autogen"
  )
endif()
