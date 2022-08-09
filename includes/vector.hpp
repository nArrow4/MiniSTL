#include <type_traits>

#include "allocator.hpp"
#include "iterator.hpp"


namespace mystl{

template <class T>  // 类型名为T
class vector{
    // 不支持bool？
    static_assert(!std::is_same<T, bool>::value, "vector<bool> is not supported.");
public:
    typedef mystl::allocator<T>     allocator_type;

    typedef typename allocator_type::value_type value_type;
    typedef typename allocator_type::size_type  size_type;
private:
    iterator _begin;
    iterator _end;
    iterator _cap;

    
public:
    vector() noexcept   // 构造时出现异常就终止程序
    { try_init(); }

    explicit vector(size_type n)
    { fill_init(n, value_type()); } // value_type()用于初始化

    explicit vector(size_type n, const value_type& value)
    { fill_init(n, value); }

    template <class Iter, typename std::enable_if<  // enable_if选择
        mystl::is_input_iterator<Iter>::value, int>::type = 0>
    vector(Iter first, Iter last)
    { range_init(first, last); }

    vector(const vector& rhs)
    { range_init(rhs._begin, rhs._end); }

    vector(vector&& rhs) noexcept
        :_begin(rhs._begin),
        _end(rhs._end),
        _cap(rhs._cap)
    {
        rhs._begin = nullptr;
        rhs._end = nullptr;
        rhs._cap = nullptr;
    }

private:
    void try_init() noexcept;
    void fill_init(size_type n, const value_type& value); 
    // void range_init(iterator _begin, iterator _end);

};

template <typename T>
void vector<T>::
try_init() noexcept{
    try{
        // _begin = 
        // _end = _begin;
    } catch(...){
        // ...
    }
}

template <typename T>
void vector<T>::
fill_init(size_type n, const value_type& value)
{

}

// template <typename T>
// void vector<T>::
// range_init(iterator _begin, iterator _end)
// {

// }


}