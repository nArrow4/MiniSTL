/**
 * @Description: 
 * @Email: zhiyyyu@gmail.com
 * @Author: Zehui Deng
 * @Github: nArrow4
 * @Date: 2022-10-16 16:06:05
 */

#ifndef _MINISTL_VECTOR_HELPER_H
#define _MINISTL_VECTOR_HELPER_H

#include "vector.hpp"
#include "algobase.hpp"
#include "uninitialized.hpp"

namespace mystl {

// 构造函数辅助函数
/**
 * @brief: 默认容量为16，大小为0
 */
template <typename T>
void 
vector<T>::try_init() noexcept {
    try {
        _begin = data_allocator::allocate(16); _end = _begin; _cap = _begin + 16;
    } catch(...) {
        _begin = _end = _cap = nullptr;
    }
}

/**
 * @brief: 指定容量和大小
 */
template <typename T>
void 
vector<T>::init_space(size_type size, size_type cap) {
    try {
        _begin = data_allocator::allocate(cap); _end = _begin + size; _cap = _begin + cap;
    } catch(...) {
        _begin = _end = _cap = nullptr; throw;
    }
}

/**
 * @brief: 指定大小和容器中的值
 */
template <typename T>
void 
vector<T>::fill_init(size_type n, const value_type& value) {
    const size_type init_size = mystl::max(static_cast<size_type>(16), n);
    init_space(n, init_size);
    mystl::uninitialized_fill_n(_begin, n, value);
}

/**
 * @brief: 
 */
template <typename T>
template <typename Iter>
void 
vector<T>::range_init(Iter first, Iter last) {
    const size_type init_size = mystl::max(static_cast<size_type>(last - first), static_cast<size_type>(16));
    init_space(static_cast<size_type>(last - first), init_size);
    mystl::uninitialized_copy(first, last, _begin);
}

/**
 * @brief: 
 */
template <typename T>
void 
vector<T>::destroy_and_recover(iterator first, iterator last, size_type n) {
    data_allocator::destory(first, last);
    data_allocator::deallocate(first, n);
}

/**
 * @brief: 查询分配add_size之后新空间的大小
 */
template <typename T>
typename vector<T>::size_type
vector<T>::get_new_cap(size_type add_size) {
    const auto old_size = capacity();
    const auto new_size = old_size == 0 
        ? mystl::max(static_cast<size_type>(16), add_size)
        : old_size + mystl::max(old_size / 2, add_size);
    return new_size;
}

/**
 * @brief: 重新分配空间，并且在pos处就地构造
 */
template <typename T>
template <typename ...Args>
void
vector<T>::reallocate_emplace(iterator pos, Args&&... args) {
    const auto new_size = get_new_cap(1);
    // 重新分配是因为当前内存后面的区域不一定空余
    auto new_begin = data_allocator::allocate(new_size);
    auto new_end = new_begin;
    try {
        new_end = mystl::uninitialized_move(_begin, pos, new_begin);
        data_allocator::construct(&*new_end, mystl::forward<Args>(args)...);
        new_end ++;
        new_end = mystl::uninitialized_move(pos, _end, new_end);
    } catch(...) {
        data_allocator::deallocate(new_begin, new_size);
        throw;
    }
    destroy_and_recover(_begin, _end, _cap - _begin);
    _begin = new_begin; _end = new_end; _cap = new_begin + new_size;
}

/**
 * @brief: 重新分配空间，并且在pos处插入元素
 */
template <typename T>
void
vector<T>::reallocate_insert(iterator pos, const value_type& value) {
    const auto new_size = get_new_cap(1);
    auto new_begin = data_allocator::allocate(new_size);
    auto new_end = new_begin;
    try {
        // 移动_begin到pos的部分
        new_end = mystl::uninitialized_move(_begin, pos, new_begin);
        data_allocator::construct(&*new_end, value);
        ++new_end;
        new_end = mystl::uninitialized_move(pos, _end, new_end);
    } catch( ... ) {
        data_allocator::deallocate(new_begin, new_size);
        throw;
    }
    // 析构并且释放旧空间
    destroy_and_recover(_begin, _end, _cap - _begin);
    // 修改迭代器指向新空间
    _begin = new_begin; _end = new_end; _cap = new_begin + new_size;
}

}

#endif // _MINISTL_VECTOR_HELPER_H