#include "logger.hpp"

class A {
public:
    typedef int a;
    void func_a() { LOG("func_a"); }
};

class B {
public:
    typedef int b;
    void func_b() {}
};

template <typename T, typename M>
struct has_member {
private:
    struct two { char a; char b; };
    template <typename U>
    static two test(...);
    template <typename U>
    static char test(M );
public:
    static const bool value = sizeof(test<T>(0)) == sizeof(char);
};

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
    struct two { char a; char b; };
    template <typename U>
    static two test(...);
    template <typename U>
    static char test(decltype(&U::func_a) = 0);
public:
    static const bool value = sizeof(test<T>(NULL)) == sizeof(char);
};

int main() {
    
    // 这里的aa是函数指针，但是因为func_a不是静态成员函数，所以这里的地址是不正确的
    decltype(&A::func_a) aa;
    
    LOG(has_a<A>::value);
    LOG(has_a<B>::value);
    LOG(has_func_a<A>::value);
    LOG(has_func_a<B>::value);

    LOG((has_member<A, A::a>::value));
    LOG((has_member<B, A::a>::value));
    LOG((has_member<A, decltype(&A::func_a)>::value));
    LOG((has_member<B, decltype(&A::func_a)>::value));

    
}