cmake_minimum_required(VERSION 3.14)

project(FirstTestClient C CXX)

include(../cmake/common.cmake)
include(./cmake/central_control.cmake)

FIND_INCLUDE_DIR(INCLUDE_DIR_LIST ${PROJECT_SOURCE_DIR}/include)
file(GLOB_RECURSE SRC_DIR_LIST "src/*.cpp")
message(STATUS "SRC_DIR_LIST = ${SRC_DIR_LIST}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}" "${INCLUDE_DIR_LIST}")

# ft_grpc_ptoro
add_library(ft_grpc_proto
    ${ft_grpc_srcs}
    ${ft_grpc_hdrs}
    ${ft_proto_srcs}
    ${ft_proto_hdrs})
target_link_libraries(ft_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})

add_library(FirstTest
    ${INCLUDE_DIR_LIST}
    ${SRC_DIR_LIST})
target_link_libraries(
    FirstTest
    ft_grpc_proto)

add_executable(FirstTestClient
    main.cpp)
target_link_libraries(FirstTestClient
    ft_grpc_proto
    FirstTest
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})

install(TARGETS FirstTestClient
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
