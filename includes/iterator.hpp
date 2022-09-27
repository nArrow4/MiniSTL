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
    typedef T                           value_type;
    typedef ptrdiff_t                   difference_type;
    typedef T&                          reference;
    typedef T*                          pointer;
    typedef random_access_iterator_tag  iterator_category;
};

// const指针的偏特化
template <typename T>
struct iterator_traits<const T*> {
    typedef T                           value_type;
    typedef ptrdiff_t                   difference_type;
    typedef const T&                    reference;
    typedef const T*                    pointer;
    typedef random_access_iterator_tag  iterator_category;
};

// Iterator类
template <typename Category,
          typename T,
          typename Distance = ptrdiff_t,
          typename Pointer = T*,
          typename Reference = T&>
struct Iterator {
    typedef Category        iterator_category;
    typedef T               value_type;
    typedef Distance        difference_type;
    typedef Pointer         pointer;
    typedef Reference       reference;
};

// 判断迭代器的类型
template <typename T, typename U, bool = has_iterator_cat<T>::value>
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

}

#endif // _MINISTL_ITERATOR_H