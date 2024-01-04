cmake_minimum_required(VERSION 3.22)
project(kore_lib LANGUAGES CXX)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

message("Source files: ${SRC_FILES}")
message("Header files: ${HEADER_FILES}")
message("Include directory: ${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${CMAKE_PROJECT_NAME} pthread)
target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_23)
