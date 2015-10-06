#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

#include "gmock/gmock.h"

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        std::vector<string> v(numRows);

        int pos = 0;
        int cur = 0;
        int inc = +1;
        if (numRows == 1) {
        	inc = 0;
        }
        while (pos < s.length()) {
        	v[cur] += s[pos++];
        	if ((cur == 0 && inc < 0) || cur == (numRows - 1)) {
        		inc = -inc;
        	}
        	cur += inc;
        }

        string res;
        for (const auto &str: v) {
        	res += str;
        }

        return res;
    }
};

TEST(LongestSubstring, statement) {
    Solution sol;
    ASSERT_THAT(sol.convert("PAYPALISHIRING", 3), testing::Eq("PAHNAPLSIIGYIR"));
}

TEST(LongestSubstring, dummy) {
    Solution sol;
    ASSERT_THAT(sol.convert("PAYPALISHIRING", 1), testing::Eq("PAYPALISHIRING"));
}

TEST(LongestSubstring, test1) {
    Solution sol;
    ASSERT_THAT(sol.convert("ABCD", 2), testing::Eq("ACBD"));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
