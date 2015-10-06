#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "gmock/gmock.h"

using namespace std;

std::vector<int> maxSubArray(const std::vector<int> &v) {
	std::vector<int> mx(v.size());
	std::vector<int> mx2(v.size());

	for (auto i = 0; i < v.size(); ++i) {
		if (i == 0) {
			mx[i] = v[i];
			mx2[i] = v[i];
		} else {
			mx[i] = std::max(v[i], mx[i - 1] + v[i]);
			mx2[i] = std::max(std::max(v[i], mx2[i - 1] + v[i]),  mx2[i - 1]);
		}
	}

	auto m1 = std::max_element(begin(mx), end(mx));
	auto m2 = std::max_element(begin(mx2), end(mx2));
	return std::vector<int> {*m1, *m2};
}

TEST(MaxSubArray, Statement1) {
	std::vector<int> input = { 1, 2, 3, 4 };
	std::vector<int> res = { 10, 10 };
	ASSERT_THAT(maxSubArray(input), testing::Eq(res));
}

TEST(MaxSubArray, Statement2) {
	std::vector<int> input = { 2, -1, 2, 3, 4, -5 };
	std::vector<int> res = { 10, 11 };
	ASSERT_THAT(maxSubArray(input), testing::Eq(res));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
