#include <iostream>

#define DEBUG

namespace mystl{

#ifdef DEBUG

#define LOG(str) \
    std::cout << str << std::endl;

#else

#define LOG(str)

#endif

}