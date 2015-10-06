#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "gmock/gmock.h"

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        auto len1 = nums1.size();
        auto len2 = nums2.size();

        int idx1 = 0, idx2 = 0;
        if ((len1 + len2) % 2 == 1) {
            idx1 = idx2 = (len1 + len2) / 2 + 1;
        } else {
            idx1 = (len1 + len2) / 2;
            idx2 = (len1 + len2) / 2 + 1;
        }

        int i1 = 0, i2 = 0;
        int v1 = 0, v2 = 0;
        for (int i = 0; i < idx2; ++i) {
            int cur = 0;

            if (i1 == len1) {
                cur = nums2[i2++];
            } else if (i2 == len2) {
                cur = nums1[i1++];
            } else if (nums1[i1] <= nums2[i2]) {
                cur = nums1[i1++];
            } else {
                cur = nums2[i2++];
            }

            if (i == idx1 - 1)
                v1 = cur;

            if (i == idx2 - 1)
                v2 = cur;
        }

        return (v1 + v2) / 2.;
    }
};

TEST(LongestSubstring, Test1) {
	Solution sol;
    std::vector<int> v1 = { 1, 2, 3, 4, 5, 6 };
    std::vector<int> v2 = { 7, 17, 38, 45, 46, 1024, 1000043};
	ASSERT_THAT(sol.findMedianSortedArrays(v1, v2), testing::Eq(7.));
}

TEST(LongestSubstring, Test2) {
    Solution sol;
    std::vector<int> v1 = { 1, 2, 3, 4, 5, 6 };
    std::vector<int> v2 = { 7, 17, 38, 45, 46, 1024};
    ASSERT_THAT(sol.findMedianSortedArrays(v1, v2), testing::Eq(6.5));
}

TEST(LongestSubstring, Test3) {
    Solution sol;
    std::vector<int> v1 = { 1};
    std::vector<int> v2 = { 7, 17, 38, 45, 46, 1024};
    ASSERT_THAT(sol.findMedianSortedArrays(v1, v2), testing::Eq(38.));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
