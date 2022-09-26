#ifndef _MINISTL_LOGGER_H
#define _MINISTL_LOGGER_H

#include <iostream>

#define DEBUG

namespace mystl{

#ifdef DEBUG

#define LOG(str) \
    std::cout << str << std::endl

#else

#define LOG(str)

#endif

}

#endif // _MINISTL_LOGGER_H