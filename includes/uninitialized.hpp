#ifndef _MINISTL_UNINITIALIZED_H
#define _MINISTL_UNINITIALIZED_H

#include <cstring>
#include "allocator.hpp"
#include "constructor.hpp"
#include "iterator.hpp"

namespace mystl {

template <typename Tp, typename Size, typename Up>
typename std::enable_if<
    std::is_integral<Tp>::value && sizeof(Tp) == 1 && 
    std::is_same<Tp, bool>::value &&
    std::is_integral<Up>::value && sizeof(Up) == 1,
    Tp*>::type
unchecked_fill_n(Tp* first, Size n, Up value) {
    if(n > 0) {
        std::memset(first, (unsigned char) value, (size_t) n);
    }
    return first + n;
}
    

template <typename OutputIter, typename Size, typename T>
OutputIter
fill_n(OutputIter first, Size n, const T& value) {
    return unchecked_fill_n(first, n, value);
}

template <typename ForwardIter, typename Size, typename T>
ForwardIter
unchecked_uninit_fill_n(ForwardIter first, Size n, const T& value, std::true_type) {
    return fill_n(first, n, value);
}

template <typename ForwardIter, typename Size, typename T>
ForwardIter
unchecked_uninit_fill_n(ForwardIter first, Size n, const T& value, std::false_type) {
    auto cur = first;
    try {
        for(; n > 0; n--, cur++) mystl::construct(&*cur, value);
    } catch(...) {
        for(; first != cur; first++) mystl::destory(&*first);
    }
    return cur;
}

template <typename ForwardIter, typename Size, typename T>
ForwardIter 
uninitialized_fill_n(ForwardIter first, Size n, const T& value) {
    return unchecked_uninit_fill_n(first, n, value, 
        std::is_trivially_copy_assignable<typename 
        iterator_traits<ForwardIter>::value_type>{} );
}

template <class InputIter, class ForwardIter>
ForwardIter
uninitialized_copy(InputIter first, InputIter last, ForwardIter result) {

}

}

#endif // _MINISTL_UNINITIALIZED_H