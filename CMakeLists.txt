cmake_minimum_required(VERSION 3.16)
project(ClockworkWaveApp)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(APP_NAME "ClockworkWaveApp")

file(GLOB_RECURSE SRC_FILES "src/[A-Z]*.cpp")
add_executable(${APP_NAME} ${SRC_FILES})
target_link_libraries(${APP_NAME} be)
