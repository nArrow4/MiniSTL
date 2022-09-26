#include "../includes/vector.hpp"

using namespace mystl;

int main(){
    // 构造函数测试
    vector<int> v1;
    vector<int> v2(5);
    vector<int> v3(5, 1);
    vector<int> v4(v3);
    vector<int> v5(std::move(v4));
    // vector<int> v6(v5.begin(), v5.end());    // 暂不支持
    vector<int> v7 = {1, 2, 3};
    // vector<bool> v8;
    
    

}