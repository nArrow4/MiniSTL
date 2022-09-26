#ifndef _MINISTL_UTILS_H
#define _MINISTL_UTILS_H

#include "type_traits.hpp"

namespace mystl{
    
template <typename T>
const T& max(const T& a, const T& b){
    return a > b ? a : b;
}

template <typename T>
T&& forward(typename std::remove_reference<T>::type& param) noexcept{
    return static_cast<T&&>(param);
}

template <typename T>
T&& forward(typename std::remove_reference<T>::type&& param) noexcept{
    // ? 这里是为啥
    static_assert(!std::is_lvalue_reference<T>::value, "bad forward");
    return static_cast<T&&>(param);
}

template <typename T>
typename std::remove_reference<T>::type&& move(T&& param) noexcept{
    return static_cast<typename std::remove_reference<T>::type&&>(param);
}



}

#endif // _MINISTL_UTILS_H