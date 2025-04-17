#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

int main() {
  int n;
  std::cin >> n;

  const int cCnt = 100000;
  std::vector<std::tuple<int, int, int>> edges;

  std::vector<std::vector<long long>> a(n, std::vector<long long>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> a[i][j];
      if (a[i][j] != cCnt) {
        edges.push_back({i, j, (int)a[i][j]});
      }
    }
  }

  std::vector<long long> dist(n, 0);
  std::vector<int> parent(n, -1);

  int x = -1;
  for (int i = 0; i < n; i++) {
    x = -1;
    for (auto& edge : edges) {
      int u;
      int v;
      int w;
      std::tie(u, v, w) = edge;
      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        parent[v] = u;
        x = v;
      }
    }
  }

  if (x == -1) {
    std::cout << "NO\n";
    return 0;
  }

  int y = x;
  for (int i = 0; i < n; i++) {
    y = parent[y];
  }

  std::vector<int> cycle;
  for (int cur = y;; cur = parent[cur]) {
    cycle.push_back(cur);
    if (cur == y && cycle.size() > 1) {
      break;
    }
  }
  reverse(cycle.begin(), cycle.end());

  std::cout << "YES\n";
  std::cout << cycle.size() << "\n";
  for (auto v : cycle) {
    std::cout << v + 1 << " ";
  }
  std::cout << "\n";

  return 0;
}
