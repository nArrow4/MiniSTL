
#include <cstddef>


namespace mystl{

template <class Category, class T, class Distance,
    class Pointer = T*, class Reference = T&>
class iterator
{
public:

};

template <class Iter>
class is_input_iterator 
{
    static constexpr Iter value = false;
}; 

// template <class T, T v>
// struct m_integral_constant
// {
//   static constexpr T value = v;
// };

// template <bool b>
// using m_bool_constant = m_integral_constant<bool, b>;

// typedef m_bool_constant<true>  m_true_type;
// typedef m_bool_constant<false> m_false_type;

// template <class T>
// struct has_iterator_cat
// {
// private:
//   struct two { char a; char b; };
//   template <class U> static two test(...);
//   template <class U> static char test(typename U::iterator_category* = 0);
// public:
//   static const bool value = sizeof(test<T>(0)) == sizeof(char);
// };

// template <class T, class U, bool = has_iterator_cat<iterator_traits<T>>::value>
// struct has_iterator_cat_of
//   : public m_bool_constant<std::is_convertible<
//   typename iterator_traits<T>::iterator_category, U>::value>
// {
// };

// // 萃取某种迭代器
// template <class T, class U>
// struct has_iterator_cat_of<T, U, false> : public m_false_type {};

// template <class Iter>
// struct is_input_iterator : public has_iterator_cat_of<Iter, input_iterator_tag> {};


}