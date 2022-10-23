/**
 * @Description: 
 * @Email: zhiyyyu@gmail.com
 * @Author: Zehui Deng
 * @Github: nArrow4
 * @Date: 2022-10-17 02:03:53
 */
#ifndef _MINISTL_TYPE_TRAITS_TEST_H
#define _MINISTL_TYPE_TRAITS_TEST_H

#include <type_traits>
#include "iterator.hpp"
#include "logger.hpp"

template <typename T>
class a_input_iterator:
    public mystl::iterator<mystl::random_access_iterator_tag, T> {};

int main() {

    LOG("int* is random iter? " << mystl::is_random_access_iterator<int*>::value);
    LOG("int* is input iter? " << mystl::is_input_iterator<int*>::value);
    LOG("int* is iter? " << mystl::is_iterator<int*>::value);
    LOG("int* has category? " << mystl::has_iterator_cat<int*>::value);
    LOG("a_input_iter is iter? " << mystl::is_iterator<a_input_iterator<int>>::value);
    LOG("test is_same? " << std::is_same<
        mystl::iterator_traits<int*>::test, void>::value);
    LOG("category is_same? " << std::is_same<
        mystl::iterator_traits<int*>::iterator_category, mystl::random_access_iterator_tag>::value);

}

#endif // _MINISTL_TYPE_TRAITS_TEST_H