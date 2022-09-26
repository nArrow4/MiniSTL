cmake_minimum_required(VERSION 3.16.3)

project(ministl)

include_directories(includes)

function(tests arg)
    list(GET ARGV 0 demo_name)
    add_executable(${demo_name} tests/${demo_name}.cpp)
endfunction(tests)

tests(vector_demo)
