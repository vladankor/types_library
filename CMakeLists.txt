cmake_minimum_required(VERSION 3.22)
project(kore_lib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

message("Source files: ${SRC_FILES}")
message("Header files: ${HEADER_FILES}")
message("Include directory: ${CMAKE_CURRENT_SOURCE_DIR}")

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_library(${CMAKE_PROJECT_NAME} ${SRC_FILES})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${CMAKE_PROJECT_NAME} pthread)
    target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_23)
endif()

add_subdirectory(test)

enable_testing()