# MiniSTL

基于C++11的小型STL，主要用于学习现代C++

# Dependence

* Win11 + WSL2 + Ubuntu20.04
* cmake 3.16.3
* g++ 9.4.0
* gtest

# Build & Run

```sh
git clone https://github.com/nArrow4/MiniSTL.git
mkdir build && cd build
cmake ..
make -j4
./${test_demo_name}
```

# Finished

* allocator
* constructor

# Working On

* iterator
* vector

# TODO

* list
* deque
* queue
* stack
* map
* set
* unordered_map
* unordered_set

* algorithm
* functional

* gtest

# Tutorial

[记录一下学习过程中的笔记](./docs/Tutorial.md)