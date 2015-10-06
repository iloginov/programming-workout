#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

#include "gmock/gmock.h"

using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        int res = 0;
        int sign = 1;
        int pos = 0;
        for (; pos < str.length(); ++pos) {
            if (!isspace(str[pos])) {
                break;;
            }
        }

        auto c = str[pos];
        if (c == '-' || c == '+') {
            if (str[pos] == '-') {
                sign = -1;
            }
            ++pos;
        }

        for (; pos < str.length(); ++pos) {
            if (isdigit(str[pos])) {
                int d = str[pos] - '0';
                if (sign > 0 && res > (INT_MAX - d) / 10) {
                    return INT_MAX;
                }
                if (sign < 0 && res < (INT_MIN + d) / 10) {
                    return INT_MIN;
                }
                res = res * 10 + sign * d;
            } else {
                break;
            }
        }

        return res;
    }
};

TEST(LongestSubstring, dummy) {
    Solution sol;
    ASSERT_THAT(sol.myAtoi(""), testing::Eq(0));
}

TEST(LongestSubstring, test1) {
    Solution sol;
    ASSERT_THAT(sol.myAtoi("0"), testing::Eq(0));
}

TEST(LongestSubstring, test2) {
    Solution sol;
    ASSERT_THAT(sol.myAtoi("     0"), testing::Eq(0));
}

TEST(LongestSubstring, test3) {
    Solution sol;
    ASSERT_THAT(sol.myAtoi("     0  "), testing::Eq(0));
}

TEST(LongestSubstring, test4) {
    Solution sol;
    ASSERT_THAT(sol.myAtoi("     0  a"), testing::Eq(0));
}

TEST(LongestSubstring, test5) {
    Solution sol;
    ASSERT_THAT(sol.myAtoi("1234"), testing::Eq(1234));
}

TEST(LongestSubstring, test6) {
    Solution sol;
    ASSERT_THAT(sol.myAtoi("-1234"), testing::Eq(-1234));
}

TEST(LongestSubstring, test7) {
    Solution sol;
    ASSERT_THAT(sol.myAtoi("   -1234   b"), testing::Eq(-1234));
}

TEST(LongestSubstring, test8) {
    Solution sol;
    ASSERT_THAT(sol.myAtoi("2147483648"), testing::Eq(INT_MAX));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
