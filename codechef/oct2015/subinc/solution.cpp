#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "gmock/gmock.h"

using namespace std;

int subArrayCount(const std::vector<int> &v) {
	auto n = v.size();
	std::vector<int> dp(n, 1);

	for (int i = 1; i < n; ++i) {
		if (v[i - 1] <= v[i]) {
			dp[i] += dp[i - 1];
		}
	}

	return accumulate(begin(dp), end(dp), 0, plus<int>());
}

TEST(SubArryaCount, Statement1) {
	std::vector<int> v = { 1, 4, 2, 3 };
	ASSERT_THAT(subArrayCount(v), testing::Eq(6));
}

TEST(SubArryaCount, Statement2) {
	std::vector<int> v = { 5 };
	ASSERT_THAT(subArrayCount(v), testing::Eq(1));
}

TEST(SubArryaCount, Test1) {
	std::vector<int> v = { 1, 2, 3, 4, 5 };
	ASSERT_THAT(subArrayCount(v), testing::Eq(15));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
