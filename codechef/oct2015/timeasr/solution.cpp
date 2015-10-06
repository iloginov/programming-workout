#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "gmock/gmock.h"

using namespace std;

double angleDiff(int h, int m)
{
	double ha = h * 30. + m * 1./2;
	double ma = m * 6.;

	double r = fabs(ha - ma);
	if (r > 180.) {
		r = 360. - r;
	}
	return r;
}

std::vector<string> getTimes(double a)
{
	std::vector<string> res;
	char buf[100];

	for (int h = 0; h < 12; ++h) {
		for (int m = 0; m < 60; ++m) {
			if (fabs(a - angleDiff(h, m)) <= 1./120) {
				sprintf(buf, "%02d:%02d", h, m);
				res.push_back(buf);
			}
		}
	}

	return res;
}

TEST(Time, Statement1) {
	std::vector<string> res = { "00:00" };
	ASSERT_THAT(getTimes(0.), testing::Eq(res));
}

TEST(Time, Statement2) {
	std::vector<string> res = { "01:00", "11:00" };
	ASSERT_THAT(getTimes(30.), testing::Eq(res));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
