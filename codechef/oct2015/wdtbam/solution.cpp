#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "gmock/gmock.h"

using namespace std;

int predictMaxProfit(const string &etalon,
					 const string &answers,
					 const std::vector<int> &w) {
	auto n = etalon.length();

	auto k = 0;
	for (auto i = 0; i < n; ++i) {
		if (etalon[i] == answers[i]) {
			++k;
		}
	}

	if (k == 0 || k == n) {
		return w[k];
	} else {
		auto m = w[0];
		for (auto i = 1; i <= k; ++i) {
			if (w[i] > m) {
				m = w[i];
			}
		}
		return m;
	}
}

TEST(Millionaire, Statement1) {
	string s1 = "ABCDE";
	string s2 = "EBCDA";
	std::vector<int> w = { 0, 10, 20, 30, 40, 50 };
	ASSERT_THAT(predictMaxProfit(s1, s2, w), testing::Eq(30));
}

TEST(Millionaire, Statement2) {
	string s1 = "CHEF";
	string s2 = "QUIZ";
	std::vector<int> w = { 4, 3, 2, 1, 0 };
	ASSERT_THAT(predictMaxProfit(s1, s2, w), testing::Eq(4));
}

TEST(Millionaire, Statement3) {
	string s1 = "ABBABAAB";
	string s2 = "ABABABAB";
	std::vector<int> w = { 100, 100, 100, 100, 100, 100, 100, 100, 100 };
	ASSERT_THAT(predictMaxProfit(s1, s2, w), testing::Eq(100));
}

TEST(Millionaire, Test1) {
	string s1 = "CHEF";
	string s2 = "QHIZ";
	std::vector<int> w = { 4, 3, 2, 1, 0 };
	ASSERT_THAT(predictMaxProfit(s1, s2, w), testing::Eq(4));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}