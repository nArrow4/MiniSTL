#ifndef _MINISTL_VECTOR_H
#define _MINISTL_VECTOR_H

#include <type_traits>
#include <initializer_list>

#include "utils.hpp"
#include "logger.hpp"
#include "allocator.hpp"
#include "iterator.hpp"
#include "algobase.hpp"
#include "uninitialized.hpp"


namespace mystl{

template <class T>  // 类型名为T
class vector{
// 不支持vector<bool>
    static_assert(!std::is_same<T, bool>::value, "vector<bool> is not supported.");
// vector嵌套型别定义
public:
    typedef mystl::allocator<T>     allocator_type;
    typedef mystl::allocator<T>     data_allocator;

    // typename 指明为类型而不是成员
    typedef typename allocator_type::value_type      value_type;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;

    typedef value_type*             iterator;
    typedef const value_type*       const_iterator;

// 构造、析构、移动函数
public:
    vector() noexcept 
    { try_init(); }
    vector(size_type n)
    { fill_init(n, value_type()); }
    vector(size_type n, const value_type& value)
    { fill_init(n, value); }
    template <class Iter, typename std::enable_if
        <mystl::is_input_iterator<Iter>::value, int>::type = 0>
    vector(Iter first, Iter last)
    { range_init(first, last); }
    vector(const vector& rhs)
    { range_init(rhs.begin(), rhs.end()); }
    vector(vector&& rhs) noexcept: 
        _begin(rhs.begin()), _end(rhs.end()), _cap(rhs._cap)
    { rhs._begin = rhs._end = rhs._cap = nullptr; }
    vector(std::initializer_list<value_type> il)
    { range_init(il.begin(), il.end()); }

    ~vector()
    { _begin = _end = _cap = nullptr; }
    
    vector& operator=(const vector& rhs);
    vector& operator=(vector&& rhs) noexcept;
    vector& operator=(std::initializer_list<value_type> ilist);

// 迭代器相关
public:
    iterator _begin;    // 目前使用空间的起始位置
    iterator _end;      // 目前使用空间的结束位置
    iterator _cap;      // 当前空间的结束位置

public:
    iterator begin() noexcept
    { return _begin; }
    const_iterator begin() const noexcept
    { return _begin; }
    const_iterator cbegin() noexcept
    { return _begin; }
    iterator end() noexcept
    { return _end; }
    const_iterator end() const noexcept
    { return _end; }
    const_iterator cend() noexcept
    { return _end; }
    
    size_type size() noexcept
    { return static_cast<size_type>(end() - begin()); }
    size_type capacity() noexcept
    { return static_cast<size_type>(capacity() - begin()); }
    size_type max_size() noexcept
    { return static_cast<size_type>(-1) - sizeof(T); }
    bool empty() const noexcept
    { return begin() == end(); }
    void reserve(size_type n);
    void shrink_to_fit();

// 访问元素
public:
    reference operator[] (size_type n)
    { return *(_begin + n); }
    const_reference operator[] (size_type n) const 
    { return *(_begin + n); }
    reference at (size_type n)
    { return (*this)[n]; }
    const_reference at (size_type n) const 
    { return (*this)[n]; }

    iterator front()
    { return *_begin; }
    const_iterator front() const
    { return *_begin; }
    iterator back()
    { return *(_end - 1); }
    const_iterator back() const
    { return *(_end - 1); }

    pointer data() noexcept
    { return _begin; }
    const_pointer data() const noexcept
    { return _begin; }

// 修改容器
public:
    template <typename ...Args>
    iterator emplace(const_iterator pos, Args&& ...args);
    template <typename ...Args>
    void emplace_back(Args&& ...args);

    void push_back(const value_type& value);
    void push_back(value_type&& value);
    void pop_back();

    void assign(size_type n, const value_type& value);
    void assign(std::initializer_list<value_type> il);
    template <typename Iter, typename std::enable_if
        <mystl::is_input_iterator<Iter>::value, int>::type = 0>
    void assign(Iter first, Iter last);

    iterator insert(const_iterator pos, const value_type& value);
    iterator insert(const_iterator pos, value_type&& value);
    iterator insert(const_iterator pos, size_type n, const value_type& value);
    template <typename Iter, std::enable_if
        <mystl::is_input_iterator<Iter>::value, int>::type = 0>
    iterator insert(const_iterator pos, Iter first, Iter last);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    void clear() { erase(begin(), end()); }

    void resize(size_type n);
    void resize(size_type n, const value_type& value);

    void swap(vector& rhs) noexcept;

// helper函数
private:
    // 各种配置空间的方式：单个元素、连续空间、迭代器...
    void try_init() noexcept;
    void fill_init(size_type n, const value_type& value); 
    template <typename Iter>
    void range_init(Iter first, Iter last);
    void init_space(size_type size, size_type cap); 
    
    // 析构并释放空间
    void destroy_and_recover(iterator first, iterator last, size_type n);

    // 扩容函数
    void get_new_cap(size_type add_size);

    // assign辅助函数
    void fill_assign(size_type n, const value& value);
    template <typename InputIter>
    void copy_assign(InputIter first, InputIter last, input_iterator_tag);
    template <typename ForwardIter>
    void copy_assign(ForwardIter first, ForwardIter last, forward_iterator_tag);

    // 重新分配空间
    template <typename ..Args>
    void reallocate_emplace(iterator pos, Args&& ...args);
    void reallocate_insert(iterator pos, const value_type& value);
    void fill_insert(iterator pos, size_type n, const value_type& value);
    template <typename Iter>
    void copy_insert(iterator pos, Iter first, Iter last);
    void reinsert(size_type n);
};

// 构造函数辅助函数
template <typename T>
void vector<T>::try_init() noexcept {
    try {
        _begin = data_allocator(16); _end = _begin; _cap = _begin + 16;
    } catch(...) {
        _begin = _end = _cap = nullptr;
    }
}

template <typename T>
void vector<T>::init_space(size_type size, size_type cap) {
    try {
        _begin = data_allocator(cap); _end = _begin + size; _cap = _begin + cap;
    } catch(...) {
        _begin = _end = _cap = nullptr; throw;
    }
}

template <typename T>
void vector<T>::fill_init(size_type n, const value_type& value) {
    const size_type init_size = mystl::max(static_cast<size_type>(16), n);
    init_space(n, init_size);
    mystl::uninitialized_fill_n(_begin, n, value);
}

template <typename T>
template <typename Iter>
void vector<T>::range_init(Iter first, Iter last) {
    const size_type init_size = mystl::max(static_cast<size_type>(last - first), static_cast<size_type>(16));
    init_space(static_cast<size_type>(last - first), init_size);
    mystl::uninitialized_copy(first, last, _begin);
}

// 赋值运算符重载
template <typename T>
vector<T>&
vector<T>::operator=(const vector& rhs) {
    if(this == &rhs) {
        return *this;
    }
    const auto len = rhs.size();
    if(len > capacity()) {
        vector<T> tmp(rhs.begin(), rhs.end());
    } else if(len > size()) {
        
    } else {

    }
}

}

#endif // _MINISTL_VECTOR_H