cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 17)

project(kosaraju_scc)

add_executable(kosaraju_scc
 ${CMAKE_SOURCE_DIR}/main.cpp
 ${CMAKE_SOURCE_DIR}/graph.h
 ${CMAKE_SOURCE_DIR}/kosaraju.h
 )
