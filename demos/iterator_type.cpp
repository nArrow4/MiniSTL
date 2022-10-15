/**
 * @Description: 迭代器类型判断相关
 * @Email: zhiyyyu@gmail.com
 * @Author: Zehui Deng
 * @Github: nArrow4
 * @Date: 2022-10-15 21:08:33
 */

#include "iterator.hpp"
#include "logger.hpp"

template <typename T>
class a_input_iterator:
    public mystl::iterator<mystl::input_iterator_tag, T> {};

template <typename T>
class a_output_iterator:
    public mystl::iterator<mystl::output_iterator_tag, T> {};

template <typename T>
class a_forward_iterator:
    public mystl::iterator<mystl::forward_iterator_tag, T> {};

template <typename T>
class a_bidirectional_iterator:
    public mystl::iterator<mystl::bidirectional_iterator_tag, T> {};

template <typename T>
class a_random_access_iterator:
    public mystl::iterator<mystl::random_access_iterator_tag, T> {};

template <typename Iter, 
          typename std::enable_if<mystl::is_input_iterator<Iter>::value, int>::type = 0>
void func_input(Iter it)
{ LOG("is input iter."); }

template <typename Iter, 
          typename std::enable_if<mystl::is_output_iterator<Iter>::value, int>::type = 0>
void func_output(Iter it)
{ LOG("is output iter."); }

template <typename Iter, 
          typename std::enable_if<mystl::is_forward_iterator<Iter>::value, int>::type = 0>
void func_forward(Iter it)
{ LOG("is forward iter."); }

template <typename Iter, 
          typename std::enable_if<mystl::is_bidirectional_iterator<Iter>::value, int>::type = 0>
void func_bidirectional(Iter it)
{ LOG("is bidirectional iter."); }

template <typename Iter, 
          typename std::enable_if<mystl::is_random_access_iterator<Iter>::value, int>::type = 0>
void func_random_access(Iter it)
{ LOG("is random_access iter."); }

template <typename T>
void func_iter(T* it)
{ LOG("is pointer"); }

template <typename T>
void func_iter(const T* it)
{ LOG("is const pointer"); }

template <typename Iter,
          typename std::enable_if<mystl::is_iterator<Iter>::value, int>::type = 0>
void func_iter(Iter it)
{ LOG("is iter"); }

int main() {

    a_input_iterator<int> in_it;
    func_input(in_it);
    a_output_iterator<int> out_it;
    func_output(out_it);
    a_forward_iterator<int> fo_it;
    func_forward(fo_it);
    a_bidirectional_iterator<int> bi_it;
    func_bidirectional(bi_it);
    a_random_access_iterator<int> ra_it;
    func_random_access(ra_it);

    // 适配原生指针
    int a[5];
    const int* b = a;
    func_iter(in_it);
    func_iter(out_it);
    func_iter(fo_it);
    func_iter(bi_it);
    func_iter(ra_it);
    func_iter(a);
    func_iter(b);
}