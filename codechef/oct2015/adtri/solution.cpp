#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "gmock/gmock.h"

using namespace std;

string goodNumber(int N)
{
	long long N2 = N * N;

	long long i, j;
	for (i = 1, j = N - 1; i <= j; ++i) {
		while (i*i + j*j > N2)
			--j;
		if (i*i + j*j == N2)
			return "YES";
	}
	return "NO";
}

TEST(Triangle, Statement1) {
	ASSERT_THAT(goodNumber(5), testing::Eq("YES"));
}

TEST(Triangle, Statement2) {
	ASSERT_THAT(goodNumber(3), testing::Eq("NO"));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
