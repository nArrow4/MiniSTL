#ifndef _MINISTL_TYPE_TRAITS_H
#define _MINISTL_TYPE_TRAITS_H

#include <type_traits>

template <class T, T v>
struct m_integral_constant
{
  static constexpr T value = v;
};

template <bool b>
using m_bool_constant = m_integral_constant<bool, b>;

typedef m_bool_constant<true> m_true_type;
typedef m_bool_constant<false> m_false_type;

#endif // _MINISTL_TYPE_TRAITS_H