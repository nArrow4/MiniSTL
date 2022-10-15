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

# tests(allocator_test)
# tests(iterator_test)
# tests(vector_test)
tests(gtest_demo)

function(demos arg)
    list(GET ARGV 0 demo_name)
    add_executable(${demo_name} demos/${demo_name}.cpp)
endfunction(demos)

demos(template_parameter_pack)
demos(is_same)
demos(is_convertable)
demos(sfinae)
demos(iterator_type)
