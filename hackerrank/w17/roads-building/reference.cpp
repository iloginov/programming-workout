#include <map>
#include <queue>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int64_t> Dijkstra(const vector<map<int, int>> &E, int F) {
  vector<int64_t> r(E.size(), INT64_MAX);
  queue<pair<int, int64_t>> q;
  r[F] = 0;
  q.push(make_pair(F, 0));
  while (q.size()) {
    pair<int, int> p2 = q.front();
    int N = p2.first;
    q.pop();
    if (r[N] != p2.second)
      continue;
    for (auto &p1: E[N]) {
      int o = p1.first;
      int c = p1.second;
      if (r[o] > r[N] + c) {
        r[o] = r[N] + c;
        q.push(make_pair(o, r[o]));
      }
    }
  }
  return r;
}

int64_t Solve(const vector<map<int, int>> &E) {
  int N = E.size();
  vector<int64_t> ds = Dijkstra(E, 0);
  vector<int64_t> de = Dijkstra(E, N - 1);
  /*
  for (int i : ds) {
    cout << i << ' ';
  }
  cout << endl;*/
  sort(de.begin(), de.end());
  vector<int64_t> se(de.size());
  int64_t t = 0;
  for (int i = 0; i < int(de.size()); i++) {
    t += de[i];
    se[i] = t;
  }
  int64_t C = ds.back();
  //  ds.pop_back();

  int64_t res = 0;
  for (int i = 0; i < int(ds.size()) - 1; i++) {
    if (ds[i] >= C)
      continue;
    int64_t e = C - ds[i] - 1;
    auto it = upper_bound(de.begin(), de.end(), e);
    assert(it != de.begin());
    it--;
    int p = it - de.begin();
    res += (p + 1) * e - se[p];
  }
  return res;
}

int64_t Naive(const vector<map<int, int>> &E) {
  int N = E.size();
  vector<int64_t> ds = Dijkstra(E, 0);
  vector<int64_t> de = Dijkstra(E, N - 1);
  int C = ds.back();
  int64_t res = 0;
  for (int i = 0; i < N; i++) {
    for (int k = i + 1; k < N; k++) {
      int64_t t = ds[i] + de[k];
      if (t >= C)
        continue;
      res += C - t - 1;
    }
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);

  int N, M;
  cin >> N >> M;
  vector<map<int, int>> E(N);
  while (M--) {
    int X, Y, Z;
    cin >> X >> Y >> Z;
    X--; Y--;

    if (E[X][Y])
      E[X][Y] = min(E[X][Y], Z);
    else
      E[X][Y] = Z;
    E[Y][X] = E[X][Y];
  }
  cout << Solve(E) << endl;
  return 0;
}
