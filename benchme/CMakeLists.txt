cmake_minimum_required(VERSION 2.8)
set(BENCHME_NAME benchme)
set(${BENCHME_NAME} CXX)

#CXX
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -std=c++14 -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#INCLUDE
set(BENCHME_INCLUDE include/)

include_directories(${BENCHME_INCLUDE})
file(GLOB BENCHME_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
MESSAGE(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${BENCHME_NAME} ${BENCHME_SRC_FILES})
