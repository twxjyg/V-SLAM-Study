cmake_minimum_required(VERSION 2.8)

project(eigen_usage)

find_package(Eigen3 REQUIRED)

add_executable(eigen_usage
    src/use_eigen.cpp
)

add_executable(geometry_usage
    src/use_geometry.cpp
)
