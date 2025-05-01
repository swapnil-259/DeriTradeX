cmake_minimum_required(VERSION 3.10)
project(DeriTradeX)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third-party
)

add_executable(DeriTradeX
    src/main.cpp
)
