cmake_minimum_required(VERSION 3.14)

project(CentralControlClient C CXX)

include(../cmake/common.cmake)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

# Proto file
get_filename_component(cq_proto "../../protos/CentralControlRequest.proto" ABSOLUTE)
get_filename_component(cq_proto_path "${cq_proto}" PATH)
get_filename_component(cp_proto "../../protos/CentralControlResponse.proto" ABSOLUTE)
get_filename_component(cp_proto_path "${cp_proto}" PATH)

# Generated sources
set(cq_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/CentralControlRequest.pb.cc")
set(cq_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/CentralControlRequest.pb.h")
set(cq_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/CentralControlRequest.grpc.pb.cc")
set(cq_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/CentralControlRequest.grpc.pb.h")

set(cp_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/CentralControlResponse.pb.cc")
set(cp_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/CentralControlResponse.pb.h")
set(cp_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/CentralControlResponse.grpc.pb.cc")
set(cp_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/CentralControlResponse.grpc.pb.h")

add_custom_command(
      OUTPUT "${cq_proto_srcs}" "${cq_proto_hdrs}" "${cq_grpc_srcs}" "${cq_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${cq_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${cq_proto}"
      DEPENDS "${cq_proto}")


add_custom_command(
        OUTPUT "${cp_proto_srcs}" "${cp_proto_hdrs}" "${cp_grpc_srcs}" "${cp_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
          --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
          -I "${cp_proto_path}"
          --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
          "${cp_proto}"
        DEPENDS "${cp_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# cq_grpc_proto
add_library(cq_grpc_proto
  ${cq_grpc_srcs}
  ${cq_grpc_hdrs}
  ${cq_proto_srcs}
  ${cq_proto_hdrs})
add_library(cp_grpc_proto
    ${cp_grpc_srcs}
    ${cp_grpc_hdrs}
    ${cp_proto_srcs}
    ${cp_proto_hdrs})
target_link_libraries(cq_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})
target_link_libraries(cp_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

add_executable(CentralControlClient
  main.cpp
)
target_link_libraries(CentralControlClient
    Qt${QT_VERSION_MAJOR}::Core
    cq_grpc_proto
    cp_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})

install(TARGETS CentralControlClient
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
