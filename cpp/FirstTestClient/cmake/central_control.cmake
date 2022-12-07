# Proto file
get_filename_component(ft_proto "../../../protos/FirstTest.proto")
get_filename_component(ft_proto "${ft_proto}" PATH)

# Generated sources
set(ft_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/FirstTest.pb.cc")
set(ft_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/FirstTest.pb.h")
set(ft_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/FirstTest.grpc.pb.cc")
set(ft_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/FirstTest.grpc.pb.h")

add_custom_command(
    OUTPUT "${ft_proto_srcs}" "${ft_proto_hdrs}" "${ft_grpc_srcs}" "${ft_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${ft_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${ft_proto}"
      DEPENDS "${ft_proto}")

# Find head file      

macro(FIND_INCLUDE_DIR result curdir)
  file(GLOB_RECURSE children "${curdir}/*.h" "${curdir}//*.hpp")
  message(STATUS "children = ${children}")
  set(dirlist "")
  foreach(child ${children})
    string(REGEX REPLACE "(.*)/.*" "\\1" LIB_NAME ${child})
    if(IS_DIRECTORY ${LIB_NAME})
      if(dirlist MATCHES ${LIB_NAME})
      else()
        message(STATUS "current platform: Linux")
        LIST(APPEND dirlist ${LIB_NAME})
      endif()
    endif()
  endforeach()
  set(${result} ${dirlist})
endmacro()     