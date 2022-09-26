#include <type_traits>
#include <iostream>

template <typename T>
class vector{
public:
    vector(){
        if(std::is_same<T, int>::value) std::cout << "int type\n";
        else std::cout << "other type\n";
    }
};


int main(){
    vector<int> v1;
    vector<bool> v2;
}