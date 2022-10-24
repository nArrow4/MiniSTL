/**
 * @Description: 
 * @Email: zhiyyyu@gmail.com
 * @Author: Zehui Deng
 * @Github: nArrow4
 * @Date: 2022-09-25 19:33:58
 */
#include "vector.hpp"
#include <gtest/gtest.h>

using namespace mystl;

void test_constructor() {
    // 构造函数测试
    vector<int> v1;
    vector<int> v2(5);
    vector<int> v3(5, 1);
    vector<int> v4(v3);
    vector<int> v5(std::move(v4));
    // 测试到这里的时候修复了一些bug，主要是int*不能匹配到is_iterator的情况
    vector<int> v6(v5.begin(), v5.end());
    vector<int> v7 = {1, 2, 3};
    // vector<bool> v8;
    
    LOG("constructor test pass!");
}

void test_operator_eq() {
    vector<int> v0;
    // LOG("v0 size: " << v0.size() << " cap: " << v0.capacity());
    vector<int> v1 = {1, 2, 3};
    // LOG("v1 size: " << v1.size() << " cap: " << v1.capacity());
    vector<int> v2 = {1, 2, 3, 4, 5};
    // LOG("v2 size: " << v2.size() << " cap: " << v2.capacity());
    vector<int> v3(20, 1);
    // LOG("v3 size: " << v3.size() << " cap: " << v3.capacity());

    v1 = v0;
    EXPECT_EQ(v1.size(), v0.size());
    EXPECT_EQ(v1.capacity(), v0.capacity());

    v1 = v1;
    v1 = v2;
    EXPECT_EQ(v1.size(), v2.size());
    EXPECT_EQ(v1.capacity(), v2.capacity());

    v1 = v3;
    EXPECT_EQ(v1.size(), v3.size());
    EXPECT_EQ(v1.capacity(), v3.capacity());

    vector<int> tmp(v2);
    v1 = move(v2);
    EXPECT_EQ(v1.size(), tmp.size());
    EXPECT_EQ(v1.capacity(), tmp.capacity());

    LOG("operator= test pass!");
}

void test_emplace_back() {
    vector<int> v1(15);
    //  size = 15, cap = 16
    // LOG("v size: " << v.size() << " cap: " << v.capacity());
    // emplace_back
    v1.emplace_back(1);
    EXPECT_EQ(v1.size(), 16);
    EXPECT_EQ(v1[15], 1);

    int i = 1;
    v1.emplace_back(i);
    EXPECT_EQ(v1.size(), 17);
    EXPECT_EQ(v1[16], 1);

    LOG("emplace_back test pass!");
}

void test_push_back() {
    vector<int> v2(15);

    v2.emplace_back(1);
    EXPECT_EQ(v2.size(), 16);
    EXPECT_EQ(v2[15], 1);

    int i = 1;
    v2.emplace_back(i);
    EXPECT_EQ(v2.size(), 17);
    EXPECT_EQ(v2[16], 1);

    LOG("push_back test pass!");
}

void test_pop_back() {
    vector<int> v;
    v.push_back(1);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 1);
    v.pop_back();
    EXPECT_EQ(v.size(), 0);

    LOG("pop_back test pass!");
}

void test_emplace() {
    vector<int> v3(15);

    v3.emplace(v3.begin(), 1);
    EXPECT_EQ(v3.size(), 16);
    EXPECT_EQ(v3[0], 1);

    int i = 1;
    v3.emplace(v3.begin() + 3, i);
    EXPECT_EQ(v3.size(), 17);
    EXPECT_EQ(v3[3], 1);
    
    v3.emplace(v3.end(), i);
    EXPECT_EQ(v3.size(), 18);
    EXPECT_EQ(v3[17], 1);

    LOG("emplace test pass!");
}

void test_assign() {

}

void test_insert() {

}

void test_erase() {
    
}

void test_resize() {

}

void test_swap() {

}

void test_functions() {
    test_emplace_back();
    test_push_back();
    test_emplace();  
    test_pop_back();  
    test_assign();
    test_insert();
    test_erase();
    test_resize();
    test_swap();   
}

int main(){
    test_constructor();
    test_operator_eq();
    test_functions();

}