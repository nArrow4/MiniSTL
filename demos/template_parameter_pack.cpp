/**
 * @Description: 变长模板参数
 * @Email: zhiyyyu@gmail.com
 * @Author: Zehui Deng
 * @Github: nArrow4
 * @Date: 2022-09-26 16:48:13
 */
#include <iostream>

/**
 * @brief: 注意一下...的位置就好了（三处）
 */
template <typename ...  Args> void 
func(const char* s, Args ... args) {
    printf(s, args...);
}


int main() {
    // 变长模板参数
    func<int, int>("%d %d\n", 1, 2);
    // 自动推导参数类型
    func("%d %d\n", 1, 2);
}