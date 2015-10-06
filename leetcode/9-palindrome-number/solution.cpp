#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

#include "gmock/gmock.h"

using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }

        int x_len = 0;
        int tmp = x;
        while (tmp > 0) {
            ++x_len;
            tmp /= 10;
        }

        tmp = x;
        for (int i = 0; i < x_len / 2; ++i) {
            int d1 = tmp % 10;
            int d2 = tmp / (int)pow(10, x_len - 2 * i - 1);
            if (d1 != d2) {
                return false;
            }
            tmp = (tmp % (int)pow(10, x_len - 2 * i - 1)) / 10;
        }

        return true;
    }
};

TEST(LongestSubstring, singleDigit) {
    Solution sol;
    ASSERT_THAT(sol.isPalindrome(1), testing::Eq(true));
}

TEST(LongestSubstring, twoDigits1) {
    Solution sol;
    ASSERT_THAT(sol.isPalindrome(11), testing::Eq(true));
}

TEST(LongestSubstring, twoDigits2) {
    Solution sol;
    ASSERT_THAT(sol.isPalindrome(12), testing::Eq(false));
}

TEST(LongestSubstring, manyDigits1) {
    Solution sol;
    ASSERT_THAT(sol.isPalindrome(1234321), testing::Eq(true));
}

TEST(LongestSubstring, manyDigits2) {
    Solution sol;
    ASSERT_THAT(sol.isPalindrome(1224321), testing::Eq(false));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
