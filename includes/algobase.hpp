#ifndef _MINISTL_ALGOBASE_H
#define _MINISTL_ALGOBASE_H

#include <cstring>
#include <type_traits>

#include "iterator.hpp"
#include "algobase_impl.hpp"

namespace mystl {


template <typename OutputIter, typename Size, typename T>
OutputIter
fill_n(OutputIter first, Size n, const T& value) {
    return unchecked_fill_n(first, n, value);
}


template <typename InputIter, typename OutputIter>
OutputIter 
copy(InputIter first, InputIter last, OutputIter result) {
    return unchecked_copy(first, last, result);
}

template <typename InputIter, typename OutputIter>
OutputIter 
move(InputIter first, InputIter last, OutputIter result) {
    return unchecked_move(first, last, result);
}

/**
 * @brief: 将 [first, last)区间内的元素拷贝到 [result - (last - first), result)内
 */
template <typename BidirectionalIter1, typename BidirectionalIter2>
BidirectionalIter2
copy_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result) {
    return unchecked_copy_backward(first, last, result);
}

/**
 * @brief: 为 [first, last)区间内的所有元素填充新值
 */
template <typename ForwardIter, typename T>
void
fill(ForwardIter first, ForwardIter last, const T& value) {
    fill_cat(first, last, value, iterator_category(first));
}

}

#endif // _MINISTL_ALGOBASE_H