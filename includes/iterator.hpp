#ifndef _MINISTL_ITERATOR_H
#define _MINISTL_ITERATOR_H

#include <cstddef>
#include "type_traits.hpp"

namespace mystl{

// 五种类型的迭代器
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag, output_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// 用于判断T中是否有iterator_category属性
template <typename T>
struct has_iterator_cat {
private:
    struct two {char a; char b;};
    template <typename U>
    static two test(...);
    template <typename U>
    static char test(typename U::iterator_category* = 0);
public:
    static const bool value = sizeof(test<T>(0)) == sizeof(char); 
};

template <typename Iterator, bool>
struct iterator_traits_impl {};

template <typename Iterator>
struct iterator_traits_impl<Iterator, true> {
    typedef typename Iterator::value_type           value_type;
    typedef typename Iterator::difference_type      difference_type;
    typedef typename Iterator::reference            reference;
    typedef typename Iterator::pointer              pointer;
    typedef typename Iterator::iterator_category    iterator_category;
};

template <typename Iterator, bool>
struct iterator_traits_helper {};

// 判断迭代器是否属于input_iterator或output_iterator
template <typename Iterator>
struct iterator_traits_helper<Iterator, true>:
    public iterator_traits_impl<Iterator, 
        std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
        std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value > {};

// 判断传入的迭代器类型是否有iterator_category属性
template <typename Iterator>
struct iterator_traits :
    public iterator_traits_helper<Iterator, 
        has_iterator_cat<Iterator>::value > {};

// 指针的偏特化
template <typename T>
struct iterator_traits<T*> {
    typedef T                                   value_type;
    typedef ptrdiff_t                           difference_type;
    typedef T&                                  reference;
    typedef T*                                  pointer;
    typedef random_access_iterator_tag          iterator_category;
    // just for test
    typedef void                                test;   
};

// const指针的偏特化
template <typename T>
struct iterator_traits<const T*> {
    typedef T                                   value_type;
    typedef ptrdiff_t                           difference_type;
    typedef const T&                            reference;
    typedef const T*                            pointer;
    typedef random_access_iterator_tag          iterator_category;
};

// iterator类
// Category表明迭代器的类型
// T表明迭代器中数据的类型
template <typename Category,
          typename T,
          typename Distance = ptrdiff_t,
          typename Pointer = T*,
          typename Reference = T&>
struct iterator {
    typedef Category        iterator_category;
    typedef T               value_type;
    typedef Distance        difference_type;
    typedef Pointer         pointer;
    typedef Reference       reference;
};

// 判断迭代器的类型
template <typename T, typename U, bool = has_iterator_cat<iterator_traits<T>>::value>
struct has_iterator_cat_of :
    public m_bool_constant<std::is_convertible<
    typename iterator_traits<T>::iterator_category, U>::value> {};

template <typename T, typename U>
struct has_iterator_cat_of<T, U, false>:
    public m_false_type {};

template <typename Iterator>
struct is_input_iterator :
    public has_iterator_cat_of<Iterator, input_iterator_tag> {};

template <typename Iterator>
struct is_output_iterator :
    public has_iterator_cat_of<Iterator, output_iterator_tag> {};

template <typename Iterator>
struct is_forward_iterator :
    public has_iterator_cat_of<Iterator, forward_iterator_tag> {};

template <typename Iterator>
struct is_bidirectional_iterator :
    public has_iterator_cat_of<Iterator, bidirectional_iterator_tag> {};

template <typename Iterator>
struct is_random_access_iterator :
    public has_iterator_cat_of<Iterator, random_access_iterator_tag> {};

template <typename Iterator>
struct is_iterator :
    public m_bool_constant<is_input_iterator<Iterator>::value || 
    is_output_iterator<Iterator>::value> {};

/**** 萃取迭代器特性 ****/
/**
 * @brief: 萃取迭代器类型
 */
template <typename Iterator>
typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&) {
    typedef typename iterator_traits<Iterator>::iterator_category Category;
    return Category();
}

// distance 的 input_iterator_tag 的版本
template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance_dispatch(InputIterator first, InputIterator last, 
    input_iterator_tag) {
    typename iterator_traits<InputIterator>::difference_type n = 0;
    while (first != last)
    {
        ++first;
        ++n;
    }
    return n;
}

// distance 的 random_access_iterator_tag 的版本
template <class RandomIter>
typename iterator_traits<RandomIter>::difference_type
distance_dispatch(RandomIter first, RandomIter last,
    random_access_iterator_tag) {
    return last - first;
}

/**
 * @brief: 计算两个迭代器之间的距离
 */
template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last) {
    return distance_dispatch(first, last, iterator_category(first));
}


// advance 的 input_iterator_tag 的版本
template <class InputIterator, class Distance>
void advance_dispatch(InputIterator& i, Distance n, input_iterator_tag) {
    while (n--) 
        ++i;
}

// advance 的 bidirectional_iterator_tag 的版本
template <class BidirectionalIterator, class Distance>
void advance_dispatch(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag) {
    if (n >= 0)
        while (n--)  ++i;
    else
        while (n++)  --i;
}

// advance 的 random_access_iterator_tag 的版本
template <class RandomIter, class Distance>
void advance_dispatch(RandomIter& i, Distance n, random_access_iterator_tag) {
    i += n;
}

/**
 * @brief: 迭代器前进n步
 */
template <class InputIterator, class Distance>
void advance(InputIterator& i, Distance n) {
    advance_dispatch(i, n, iterator_category(i));
}


}




#endif // _MINISTL_ITERATOR_H