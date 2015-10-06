#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "gmock/gmock.h"

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
    	int res = 0;
        std::vector<int> v(256, -1);

        int cur = 0;
        for (int i = 0; i < s.length(); ++i) {
        	if (v[s[i]] == -1) {
        		cur++;
        	} else {
        		cur = min(i - v[s[i]], cur + 1);
        	}

        	v[s[i]] = i;

        	if (cur > res)
        		res = cur;
        }

        return res;
    }
};

TEST(LongestSubstring, EmptyString) {
	Solution sol;
	ASSERT_THAT(sol.lengthOfLongestSubstring(""), testing::Eq(0));
}

TEST(LongestSubstring, StatementExample1) {
	Solution sol;
	ASSERT_THAT(sol.lengthOfLongestSubstring("abcabcbb"), testing::Eq(3));
}

TEST(LongestSubstring, StatementExample2) {
	Solution sol;
	ASSERT_THAT(sol.lengthOfLongestSubstring("bbbbb"), testing::Eq(1));
}

TEST(LongestSubstring, Wrong1) {
	Solution sol;
	ASSERT_THAT(sol.lengthOfLongestSubstring("abba"), testing::Eq(2));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
