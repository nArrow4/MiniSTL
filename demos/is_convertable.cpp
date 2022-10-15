/**
 * @Description: 
 * @Email: zhiyyyu@gmail.com
 * @Author: Zehui Deng
 * @Github: nArrow4
 * @Date: 2022-10-16 01:33:43
 */
#include "logger.hpp"
#include <type_traits>

class A {};

int main() {
    LOG(std::is_convertible<int, char>::value);
    LOG(std::is_convertible<int, A>::value);
}