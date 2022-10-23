#ifndef _MINISTL_UNINITIALIZED_H
#define _MINISTL_UNINITIALIZED_H

#include <cstring>
#include "allocator.hpp"
#include "constructor.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "algobase.hpp"

namespace mystl {

/**** uninitialized_fill_n ****/
// 填充连续n个空间
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

/**** uninitialized_copy ****/
// 如果没有普通赋值运算符函数了
template <typename InputIter, typename ForwardIter>
ForwardIter
unchecked_uninit_copy(InputIter first, InputIter last, ForwardIter result, std::false_type) {
    auto cur = result;
    try {
        for(; first != last; first++, cur++) {
            mystl::construct(&*cur, first);
        }
    } catch( ... ) {
        for(; result != cur; cur--) {
            mystl::destory(&*cur);
        }
    }
    return cur;
}

// 如果已经有普通赋值运算符函数了，就直接copy
template <typename InputIter, typename ForwardIter>
ForwardIter
unchecked_uninit_copy(InputIter first, InputIter last, ForwardIter result, std::true_type) {
    return mystl::copy(first, last, result);
}

template <class InputIter, class ForwardIter>
ForwardIter
uninitialized_copy(InputIter first, InputIter last, ForwardIter result) {
    return unchecked_uninit_copy(first, last, result, 
        // 检查result是否有赋值运算符
        /** 这里的{}是啥意思？ **/
        std::is_trivially_copy_assignable<
            typename iterator_traits<ForwardIter>::value_type>{});
}

/**** uninitialized_move ****/

/**
 * @brief: 
 */
template <typename InputIter, typename ForwardIter>
ForwardIter
unchecked_uninit_move(InputIter first, InputIter last, ForwardIter result, std::false_type) {
    auto cur = result;
    try {
        // 逐个元素尝试移动构造
        for(; first != last; first++, cur++) {
            mystl::construct(&*cur, mystl::move(*first));
        }
    } catch(...) {
        // 析构这一部分
        mystl::destory(result, cur);
    }
    return cur;
}

/**
 * @brief: 
 */
template <typename InputIter, typename ForwardIter>
ForwardIter
unchecked_uninit_move(InputIter first, InputIter last, ForwardIter result, std::true_type) {
    return mystl::move(first, last, result);
}

/**
 * @brief: 将[first, last)移动到result上
 */
template <typename InputIter, typename ForwardIter>
ForwardIter
uninitialized_move(InputIter first, InputIter last, ForwardIter result) {
    return unchecked_uninit_move(first, last, result,
        std::is_trivially_move_assignable<
        typename iterator_traits<InputIter>::value_type>{} );
}

}

#endif // _MINISTL_UNINITIALIZED_H