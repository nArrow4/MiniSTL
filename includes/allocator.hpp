#ifndef _MINISTL_ALLOCATOR_H
#define _MINISTL_ALLOCATOR_H

#include <cstddef>
#include "constructor.hpp"
#include "logger.hpp"


namespace mystl{

template <class T>
class allocator{

// STL规范规定的必要接口
public:
    // 定义一些数据类型
    typedef T           value_type;
    typedef T*          pointer;
    typedef T*          iterator;
    typedef const T*    const_pointer;
    typedef T&          reference;
    typedef const T&    const_reference;
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;

public:
    // 静态构造函数
    static pointer allocate();
    static pointer allocate(size_type n);

    static void deallocate(pointer ptr);
    static void deallocate(pointer ptr, size_type n);

    static void construct(pointer ptr);
    static void construct(pointer ptr, const_reference value);
    static void construct(pointer ptr, T&& value);
    template <typename ... Args>
    static void construct(pointer ptr, Args&&...  args);

    static void destory(pointer ptr);
    static void destory(iterator first, iterator last);
};

// 分配单个变量的空间
template <typename T>
T* allocator<T>::
allocate()
{
    LOG("allocate()");
    return static_cast<T*>(::operator new(sizeof(T))); 
}

template <typename T>
T* allocator<T>::
allocate(size_type n)
{
    LOG("allocate(size_type n)");
    if(n == 0) return nullptr;
    // ::operator new 只会分配内存，不会调用构造函数
    return static_cast<T*>(::operator new(n * sizeof(T)));
}

template <typename T>
void allocator<T>::
deallocate(T* ptr)
{
    LOG("deallocate(T* ptr)");
    if(!ptr) return;
    ::operator delete(ptr);
}

template <typename T>
void allocator<T>::
deallocate(T* ptr, size_type n)
{
    LOG("deallocate(T* ptr, size_type n)");
    if(!ptr) return;
    ::operator delete(ptr);
}

template <typename T>
void allocator<T>::
construct(T* ptr)
{
    LOG("construct(T* ptr)");
    mystl::construct(ptr);
}

template <typename T>
void allocator<T>::
construct(T* ptr, const T& value)
{
    LOG("construct(T* ptr, const T& value)");
    mystl::construct(ptr, value);
}

template <typename T>
void allocator<T>::
construct(T* ptr, T&& value)
{
    LOG("construct(T* ptr, T&& value)");
    mystl::construct(ptr, move(value));
}

template <typename T>
template <typename ...Args>
void allocator<T>::
construct(T* ptr, Args&&... args)
{
    LOG("construct(T* ptr, Args&& ... args)");
    mystl::construct(ptr, mystl::forward<Args>(args)...);
}

template <typename T>
void allocator<T>::
destory(T* ptr)
{
    LOG("destory(T* ptr)");
    mystl::destory(ptr);
}

template <typename T>
void allocator<T>::
destory(T* first, T* last)
{
    LOG("destory(T* first, T* last)");
    mystl::destory(first, last);
}

}

#endif // _MINISTL_ALLOCATOR_H