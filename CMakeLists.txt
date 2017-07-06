cmake_minimum_required(VERSION 2.8)

add_subdirectory(${CMAKE_SOURCE_DIR}/benchme/)

#PRPA
find_package(Boost COMPONENTS graph REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(PROJECT_NAME prpa)
set(${PROJECT_NAME} CXX)
cmake_policy(SET CMP0042 NEW)

#CXX
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -std=c++14 -pedantic -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#INCLUDE
set(PROJECT_INCLUDE src/)

include_directories(${PROJECT_INCLUDE})
file(GLOB PROJECT_SRC_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/loader/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/graph/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/greedy/*.cc
)

add_executable(${PROJECT_NAME} ${PROJECT_SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${Boost_PROGRAM_OPTIONS_LIBRARY})

add_custom_target(
  run
  DEPENDS
  ${PROJECT_NAME}
  COMMAND
  ./${PROJECT_NAME}
)
