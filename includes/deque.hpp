#ifndef _MINISTL_DEQUE_H
#define _MINISTL_DEQUE_H

#include "allocator.hpp"
#include "logger.hpp"

namespace mystl {

template <typename T>
class deque_iterator {

};

template <typename T>
class deque {
// deque型别定义
public:
    typedef mystl::allocator<T>                      allocator_type;
    typedef mystl::allocator<T>                      data_allocator;
    
    typedef typename allocator_type::value_type      value_type;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;

    allocator_type get_allocator()
    { return data_allocator(); }


};

}

#endif // _MINISTL_DEQUE_H