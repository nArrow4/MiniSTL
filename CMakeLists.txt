cmake_minimum_required(VERSION 3.16.3)

project(ministl)
# 项目中使用C++11，GTest需要C++14
set(CMAKE_CXX_STANDARD 14)

enable_testing()

find_package(GTest REQUIRED)

include_directories(includes)
include_directories(${GTEST_INCLUDE_DIRS})

function(tests arg)
    list(GET ARGV 0 test_name)
    add_executable(${test_name} tests/${test_name}.cpp)
    target_link_libraries(${test_name} ${GTEST_BOTH_LIBRARIES} pthread) 
    gtest_discover_tests(${test_name})
endfunction(tests)

file(GLOB TESTS tests/*.cpp)
foreach(FILE_PATH ${TESTS})
    message("processing " ${FILE_PATH})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FILE_PATH})
    # message(${FILE_NAME})
    tests(${FILE_NAME})
endforeach()

function(demos arg)
    list(GET ARGV 0 demo_name)
    add_executable(${demo_name} demos/${demo_name}.cpp)
endfunction(demos)

file(GLOB DEMOS demos/*.cpp)
foreach(FILE_PATH ${DEMOS})
    message("processing " ${FILE_PATH})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FILE_PATH})
    # message(${FILE_NAME})
    demos(${FILE_NAME})
endforeach()