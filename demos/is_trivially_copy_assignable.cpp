/**
 * @Description:
 *      is_trivial: 是否有默认构造函数
 *      is_copy_assignable: 是否具有拷贝赋值运算符 
 *      is_trivially_copy_assignable: 是否有默认拷贝赋值运算符
 * @Email: zhiyyyu@gmail.com
 * @Author: Zehui Deng
 * @Github: nArrow4
 * @Date: 2022-10-16 19:27:42
 */
#include "logger.hpp"
#include <type_traits>

class A {
public:
    // 拷贝赋值运算符，非默认
    A& operator=(const A&) {
        return *this;
    }
};

class B {
    // Default
};

class C {
    virtual void func();
};

int main() {
    LOG(std::is_trivially_copy_assignable<A>{});            //F
    LOG(std::is_trivially_copy_assignable<A>::value);       //F
    LOG(std::is_trivially_copy_assignable<C>::value);       //F
    LOG(std::is_trivially_copy_assignable<B>::value);       //T

    LOG(std::is_trivially_copy_assignable<int>::value);     //T
    LOG(std::is_trivially_copy_assignable<int*>::value);    //T
    LOG(std::is_trivially_copy_assignable<int[2]>::value);  //F
}