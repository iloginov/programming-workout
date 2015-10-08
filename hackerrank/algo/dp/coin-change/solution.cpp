#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "gmock/gmock.h"

using namespace std;

long long countCoins(int N, int M, std::vector<int> c)
{
	sort(begin(c), end(c));

	std::vector<std::vector<long long>> dp;
	dp.resize(N);
	for (auto i = 0; i < N; ++i) {
		dp[i].resize(M);
	}

	for (auto i = 0; i < M; ++i) {
		auto coin = c[i];
		if (coin <= N) {
			dp[coin - 1][i] = 1;
		}
	}

	for (auto i = 0; i < M; ++i) {
		auto coin = c[i];
		for (auto j = 0; j < N; ++j) {
			if (j + coin < N) {
				dp[j + coin][i] += dp[j][i];
			}
			if (i + 1 < M) {
				dp[j][i + 1] += dp[j][i];
			}
		}
	}

	return dp[N - 1][M - 1];
}

TEST(CoinChange, Statement1) {
	std::vector<int> coins = { 1, 2, 3 };
	ASSERT_THAT(countCoins(4, 3, coins), testing::Eq(4));
}

TEST(CoinChange, Statement2) {
	std::vector<int> coins = { 2, 5, 3, 6 };
	ASSERT_THAT(countCoins(10, 4, coins), testing::Eq(5));
}

TEST(CoinChange, Test1) {
	std::vector<int> coins = { 16, 30, 9, 17, 40, 13, 42, 5, 25, 49, 7, 23, 1, 44, 4, 11, 33, 12, 27, 2, 38, 24, 28, 32, 14, 50 };
	ASSERT_THAT(countCoins(245, 26, coins), testing::Eq(64027917156));
}


int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
