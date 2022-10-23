/**
 * @Description: 
 * @Email: zhiyyyu@gmail.com
 * @Author: Zehui Deng
 * @Github: nArrow4
 * @Date: 2022-10-16 16:11:44
 */

#ifndef _MINISTL_VECTOR_FUNC_H
#define _MINISTL_VECTOR_FUNC_H

#include "vector.hpp"
#include "allocator.hpp"
#include "constructor.hpp"
#include "algobase.hpp"
#include "uninitialized.hpp"

namespace mystl {

/**
 * @brief: 拷贝赋值运算符 Copy Assign Operator
 */
template <typename T>
vector<T>&
vector<T>::operator=(const vector& rhs) {
    if(this == &rhs) {
        return *this;
    }
    const auto len = rhs.size();
    if(len > capacity()) {      // 当前容器容量不够
        vector tmp(rhs.begin(), rhs.end());
        swap(tmp);
    } else if(len > size()) {   // 当前容器容量充足
        mystl::copy(rhs.begin(), rhs.begin() + len, begin());
        mystl::uninitialized_copy(rhs.begin() + len, rhs.end(), end());
        _end = _begin + len;
    } else {                    // 当前大小大于拷贝后的大小
        // 把rhs拷贝到当前vector中
        auto it = mystl::copy(rhs.begin(), rhs.end(), begin());
        // 析构后面一部分的对象
        data_allocator::destory(it, end());
        _end = _begin + len;
    }
    return *this;
}

/**
 * @brief: 移动赋值运算符
 */
template <typename T>
vector<T>&
vector<T>::operator=(vector&& rhs) noexcept {
    destroy_and_recover(_begin, _end, capacity());
    _begin = rhs._begin; _end = rhs._end; _cap = rhs._cap;
    rhs._begin = rhs._end = rhs._cap = nullptr;
    return *this;
}

/**
 * @brief: initializer_list 初始化
 */
template <typename T>
vector<T>&
vector<T>::operator=(std::initializer_list<value_type> ilist) {
    vector tmp(ilist.begin(), ilist.end());
    swap(tmp);
    return *this;
}

/**** 容器修改相关 ****/
/**
 * @brief: 交换两个vector
 */
template <typename T>
void 
vector<T>::swap(vector& rhs) noexcept {
    if(this == &rhs) return;
    mystl::swap(_begin, rhs._begin);
    mystl::swap(_end, rhs._end);
    mystl::swap(_cap, rhs._cap);
}

/**
 * @brief: 在末尾插入对象
 */
template <typename T>
template <typename ...Args>
void
vector<T>::emplace_back(Args&&... args) {
    if(_end < _cap) {   // 空间足够
        data_allocator::construct(&*_end, mystl::forward<Args>(args)...);
        ++_end;
    } else {
        reallocate_emplace(_end, mystl::forward<Args>(args)...);
    }
}

/**
 * @brief: 在末尾插入对象（左值引用版）
 */
template <typename T>
void
vector<T>::push_back(const value_type& value) {
    if(_end < _cap) {
        data_allocator::construct(&*_end, value);
        ++_end;
    } else {
        reallocate_insert(_end, value);
    }
}

/**
 * @brief: 在末尾插入对象（右值引用版）
 */
template <typename T>
void
vector<T>::push_back(value_type&& value) {
    emplace_back(mystl::move(value));
}

/**
 * @brief: 插入一个对象（原地构造）
 */
template <typename T>
template <typename ...Args>
typename vector<T>::iterator    // 注意这里的写法
vector<T>::emplace(const_iterator pos, Args&&... args) {
    iterator xpos = const_cast<iterator>(pos);
    const size_type n = xpos - _begin;
    if(_end == _cap) {          // 容量满了，需要扩容
        reallocate_emplace(xpos, mystl::forward<Args>(args)...);
    } else if(xpos == _end) {   // 相当于emplace_back
        data_allocator::construct(&*_end, mystl::forward<Args>(args)...);
        ++_end;
    } else {                    // 插入到中间的位置
        auto new_end = _end;
        // size 增大一个，先构造
        mystl::construct(&*_end, *(_end - 1));
        ++new_end;
        mystl::copy_backward(xpos, _end-1, _end);
        *xpos = value_type(mystl::forward<Args>(args)...);
        _end = new_end;
    }
    return _begin + n;
}

template <typename T>
void 
vector<T>::assign(size_type n, const value_type& value) {

}

template <typename T>
void 
vector<T>::assign(size_type n, const value_type& value) {

}

}

#endif // _MINISTL_VECTOR_FUNC_H