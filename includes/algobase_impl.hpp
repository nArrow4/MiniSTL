#ifndef _MINISTL_ALGOBASE_IMPL_H
#define _MINISTL_ALGOBASE_IMPL_H

#include <cstring>
#include <type_traits>

#include "iterator.hpp"

namespace mystl {

/**** fill_n ****/

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
unchecked_fill_n(OutputIter first, Size n, const T& value) {
    for(; n > 0; n--, first++) {
        *first = value;
    }
    return first;
}

/**** copy ****/
template <typename Tp, typename Up>
typename std::enable_if<
    std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
    std::is_trivially_copy_assignable<Up>::value
    , Up*>::type
unchecked_copy(Tp* first, Tp* last, Up* result) {
    const auto n = static_cast<size_t>(last - first);
    if(n != 0) {
        std::memmove(result, first, n * sizeof(Up));
    }
    return result + n;
}

/**** move ****/

template <typename InputIter, typename OutputIter>
OutputIter
unchecked_move_cat(InputIter first, InputIter last, OutputIter result, input_iterator_tag) {
    for(; first != last; first++, result++) {
        *result = mystl::move(*first);
    }
    return result;
}

template <typename InputIter, typename OutputIter>
OutputIter
unchecked_move_cat(InputIter first, InputIter last, OutputIter result, random_access_iterator_tag) {
    for(auto n = last - first; n > 0; n--, result++) {
        *result = mystl::move(*first);
    }
    return result;
}

/**
 * @brief: 
 */
template <typename InputIter, typename OutputIter>
OutputIter 
unchecked_move(InputIter first, InputIter last, OutputIter result) {
    return unchecked_move_cat(first, last, result, 
        iterator_category(first));
}

/**
 * @brief: trivially move assignable 版本
 */
template <typename Tp, typename Up>
typename std::enable_if<
    std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
    std::is_trivially_move_assignable<Up>::value
    , Up*>::type
unchecked_move(Tp* first, Tp* last, Up* result) {
    const size_t n = static_cast<size_t>(last - first);
    if(n != 0)
        std::memmove(result, first, n);
    return result + n;
}


/**** copy_backward ****/
/**
 * @brief: bidirectional_iterator特化，
 *      可以从后往前访问
 */
template <typename BidirectionalIter1, typename BidirectionalIter2>
BidirectionalIter2
unchecked_copy_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result,
    mystl::bidirectional_iterator_tag) {
    while(first != last) {
        *--result = *--last;
    }
    return result;
}

/**
 * @brief: random_access_iterator特化，
 *      可以随机访问，先计算copy的数量，防止异常情况
 */
template <typename BidirectionalIter1, typename BidirectionalIter2>
BidirectionalIter2
unchecked_copy_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result,
    mystl::random_access_iterator_tag) {
    for(auto n = last - first; n > 0; n--) {
        *--result = *--last;
    }
    return result;
}

template <typename BidirectionalIter1, typename BidirectionalIter2>
BidirectionalIter2
unchecked_copy_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result) {
    return unchecked_copy_backward_cat(first, last, result, 
        iterator_category(first));
}

template <typename Tp, typename Up>
typename std::enable_if<
    std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
    std::is_trivially_copy_assignable<Up>::value,
    Up*>::type
unchecked_copy_backward(Tp* first, Tp* last, Up* result) {
    const auto n = static_cast<size_t>(last - first);
    if(n == 0) return result;
    result -= n;
    memmove(result, first, n * sizeof(Up));
    return result;
}

/**** fill ****/
template <typename ForwardIter, typename T>
void
fill_cat(ForwardIter first, ForwardIter last, const T& value, 
    mystl::forward_iterator_tag) {
    for(; first != last; ++first) {
        *first = value;
    }
}

template <typename RandomIter, typename T>
void
fill_cat(RandomIter first, RandomIter last, const T& value,
    mystl::random_access_iterator_tag ) {
    fill_n(first, static_cast<size_t>(last - first), value);
}

}

#endif // _MINISTL_ALGOBASE_IMPL_H