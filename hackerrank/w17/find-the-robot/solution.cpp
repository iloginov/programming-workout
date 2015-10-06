#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "gmock/gmock.h"

using namespace std;

// Первый вариант.
vector<int> s1[] = { vector<int>{1, 0},
					vector<int>{0, 1},
					vector<int>{-1, 0},
					vector<int>{0, -1} };

// Ускорило в 2 раза.
int s[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

vector<int> solution(int n)
{
	// Ускорение. 100500.
	int k = n/4;
	int x = - k * 2, y = -k * 2;

	for (int i = 4 * k; i < n; ++i) {
		x += s[i % 4][0] * (i + 1);
		y += s[i % 4][1] * (i + 1);
	}

	vector<int> res = {x, y};
	return res;
}

TEST(FindTheRobot, Zero) {
	auto res = std::vector<int> {0, 0};
	ASSERT_THAT(solution(0), testing::Eq(res));
}

TEST(FindTheRobot, One) {
	auto res = std::vector<int> {1, 0};
	ASSERT_THAT(solution(1), testing::Eq(res));
}

TEST(FindTheRobot, Two) {
	auto res = std::vector<int> {1, 2};
	ASSERT_THAT(solution(2), testing::Eq(res));
}

TEST(FindTheRobot, Three) {
	auto res = std::vector<int> {-2, 2};
	ASSERT_THAT(solution(3), testing::Eq(res));
}

TEST(FindTheRobot, Four) {
	auto res = std::vector<int> {-2, -2};
	ASSERT_THAT(solution(4), testing::Eq(res));
}

TEST(FindTheRobot, Five) {
	auto res = std::vector<int> {3, -2};
	ASSERT_THAT(solution(5), testing::Eq(res));
}

TEST(FindTheRobot, Six) {
	auto res = std::vector<int> {3, 4};
	ASSERT_THAT(solution(6), testing::Eq(res));
}

TEST(FindTheRobot, Big) {
	auto res = std::vector<int> {-3000000000, -3000000000};
	ASSERT_THAT(solution(600000000), testing::Eq(res));
}


int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
