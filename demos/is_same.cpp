/**
 * @Description: is_same用于判断两个类型是否相同
 * @Email: zhiyyyu@gmail.com
 * @Author: Zehui Deng
 * @Github: nArrow4
 * @Date: 2022-09-25 19:33:58
 */

#include <type_traits>
#include <iostream>

template <typename T>
class A{
public:
    A(){
        if(std::is_same<T, int>::value) std::cout << "int type\n";
        else std::cout << "other type\n";
    }
};


int main(){
    A<int> v1;
    A<bool> v2;
    A<int*> v1_p;
    A<const int*> v1_cp;
    A<int&> v1_lr;
    A<const int&> v1_clr;
    A<int&&> v1_rr;
    A<const int> v1_c;
}