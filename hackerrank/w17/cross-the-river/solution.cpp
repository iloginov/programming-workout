#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <iterator>
#include <limits>

#include "gmock/gmock.h"

using namespace std;

/*
 * 1. Нужен код, который прочитает граф в виде списков.
 * 2. Реализация алгоритма дейкстры.
 * 3. 1 - N
 * 4. 1 - x - N
 * 5. 1 -- [x-y] -- N
 */

// Дорог может быть несколько, в граф надо заносить минимальную.

typedef int vertex_t;
typedef long weight_t;
 
const weight_t min_weight = std::numeric_limits<int>::min();
 
struct edge {
	vertex_t from;
	vertex_t to;
	weight_t weight;

	edge(int f, int t, int w)
		: from(f), to(t), weight(w) {}
};

struct stone {
	int x;
	int y;
	weight_t z;

	stone(int y1, int x1, weight_t z1)
		: y(y1), x(x1), z(z1) {}
};

void add_stone(vector<stone> &stones, vector<edge> &edges, int H, int dH, int dW, int y, int x, weight_t z) {
	int n = stones.size();

	// This shore
	if (y <= dH) {
		edges.push_back(edge(0, n + 2, z));
//		cout << "0 - " << n + 2 << " " << z << endl;
	}

	for (int i = 0; i < n; ++i) {
		auto s = stones[i];

		// Potentially can jump.
		if (abs(s.y - y) <= dH && abs(s.x - x) <= dW) {
			if (y > s.y) {
				edges.push_back(edge(i + 2, n + 2, z));
//				cout << i + 2 << " - " << n + 2 << " " << z << endl;
			} else if (y < s.y) {
				edges.push_back(edge(n + 2, i + 2, s.z));
//				cout << n + 2 << " - " << i + 2 << " " << s.z << endl;
			}
		}
	}

	stones.push_back(stone(y, x, z));

	if (abs(y  - H) <= dH) {
		edges.push_back(edge(n + 2, 1, 0));
//		cout << n + 2 << " - " << 1 << " " << 0 << endl;
	}
}

void belman_ford_max(int n,
			  	 const vector<edge> &edges,
			  	 vertex_t source,
              	 std::vector<weight_t> &min_distance,
              	 std::vector<vertex_t> &previous)
{
    min_distance.clear();
    min_distance.resize(n, min_weight / 2);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);

	// for (int j = 0; j < n; ++j) {
	// 	cout << min_distance[j] << " ";
	// }
	// cout << endl;

    for (int i = 0; i < n; ++i) {
    	for (auto &e : edges) {
    		int u = e.from;
    		int v = e.to;
    		weight_t w = e.weight;

    		if (min_distance[v] < min_distance[u] + w) {
    			min_distance[v] = min_distance[u] + w;
		        previous[v] = u;
    		}
    	}
    	// for (int j = 0; j < n; ++j) {
    	// 	cout << min_distance[j] << " ";
    	// }
    	// cout << endl;
    }
}

int solution(int N, const std::vector<edge> &g)
{
	vector<weight_t> dist;
	vector<int> prev;
	belman_ford_max(N, g, 0, dist, prev);

	return dist[1];
}

void read_statement()
 {
 	int N, H, dH, dW;
 	cin >> N >> H >> dH >> dW;

	std::vector<stone> s;
	std::vector<edge> g;

 	for (int i = 0; i < N; ++i) {
 		int y, x;
 		weight_t z;
 		cin >> y >> x >> z;
 		add_stone(s, g, H, dH, dW, y, x, z);
 	}

 	cout << solution(N + 2, g) << endl;
}

TEST(RoadsBuilding, Statement) {
	std::vector<stone> s;
	std::vector<edge> g;
	int H = 10;
	int dH = 3;
	int dW = 3;
	add_stone(s, g, H, dH, dW, 2, 2, 7);
	add_stone(s, g, H, dH, dW, 2, 3, 5);
	add_stone(s, g, H, dH, dW, 5, 5, -1);
	add_stone(s, g, H, dH, dW, 8, 3, 10);
	add_stone(s, g, H, dH, dW, 8, 8, 12);
	ASSERT_THAT(solution(5 + 2, g), testing::Eq(18));
}

TEST(RoadsBuilding, Test1) {
	std::vector<stone> s;
	std::vector<edge> g;
	int H = 10;
	int dH = 3;
	int dW = 4;
	add_stone(s, g, H, dH, dW, 2, 2, 7);
	add_stone(s, g, H, dH, dW, 2, 3, 5);
	add_stone(s, g, H, dH, dW, 5, 5, -1);
	add_stone(s, g, H, dH, dW, 8, 3, 10);
	add_stone(s, g, H, dH, dW, 8, 8, 12);
	add_stone(s, g, H, dH, dW, 5, 4, 100);
	ASSERT_THAT(solution(6 + 2, g), testing::Eq(119));
}

TEST(RoadsBuilding, Test2) {
	std::vector<stone> s;
	std::vector<edge> g;
	int H = 8;
	int dH = 3;
	int dW = 3;
	add_stone(s, g, H, dH, dW, 2, 2, -7);
	add_stone(s, g, H, dH, dW, 2, 3, -5);
	add_stone(s, g, H, dH, dW, 5, 5, -1);
	add_stone(s, g, H, dH, dW, 6, 3, -2);
	add_stone(s, g, H, dH, dW, 6, 8, -3);
	ASSERT_THAT(solution(5 + 2, g), testing::Eq(-6));
}

TEST(RoadsBuilding, Test3) {
	std::vector<stone> s;
	std::vector<edge> g;
	int H = 8;
	int dH = 2;
	int dW = 2;
	add_stone(s, g, H, dH, dW, 2, 2, 5);
	add_stone(s, g, H, dH, dW, 2, 5, 3);
	add_stone(s, g, H, dH, dW, 4, 7, 2);
	add_stone(s, g, H, dH, dW, 4, 5, 4);
	add_stone(s, g, H, dH, dW, 6, 4, 3);
	add_stone(s, g, H, dH, dW, 6, 8, 10);
	ASSERT_THAT(solution(6 + 2, g), testing::Eq(15));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
