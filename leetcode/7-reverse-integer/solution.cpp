#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

#include "gmock/gmock.h"

using namespace std;

class Solution {
public:
    int reverse(int x) {
        int res = 0;
        
        while (x != 0) {
            int d = x % 10;
            x /= 10;
            if ((d >  0 && res > (INT_MAX - d) / 10) ||
                (d < 0 && res < (INT_MIN - d) / 10)) {
                return 0;
            }
            res = res * 10 + d;
        }

        return res;
    }
};


TEST(LongestSubstring, statement1) {
    Solution sol;
    ASSERT_THAT(sol.reverse(123), testing::Eq(321));
}

TEST(LongestSubstring, statement2) {
    Solution sol;
    ASSERT_THAT(sol.reverse(-123), testing::Eq(-321));
}

TEST(LongestSubstring, test1) {
    Solution sol;
    ASSERT_THAT(sol.reverse(1534236469), testing::Eq(0));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
