#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "gmock/gmock.h"

using namespace std;

long g(vector<long> dv) {
	long y = dv[0], m = dv[1], d = dv[2];
	m = (m + 9) % 12;
	y = y - m / 10;
	return 365 * y + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 + (d - 1);
}

vector<long> d(long g) {
	long y, ddd, m, d, mi;

  	y = (10000*g + 14780)/3652425;
  	ddd = g - (y*365 + y/4 - y/100 + y/400);
  	if (ddd < 0) {
	    y--;
	    ddd = g - (y*365 + y/4 - y/100 + y/400);
	}
  	mi = (52 + 100*ddd)/3060;
  	y = y + (mi + 2)/12;
  	m = (mi + 2)%12 + 1;
  	d = ddd - (mi*306 + 5)/10 + 1;

	return vector<long> {y, m, d};
}

int solution(int d1, int m1, int y1, int d2, int m2, int y2)
{
	int res = 0;

	auto g0 = g(std::vector<long> {1900, 1, 1});
	int wday = 1;

	auto g1 = g(std::vector<long> {y1, m1, d1});
	auto g2 = g(std::vector<long> {y2, m2, d2});
	wday = (wday + g1 - g0) % 7;

	for (auto i = g1; i <= g2; ++i, wday = (wday + 1) % 7) {
		if (wday == 5 && d(i)[2] == 13)
			res++;
	}

	return res;
}

TEST(CountFridaysThe13Th, Helpers1) {
	std::vector<long> date = {9999, 9, 5};
	ASSERT_THAT(d(g(date)), testing::Eq(date));
}

TEST(CountFridaysThe13Th, SameDate1) {
	ASSERT_THAT(solution(5, 9, 2015, 5, 9, 2015), testing::Eq(0));
}

TEST(CountFridaysThe13Th, SameDate2) {
	ASSERT_THAT(solution(13, 3, 2015, 13, 3, 2015), testing::Eq(1));
}

TEST(CountFridaysThe13Th, Statement1) {
	ASSERT_THAT(solution(1, 10, 2000, 20, 10, 2000), testing::Eq(1));
}

TEST(CountFridaysThe13Th, Statement2) {
	ASSERT_THAT(solution(19, 10, 1995, 11, 7, 2015), testing::Eq(34));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
