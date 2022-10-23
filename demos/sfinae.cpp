/**
 * @Description: 
 *      SFINAE: Substitution Failure Is Not An Error.
 *      目前接触过的用法主要是判断类是否有某个变量或方法
 *      原理是利用函数重载决议，实现编译器匹配
 *      has_a、has_func_a、has_member
 *      这里has_a和has_func_a用了两种不同的写法
 * @Email: zhiyyyu@gmail.com
 * @Author: Zehui Deng
 * @Github: nArrow4
 * @Date: 2022-09-27 17:21:48
 */
#include "logger.hpp"

class A {
public:
    typedef int a;
    void func_a() { LOG("func_a"); }
    static void static_func_a() { LOG("static func_a"); }
};

class B {
public:
    typedef int b;
    void func_b() { LOG("func_b"); }
};

// template <typename T, typename M>
// struct has_member {
//     template <typename U>
//     static std::false_type test(...);
//     template <typename U>
//     static std::true_type test(M* = 0);
// public:
//     enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
// };

/**
 * @brief: 第二个test函数中，模板传入U::a类型
 *      如果此时U是类A，则含有a，匹配成功
 *      如果此时U是int，则int::a会产生编译错误，
 *      但由于SFINAE，不会报错，而是匹配到第一个test函数
 */
template <typename T>
struct has_a {
private:
    struct two { char a; char b; };
    template <typename U>
    static two test(...);
    template <typename U>
    static char test(typename U::a* = 0);
public:
    static const bool value = sizeof(test<T>(0)) == sizeof(char);
};

template <typename T>
struct has_func_a {
private:
    template <typename U>
    static std::false_type test(...);
    template <typename U>
    static std::true_type test(decltype(std::declval<U>().func_a())* = 0);
public:
    enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
};

int main() {
    
    // 这里的aa是函数指针，但是因为func_a不是静态成员函数，所以这里的地址是不正确的
    // decltype(&A::func_a) aa;
    
    LOG(has_a<A>::value);
    LOG(has_a<B>::value);
    LOG(has_func_a<A>::value);
    LOG(has_func_a<B>::value);

    // LOG((has_member<A, A::a>::value));
    // LOG((has_member<B, A::a>::value));
    // LOG((has_member<A, decltype(&A::func_a)>::value));
    // LOG((has_member<B, decltype(&A::func_a)>::value));

    /* result:
        1010
    */
}