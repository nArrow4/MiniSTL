#ifndef _MINISTL_VECTOR_H
#define _MINISTL_VECTOR_H

#include <type_traits>
#include <initializer_list>

#include "utils.hpp"
#include "logger.hpp"
#include "allocator.hpp"
#include "iterator.hpp"


namespace mystl{

// template <class T>  // 类型名为T
// class vector{
//     // 不支持bool？
//     static_assert(!std::is_same<T, bool>::value, "vector<bool> is not supported.");
// public:
//     typedef mystl::allocator<T>     allocator_type;
//     typedef mystl::allocator<T>     data_allocator;

//     // typename 指明为类型而不是成员
//     typedef typename allocator_type::value_type         value_type;
//     typedef typename allocator_type::size_type          size_type;
//     typedef typename allocator_type::reference          reference;
//     typedef typename allocator_type::const_reference    const_reference;

//     typedef value_type*             iterator;
//     typedef const value_type*       const_iterator;
    
// private:
//     iterator _begin;
//     iterator _end;
//     iterator _cap;

    
// public:
//     // 构造函数
//     vector() noexcept   // 构造时出现异常就终止程序
//     { LOG("vector()"); try_init(); }

//     explicit vector(size_type n)
//     { LOG("vector(n)"); fill_init(n, value_type()); } // value_type()用于初始化

//     explicit vector(size_type n, const value_type& value)
//     { LOG("vector(n, value)"); fill_init(n, value); }

//     template <class Iter, typename std::enable_if<  // enable_if选择
//         mystl::is_input_iterator<Iter>::value, int>::type = 0>
//     vector(Iter first, Iter last)
//     { LOG("vector(begin, end)"); range_init(first, last); }

//     vector(const vector& rhs)
//     { LOG("vector(const vector&)"); range_init(rhs._begin, rhs._end); }

//     vector(vector&& rhs) noexcept
//         :_begin(rhs._begin),
//         _end(rhs._end),
//         _cap(rhs._cap)
//     {
//         LOG("vector(vector&&)");
//         rhs._begin = nullptr;
//         rhs._end = nullptr;
//         rhs._cap = nullptr;
//     }

//     vector(std::initializer_list<value_type> ilist)
//     { LOG("vector(ilist)"); range_init(ilist.begin(), ilist.end()); }

//     // 复制、移动
//     vector& operator=(const vector& rhs);
//     vector& operator=(vector&& rhs) noexcept;
//     vector& operator=(std::initializer_list<value_type> ilist);

//     // 析构
//     ~vector()
//     {
//         _begin = _end = _cap = nullptr;
//     }

// public:     // 容量相关
//     bool empty() const noexcept
//     { return _begin == _end; }
//     size_type size() const noexcept
//     { return static_cast<size_type>(_begin - _end); }
//     size_type capacity() const noexcept
//     { return static_cast<size_type>(_cap - _end); }

//     // 访问元素
//     reference operator[](size_type n)
//     {
//         return *(_begin + n);
//     }

//     const_reference operator[](size_type n) const
//     {
//         return *(_begin + n);
//     }

//     reference at(size_type n)
//     {
//         return (*this)[n];
//     }

// public:     // 迭代器相关
//     iterator begin() noexcept
//     { return _begin; }

//     iterator begin() const noexcept
//     { return _begin; }

//     iterator end()  noexcept
//     { return _end; }

//     iterator end()  const noexcept
//     { return _end; }

// private:
//     void try_init() noexcept;

//     void init_space(size_type size, size_type cap);
    
//     void fill_init(size_type n, const value_type& value); 
    
//     template <typename Iter>
//     void range_init(Iter first, Iter last);

// };

// template <typename T>
// void vector<T>::
// try_init() noexcept{
//     try{
//         _begin = data_allocator::allocate(16);
//         _end = _begin + 0;
//         _cap = _begin + 16;
//     } catch(...) {
//         _begin = _cap = _end = nullptr;
//     }
// }

// template <typename T>
// void vector<T>::
// fill_init(size_type n, const value_type& value)
// {
//     const size_type cap_size = static_cast<size_type>(16);
//     init_space(n, mystl::max(cap_size, n));
// }

// // 不能这样写：template <typename T, typename Iter>
// template <typename T>
// template <typename Iter>
// void vector<T>::
// range_init(Iter first, Iter last)
// {
//     const size_type cap_size = static_cast<size_type>(16);
//     const size_type alloc_size = static_cast<size_type>(last - first);
//     init_space(alloc_size, mystl::max(cap_size, alloc_size));
//     // uninitialized_copy();
// }

// template <typename T>
// void vector<T>::
// init_space(size_type n, size_type cap)
// {
//     // 默认cap为16，实际看last-first和cap的较大
//     try{
//         _begin = data_allocator::allocate(cap);
//         _end = _begin + n;
//         _cap = _begin + cap;
//     } catch(...) {
//         _begin = _cap = _end = nullptr;
//         throw;
//     }
// }

}

#endif // _MINISTL_VECTOR_H