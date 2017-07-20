cmake_minimum_required(VERSION 2.8)

add_subdirectory(${CMAKE_SOURCE_DIR}/benchme/)

#PRPA
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/)
find_package(Boost COMPONENTS graph program_options REQUIRED)
find_package(TBB)
include_directories(${TBB_INCLUDE_DIRS})
add_definitions(${TBB_DEFINITIONS})
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
  ${CMAKE_CURRENT_SOURCE_DIR}/src/loader/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/graph/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/spanner/*.cc
)

add_library(_${PROJECT_NAME} SHARED ${PROJECT_SRC_FILES})
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc)

target_link_libraries(${PROJECT_NAME}
  _${PROJECT_NAME})

target_link_libraries(_${PROJECT_NAME}
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${TBB_LIBRARIES})

add_custom_target(
  greedy
  DEPENDS
  ${PROJECT_NAME}
  COMMAND
  ./${PROJECT_NAME} --greedy --data ../dataset/us_cities.csv --t 1.5 --trace
)

add_custom_target(
  wspd
  DEPENDS
  ${PROJECT_NAME}
  COMMAND
  ./${PROJECT_NAME} --wspd --data ../dataset/us_cities.csv --t 1.5 --trace
)
