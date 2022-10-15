/**
 * @Description: gtest samples
 * @Email: zhiyyyu@gmail.com
 * @Author: Zehui Deng
 * @Github: nArrow4
 * @Date: 2022-10-16 00:13:03
 */
#include <gtest/gtest.h>

int test_eq() { return 1; }

int main() {
    EXPECT_EQ(test_eq(), 0) << "FAILED: EXPECT: 0, but given 1";
    EXPECT_EQ(test_eq(), 1);

    
}