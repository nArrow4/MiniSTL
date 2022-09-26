#include <iostream>

template <typename ...  Args> void 
func(const char* s, Args ... args) {
    printf(s, args...);
}


int main() {
    func<int, int>("%d %d\n", 1, 2);
    func("%d %d\n", 1, 2);
}