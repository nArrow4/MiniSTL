#ifndef _MINISTL_LIST_H
#define _MINISTL_LIST_H

#include "utils.hpp"
#include "logger.hpp"
#include "allocator.hpp"
#include "iterator.hpp"

namespace mystl {

template <typename T>
struct _node_traits {
    typedef _list_node_base<T>* base_ptr;
    typedef _list_node<T>*      node_ptr;
};

template <typename T>
class _list_node_base {
public:
    typedef typename _node_traits<T>::base_ptr base_ptr;
    typedef typename _node_traits<T>::node_ptr node_ptr;
    
    base_ptr prev;
    base_ptr next;

    _list_node_base() = default;

    base_ptr self()
    { return static_cast<base_ptr>(&*this); }
    node_ptr as_node()
    { return static_cast<node_ptr>(self()); }
    void unlink()
    { prev = next = nullptr; }
};

template <typename T>
class _list_node: public _list_node_base<T> {
public:
    typedef T   value_type;
    T data;

public:
    _list_node() = default;
    _list_node(const value_type& value): data(value) {};
    _list_node(value_type&& value): data(mystl::move(value)) {};

    node_ptr self()
    { return static_cast<node_ptr>(&*this); }
    base_ptr as_base()
    { return static_cast<base_ptr>(self()); }
};

template <typename T>
class list_iterator: public mystl::iterator<bidirectional_iterator_tag, T> {
public:
    typedef T                                 value_type;
    typedef T*                                pointer;
    typedef T&                                reference;
    typedef typename node_traits<T>::base_ptr base_ptr;
    typedef typename node_traits<T>::node_ptr node_ptr;
    typedef list_iterator<T>                  self;

    base_ptr _node;
// 运算符重载
public:
    reference operator* () const
    { return _node->as_node()->data; }

    pointer operator-> () const
    { return &(operator*()); }

    self& operator++ ()
    { _node = _node->next; return *this; }
    self operator++ (int)
    { 
        self tmp = *this;
        ++*this;    // 即调用上面的前缀++
        return tmp; 
    }

    self operator-- ()
    { _node = _node->prev; return *this; }
    self operator-- (int)
    { 
        self tmp = *this;
        --*this;
        return tmp; 
    }

    bool operator== (const self& rhs)
    { return _node == rhs._node; }
    bool operator!= (const self& rhs)
    { return _node != rhs._node; }
};

template <typename T>
class list {
    
};

}

#endif // _MINISTL_LIST_H