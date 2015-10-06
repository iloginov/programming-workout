#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <iterator>
#include <limits>
#include <fstream>

#include "gmock/gmock.h"

using namespace std;

/*
 * 1. Нужен код, который прочитает граф в виде списков.				Done.
 * 2. Реализация алгоритма дейкстры.
 * 3. 1 - N
 * 4. 1 - x - N
 * 5. 1 -- [x-y] -- N
 */

// Дорог может быть несколько, в граф надо заносить минимальную.

typedef int vertex_t;
typedef int weight_t;
 
const weight_t max_weight = std::numeric_limits<int>::max();
 
struct neighbor {
    vertex_t target;
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight)
        : target(arg_target), weight(arg_weight) { }
};
 
typedef std::vector<std::vector<neighbor>> adjacency_list_t;

void init_graph(int n, adjacency_list_t &g)
{
	g.clear();
	g.resize(n);
}

void add_edge_int(adjacency_list_t &g, int x, int y, int z)
{
	auto &neighbors = g[x];

    for (auto neighbor_iter = neighbors.begin();
         neighbor_iter != neighbors.end();
         neighbor_iter++)
    {
    	if (neighbor_iter->target == y) {
    		if (neighbor_iter->weight >= z) {
    			neighbor_iter->weight = z;
    		}
    		return;
    	}
    }

 	neighbors.push_back(neighbor(y, z));
}

void add_edge(adjacency_list_t &g, int x, int y, int z)
{
	add_edge_int(g, x, y, z);
	add_edge_int(g, y, x, z);
}

void read_graph(adjacency_list_t &g)
{
	int N;
	cin >> N;
	init_graph(N, g);
	int M;
	cin >> M;
	for (int i = 0; i < M; ++i) {
		int x, y, z;
		cin >> x >> y >> z;
		add_edge(g, x - 1, y - 1, z);
	}
}
 
void dijkstra(int n,
			  const adjacency_list_t &adjacency_list,
			  vertex_t source,
              std::vector<weight_t> &min_distance,
              std::vector<vertex_t> &previous)
{
    min_distance.clear();
    min_distance.resize(n, max_weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);

    std::set<std::pair<weight_t, vertex_t> > vertex_queue;
    vertex_queue.insert(std::make_pair(min_distance[source], source));
 
    while (!vertex_queue.empty()) 
    {
        weight_t dist = vertex_queue.begin()->first;
        vertex_t u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());
 
        // Visit each edge exiting u
		const std::vector<neighbor> &neighbors = adjacency_list[u];
        for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
             neighbor_iter != neighbors.end();
             neighbor_iter++)
        {
            vertex_t v = neighbor_iter->target;
            weight_t weight = neighbor_iter->weight;
            weight_t distance_through_u = dist + weight;
	    if (distance_through_u < min_distance[v]) {
	        vertex_queue.erase(std::make_pair(min_distance[v], v));
 
	        min_distance[v] = distance_through_u;
	        previous[v] = u;
	        vertex_queue.insert(std::make_pair(min_distance[v], v));
 
	    }
 
        }
    }
}

int solution(int N, const adjacency_list_t &g)
{
	int res = 0;

	std::vector<int> tmp;
	std::vector<int> firstToOthers;
	dijkstra(N, g, 0, firstToOthers, tmp);
	std::vector<int> lastToOthers;
	dijkstra(N, g, N - 1, lastToOthers, tmp);

	int min = firstToOthers[N - 1];

	// 1 - N
	res += min - 1;

	// 1 - x - N - 1
	for (int i = 1; i < N - 1; ++i) {
		int s1 = firstToOthers[i];
		int s2 = lastToOthers[i];

		int k1 = min - s2;
		if (k1 > 0) {
			res += k1 - 1;
		}

		int k2 = min - s1;
		if (k2 > 0) {
			res += k2 - 1;
		}
	}

	// 1 -- x - y -- N
	for (int i = 1; i < N - 1; ++i) {
		for (int j = i + 1; j < N - 1; ++j) {
			int s1 = firstToOthers[i];
			int s2 = lastToOthers[j];
			int s3 = firstToOthers[j];
			int s4 = lastToOthers[i];

			int k = max(min - s1 - s2, min - s3 - s4);
			if (k > 0) {
				res += k - 1;
			}
		}
	}

	return res;
}

TEST(RoadsBuilding, Statement) {
	adjacency_list_t g;
	init_graph(3, g);
	add_edge(g, 0, 2, 4);
	add_edge(g, 0, 1, 1);
	add_edge(g, 1, 2, 2);
	ASSERT_THAT(solution(3, g), testing::Eq(3));
}

TEST(RoadsBuilding, Test1) {
	adjacency_list_t g;
	init_graph(6, g);
	add_edge(g, 0, 1, 1);
	add_edge(g, 1, 2, 1);
	add_edge(g, 1, 4, 100);
	add_edge(g, 2, 3, 200);
	add_edge(g, 3, 4, 1);
	add_edge(g, 4, 5, 1);
	ASSERT_THAT(solution(6, g), testing::Eq(891));
}

TEST(RoadsBuilding, Test2) {
	adjacency_list_t g;
	init_graph(2, g);
	add_edge(g, 0, 1, 1);
	ASSERT_THAT(solution(2, g), testing::Eq(0));
}

TEST(RoadsBuilding, Test3) {
	adjacency_list_t g;
	init_graph(6, g);
	add_edge(g, 0, 1, 1);
	add_edge(g, 1, 2, 1);
	add_edge(g, 1, 4, 100);
	add_edge(g, 1, 4, 1);
	add_edge(g, 2, 3, 200);
	add_edge(g, 3, 4, 1);
	add_edge(g, 4, 5, 1);
	ASSERT_THAT(solution(6, g), testing::Eq(4));
}

TEST(RoadsBuilding, Test4) {
	adjacency_list_t g;
	init_graph(5, g);
	add_edge(g, 0, 1, 6);
	add_edge(g, 0, 2, 3);
	add_edge(g, 0, 3, 6);
	add_edge(g, 1, 2, 5);
	add_edge(g, 1, 4, 1);
	add_edge(g, 2, 3, 2);
	add_edge(g, 3, 4, 4);
	ASSERT_THAT(solution(5, g), testing::Eq(19));
}

TEST(RoadsBuilding, OrigTest12) {
	fstream in("input12.txt");
	int N, M;
	in >> N >> M;
	adjacency_list_t g;
	init_graph(N, g);
	for (int i = 0; i < M; ++i) {
		int x, y, z;
		in >> x >> y >> z;
		add_edge(g, x - 1, y - 1, z);
	}
	ASSERT_THAT(solution(N, g), testing::Eq(496498765));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
