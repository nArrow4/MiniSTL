#include <cstddef>



namespace mystl{

template <class T>
class allocator{
public:
    typedef T           value_type;
    typedef T*          pointer;
    typedef T&          reference;
    typedef const T*    const_pointer;
    typedef const T&    const_reference;
    typedef size_t      size_type;
    // typedef ptrdiff_t   difference_type;

public:
    static T*   allocate();
    static T*   allocate(size_type n);
};

template <typename T>
T* allocator<T>::
allocate()
{ return static_cast<T*>(::operator new(sizeof(T))); }

template <typename T>
T* allocator<T>::
allocate(size_type n)
{
    if(n == 0) return nullptr;
    // ::operator new 只会分配内存，不会调用构造函数
    return static_cast<T*>(::operator new(n * sizeof(T)));
}

}