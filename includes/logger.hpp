/**
 * @Description: 
 * @Email: zhiyyyu@gmail.com
 * @Author: Zehui Deng
 * @Github: nArrow4
 * @Date: 2022-09-25 19:33:58
 */
#ifndef _MINISTL_LOGGER_H
#define _MINISTL_LOGGER_H

#include <iostream>

#define DEBUG

namespace mystl{

#ifdef DEBUG

#define LOG(str...) \
    std::cout << str << std::endl

#else

#define LOG(str)

#endif

}

#endif // _MINISTL_LOGGER_H