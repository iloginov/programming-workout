#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>

#include "gmock/gmock.h"

using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings) {
        int N = ratings.size();
        
    	std::vector<int> cache(N, -1);
    
    	std::function<int (int)> getCandies = [&cache, &ratings, N, &getCandies] (int i) -> int {
    		if (cache[i] != -1) {
    			return cache[i];
    		}
    
    		int p = 0, n = 0;
    		if (i > 0 && ratings[i] > ratings[i - 1]) {
    			p = getCandies(i - 1);
    		}
    		if (i < N - 1 && ratings[i] > ratings[i + 1]) {
    			n = getCandies(i + 1);
    		}
    
    		cache[i] = max(p, n) + 1;
    
    		return cache[i];
    	};
    
    	int res = 0;
    	for (auto i = 0; i < N; i++) {
    		res += getCandies(i);
    	}
    
    	return res;
    }
};

TEST(Candies, Statement1) {
	Solution sol;
	std::vector<int> rating = { 1, 2, 2 };
	ASSERT_THAT(sol.countCandies(3, rating), testing::Eq(4));
}

TEST(Candies, Test1) {
	Solution sol;
	std::vector<int> rating = { 2, 4, 2, 6, 1, 7, 8, 9, 2, 1 };
	ASSERT_THAT(sol.countCandies(10, rating), testing::Eq(19));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
