#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>

#include "gmock/gmock.h"

using namespace std;

long long countCandiesLazy(int N, const std::vector<int> &r)
{
	std::vector<long long> c(N, 1);

	for (auto i = 1; i < N; i++) {
		if (r[i] > r[i - 1]) {
			c[i] = c[i - 1] + 1;
		}
	}

	for (auto i = N - 1; i > 0; i--) {
		if (r[i] < r[i - 1]) {
			c[i - 1] = max(c[i - 1], c[i] + 1);
		}
	}

	return accumulate(begin(c), end(c), 0, std::plus<long long>());
}

long long countCandies(int N, const std::vector<int> &r)
{
	std::vector<long long> cache(N, -1);

	std::function<long long (int)> getCandies = [&cache, &r, N, &getCandies] (int i) -> long long {
		if (cache[i] != -1) {
			return cache[i];
		}

		long long p = 0, n = 0;
		if (i > 0 && r[i] > r[i - 1]) {
			p = getCandies(i - 1);
		}
		if (i < N - 1 && r[i] > r[i + 1]) {
			n = getCandies(i + 1);
		}

		cache[i] = max(p, n) + 1;

		return cache[i];
	};

	long long res = 0;
	for (auto i = 0; i < N; i++) {
		res += getCandies(i);
	}

	return res;
}

TEST(Candies, Statement1) {
	std::vector<int> rating = { 1, 2, 2 };
	ASSERT_THAT(countCandies(3, rating), testing::Eq(4));
}

TEST(Candies, Test1) {
	std::vector<int> rating = { 2, 4, 2, 6, 1, 7, 8, 9, 2, 1 };
	ASSERT_THAT(countCandies(10, rating), testing::Eq(19));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
