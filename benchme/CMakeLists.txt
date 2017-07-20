cmake_minimum_required(VERSION 2.8)
set(BENCHME_NAME benchme)
set(${BENCHME_NAME} CXX)
cmake_policy(SET CMP0042 NEW)

set(PROJECT_NAME prpa)

#CXX
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -std=c++14 -pedantic -O3 -pthread")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#INCLUDE
set(BENCHME_INCLUDE include/)

include_directories(${BENCHME_INCLUDE})
file(GLOB BENCHME_SRC_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
)

file(GLOB BENCHME_TEST_FILES
  ${CMAKE_SOURCE_DIR}/src/*.cc
  ${CMAKE_SOURCE_DIR}/src/loader/*.cc
  ${CMAKE_SOURCE_DIR}/src/graph/*.cc
  ${CMAKE_SOURCE_DIR}/src/spanner/*.cc
)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(${BENCHME_NAME} ${BENCHME_SRC_FILES})
target_link_libraries(${BENCHME_NAME}
                      ${CMAKE_DL_LIBS}
                      ${CMAKE_RT_LIBS}
                      _${PROJECT_NAME})

add_library(${BENCHME_NAME}_greedy SHARED ${CMAKE_CURRENT_SOURCE_DIR}/test/greedy_bench.cc)
add_library(${BENCHME_NAME}_parallel_greedy SHARED ${CMAKE_CURRENT_SOURCE_DIR}/test/parallel_greedy_bench.cc)

add_custom_target(
  benchme_check
  DEPENDS
  ${BENCHME_NAME}
  COMMAND
  ./${BENCHME_NAME}
)
