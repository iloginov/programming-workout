#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <queue>
#include <fstream>

#include "gmock/gmock.h"

using namespace std;

typedef std::vector<std::vector<int>> graph;

const int dist_weight = 6;

void init_graph(graph &g, int N)
{
	g.clear();
	g.resize(N);
}

void add_edge(graph &g, int x, int y)
{
	g[x - 1].push_back(y - 1);
	g[y - 1].push_back(x - 1);
}

std::vector<int> solution(int N, const graph &g, int start) {
	std::vector<int> res;
	std::vector<bool> used(N, false);
	std::vector<int> d(N, -1);
	std::vector<int> p(N, -1);

	queue<int> q;
	q.push(start);
	d[start] = 0;
	used[start] = true;

	while(!q.empty()) {
		int v = q.front(); q.pop();

		for (auto to: g[v]) {
			if (!used[to]) {
				used[to] = true;
				q.push(to);
				d[to] = d[v] + dist_weight;
				p[to] = v;
			}
		}
	}

	for (int i = 0; i < N; ++i) {
		if (i == start)
			continue;
		res.push_back(d[i]);
	}

	return res;
}

TEST(BFS, Statement) {
	int N = 4;
	graph g;
	init_graph(g, N);
	add_edge(g, 1, 2);
	add_edge(g, 1, 3);
	ASSERT_THAT(solution(N, g, 1 - 1), testing::Eq(std::vector<int> {6, 6, -1}));
}

TEST(BFS, Test1) {
	int N = 4;
	graph g;
	init_graph(g, N);
	add_edge(g, 1, 2);
	add_edge(g, 2, 3);
	add_edge(g, 2, 4);
	ASSERT_THAT(solution(N, g, 1 - 1), testing::Eq(std::vector<int> {6, 12, 12}));
}

TEST(BFS, Test2)
{
	fstream in("input01.txt");
    int T;
    graph g;
    in >> T; // T = 1

    int N, M;
    in >> N >> M;
    init_graph(g, N);
    for (int j = 0; j < M; ++j) {
        int x, y;
        in >> x >> y;
        add_edge(g, x, y);
    }
    int s;
    in >> s;
    ASSERT_THAT(solution(N, g, s - 1), testing::Eq(std::vector<int> {6, 6, 6, 6, 12, 6, 12, 6, 12, 12, 6, 6, 6, 6, 6, 12, 12, 6, 6, 6, 6, 12, 6, 12, 6, 12, 6, 12, 12, 12, 12, 6, 12, 12, 6, 12, 12, 6, 12, 6, 12, 6, 12, 12, 6, 6, 12, 6, 6, 6, 6, 12, 12, 12, 12, 6, 6, 6, 12, 6, 6, 12, 12, 12, 12, 12, 12, 6, 6}));
}

int main(int argc, char** argv) {
	testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}
