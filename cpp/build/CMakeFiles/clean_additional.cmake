# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/CentralControlClient_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/CentralControlClient_autogen.dir/ParseCache.txt"
  "CMakeFiles/cp_grpc_proto_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/cp_grpc_proto_autogen.dir/ParseCache.txt"
  "CMakeFiles/cq_grpc_proto_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/cq_grpc_proto_autogen.dir/ParseCache.txt"
  "CentralControlClient_autogen"
  "cp_grpc_proto_autogen"
  "cq_grpc_proto_autogen"
  )
endif()
