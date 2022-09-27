#ifndef _MINISTL_CONSTRUCTOR_H
#define _MINISTL_CONSTRUCTOR_H

#include <new>  // placement new
#include "utils.hpp"

namespace mystl {

template <typename T>
void construct(T* ptr)
{
    // 转成void*是因为placement new的形参是void*
    ::new ((void*) ptr) T();
}

template <typename T1, typename T2>
void construct(T1* ptr, const T2& value)
{
    ::new ((void*) ptr) T1(value);
}

template <typename T, typename ... Args>
void construct(T* ptr, Args&&... args)
{
    ::new ((void*) ptr) T(mystl::forward<Args>(args)...);
}

template <typename T>
void destroy_one(T* ptr, std::true_type)
{ }

template <typename T>
void destroy_one(T* ptr, std::false_type)
{
    if(!ptr) return;
    ptr->~T();
}

template <typename ForwardIter>
void destroy_aux(ForwardIter* first, ForwardIter* last, std::true_type t)
{ }

template <typename ForwardIter>
void destroy_aux(ForwardIter* first, ForwardIter* last, std::false_type t)
{
    
}

template <typename T>
void destory(T* ptr)
{
    destroy_one(ptr, std::is_trivially_destructible<T>{});
}

template <typename ForwardIter>
void destory(ForwardIter* first, ForwardIter* last)
{
    // destroy_aux(first, last);
}

}

#endif // _MINISTL_CONSTRUCTOR_H