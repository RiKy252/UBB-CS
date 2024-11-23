# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\OOPPracticalExam_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\OOPPracticalExam_autogen.dir\\ParseCache.txt"
  "OOPPracticalExam_autogen"
  )
endif()
