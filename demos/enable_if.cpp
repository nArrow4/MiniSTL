/**
 * @Description: 
 * @Email: zhiyyyu@gmail.com
 * @Author: Zehui Deng
 * @Github: nArrow4
 * @Date: 2022-10-16 16:00:10
 */
#include "logger.hpp"
#include <type_traits>

int main() {
    std::enable_if<true, int>::type a;
    // std::enable_if<false, int>::type a;
    LOG(std::is_same<decltype(a), int>::value);
    
}