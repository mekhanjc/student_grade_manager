# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\QManager_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\QManager_autogen.dir\\ParseCache.txt"
  "QManager_autogen"
  )
endif()
