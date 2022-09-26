#include "allocator.hpp"
#include "logger.hpp"

class B {
public:
    int b;
    double c;
};

class A {
public:
    A() { LOG("A()"); }
    // A(A a) { LOG("A(A a)"); }
    A(A& a) { LOG("A(A& a)"); }
    A(A&& a) { LOG("A(A&& a)"); }
    A(const A& a) { LOG("A(const A& a)"); }
    A(int a, B b) { LOG("A(int a, B b)"); }
    ~A() { LOG("~A()"); }

public:
    int a;
    B b;
};

int main() {
    typedef mystl::allocator<A> Allocator;
    
    // 分配内存
    A* alloc = Allocator::allocate();
    size_t n = 3;
    A* alloc1 = Allocator::allocate(n); // 不能用sizeof计算分配的内存大小
    
    // 构造对象
    Allocator::construct(alloc1);
    A a;
    const A& a_ref = a;
    Allocator::construct(alloc, a);
    Allocator::construct(alloc, a_ref);
    Allocator::construct(alloc, mystl::move(a));
    B b;
    Allocator::construct(alloc, 1, b);
    
    // 析构对象
    Allocator::destory(alloc);
    Allocator::destory(alloc1);

    // 释放内存
    Allocator::deallocate(alloc);
    Allocator::deallocate(alloc1, n);
}