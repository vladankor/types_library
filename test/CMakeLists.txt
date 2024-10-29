cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(TEST test_${PROJECT_NAME})

file(GLOB_RECURSE TEST_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE TEST_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

message("Tests source files: ${TEST_SRC_FILES}")
message("Tests header files: ${TEST_HEADER_FILES}")
message("Tests include directory: ${CMAKE_CURRENT_SOURCE_DIR}")

set (Boost_USE_STATIC_LIBS OFF)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(${TEST} ${TEST_SRC_FILES})
target_link_libraries(${TEST} ${Boost_LIBRARIES} ${CMAKE_PROJECT_NAME})