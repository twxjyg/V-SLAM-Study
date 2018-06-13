cmake_minimum_required(VERSION 2.8)
project(hello)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_definitions(-DCOMPILEDWITHC11)
   

set(hello_lib_SRC
    src/hello.cpp
)

include_directories(
    include
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

message(${hello_lib_SRC} " in " ${PROJECT_NAME})

add_library(${PROJECT_NAME} SHARED
    ${hello_lib_SRC}
)

set(hello_SRC
    src/useHello.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/executable)

message(${hello_SRC})

add_executable(${PROJECT_NAME}_node
    ${hello_SRC}
)

target_link_libraries(${PROJECT_NAME}_node
    ${PROJECT_NAME}
)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
)

install(FILES include/hello.h
    DESTINATION include
)

