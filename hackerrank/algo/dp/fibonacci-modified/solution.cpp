#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "gmock/gmock.h"

using namespace std;

long long fibModified(int N, long long A, long long B) {
    if (N == 1) {
        return A;
    } else {
        return fibModified(N - 1, B, A + B * B);
    }
}

TEST(FibonacciModified, Statement1) {
	ASSERT_THAT(fibModified(5, 0, 1), testing::Eq(5));
}

TEST(FibonacciModified, Statement2) {
	ASSERT_THAT(fibModified(10, 0, 1), testing::Eq(84266613096281243382112));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
