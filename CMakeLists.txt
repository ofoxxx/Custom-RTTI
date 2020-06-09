cmake_minimum_required (VERSION 3.8)

project ("CustomRTTI" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp TypeVisitor/TypeDispatcher.cpp)

add_subdirectory ("UTest/UTest")
include_directories("UTest/UTest")
target_link_libraries(main UTest)
