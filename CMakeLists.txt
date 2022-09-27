cmake_minimum_required(VERSION 3.16.3)

project(ministl)

include_directories(includes)

function(tests arg)
    list(GET ARGV 0 test_name)
    add_executable(${test_name} tests/${test_name}.cpp)
endfunction(tests)

tests(allocator_test)
tests(iterator_test)
tests(vector_test)

function(demos arg)
    list(GET ARGV 0 demo_name)
    add_executable(${demo_name} demos/${demo_name}.cpp)
endfunction(demos)

demos(template_parameter_pack)
demos(is_same)
demos(sfinae)
