#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "gmock/gmock.h"

using namespace std;

#define MOD 1000000007

std::vector<int> both(std::vector<int> U,
					  std::vector<int> L)
{
	std::vector<int> R;
	int il = 0;
	int iu = 0;
	auto last = -1;
	while (il < L.size() && iu < U.size()) {
		auto l = L[il];
		auto u = U[iu];
		if (u == l) {
			last = u;
			R.push_back(last);
			++iu;
			++il;
		} else {
			if (u < l) {
				++iu;
			} else {
				++il;
			}
		}
	}

	return R;
}

template<typename T>
void printVec(const string &name, const std::vector<T> &v)
{
	cout << name << " = ";
	for (auto &e: v) {
		cout << e << " ";
	}
	cout << endl;
}

std::vector<int> countDSequences(int N,
							     int M,
								 int C,
								 std::vector<int> U,
								 std::vector<int> L)
{
	sort(begin(U), end(U));
	sort(begin(L), end(L));

	auto R = both(U, L);

	if (R.size() == 0) {
		return std::vector<int> (C, 0);
	}

	std::vector<std::vector<long long>> dp;
	dp.resize(C + 1);
	for (auto i = 0; i < dp.size(); ++i) {
		dp[i].resize(R.size(), 0);
	}

	auto il = 0;
	auto iu = 0;
	for (auto i = 0; i < R.size(); ++i) {
		auto r = R[i];

		while (il < L.size() && L[il] < r) {
			++il;
		}
		while (iu < U.size() && U[iu] < r) {
			++iu;
		}

		auto cl = 0;
		auto cu = 0;
		while (il < L.size() && L[il] == r) {
			++cl;
			++il;
		}
		while (iu < U.size() && U[iu] == r) {
			++cu;
			++iu;
		}
		dp[0][i] = (cl * cu) % MOD;
	}

	for (auto i = 1; i <= C; ++i) {
		for (auto j = 0; j < R.size(); ++j) {
			for (auto k = 0; k < j; ++k) {
				dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
			}
			dp[i][j] = (dp[i][j] * dp[0][j]) % MOD;
		}
	}

	std::vector<int> res(C, 0);
	for (auto i = 0; i < C; ++i) {
		for (auto j = 0; j < R.size(); ++j) {
			res[i] = (res[i] + dp[i + 1][j]) % MOD;
		}
	}

	return res;
}

TEST(KSpheres, Helpers1) {
	std::vector<int> U = { 1, 2, 2, 2, 3, 4 };
	std::vector<int> L = { 1, 1, 1, 2, 3, 17 };
	std::vector<int> res = { 1, 2, 3 };
	ASSERT_THAT(both(U, L), testing::Eq(res));
}

TEST(KSpheres, Helpers2) {
	std::vector<int> U = { 1, 2, 2, 2, 3, 4 };
	std::vector<int> L = { 5, 6 };
	std::vector<int> res = {};
	ASSERT_THAT(both(U, L), testing::Eq(res));
}

TEST(KSpheres, Statement1) {
	int N = 3;
	int M = 4;
	int C = 3;
	std::vector<int> U = { 1, 2, 3 };
	std::vector<int> L = { 1, 1, 3, 2 };
	std::vector<int> res = { 5, 2, 0 };
	ASSERT_THAT(countDSequences(N, M, C, U, L), testing::Eq(res));
}

TEST(KSpheres, Test1) {
	int N = 3;
	int M = 4;
	int C = 3;
	std::vector<int> U = { 1, 2, 3 };
	std::vector<int> L = { 1, 3, 3, 2 };
	std::vector<int> res = { 5, 2, 0 };
	ASSERT_THAT(countDSequences(N, M, C, U, L), testing::Eq(res));
}

TEST(KSpheres, Test2) {
	int N = 5;
	int M = 5;
	int C = 3;
	std::vector<int> U = { 1, 2, 2, 3, 4 };
	std::vector<int> L = { 1, 3, 3, 2, 2 };
	std::vector<int> res = { 14, 8, 0 };
	ASSERT_THAT(countDSequences(N, M, C, U, L), testing::Eq(res));
}

TEST(KSpheres, Test3) {
	int N = 5;
	int M = 5;
	int C = 3;
	std::vector<int> U = { 1, 2, 3, 4, 5 };
	std::vector<int> L = { 1, 6, 7, 8, 9 };
	std::vector<int> res = { 0, 0, 0 };
	ASSERT_THAT(countDSequences(N, M, C, U, L), testing::Eq(res));
}

TEST(KSpheres, Test4) {
	int N = 10;
	int M = 10;
	int C = 10;
	std::vector<int> U = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<int> L = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<int> res = { 45, 120, 210, 252, 210, 120, 45, 10, 1, 0 };
	ASSERT_THAT(countDSequences(N, M, C, U, L), testing::Eq(res));
}

TEST(KSpheres, Test5) {
	int N = 4;
	int M = 4;
	int C = 3;
	std::vector<int> U = { 1, 2, 3, 4 };
	std::vector<int> L = { 5, 6, 7, 8 };
	std::vector<int> res = { 0, 0, 0 };
	ASSERT_THAT(countDSequences(N, M, C, U, L), testing::Eq(res));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
