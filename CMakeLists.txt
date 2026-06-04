cmake_minimum_required(VERSION 3.23)
project(kitsune-pi CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(kitsune-pi main.cpp incStat.cpp incStat_cov.cpp)

target_include_directories(kitsune-pi PRIVATE incStat.hpp incStat_cov.hpp)
