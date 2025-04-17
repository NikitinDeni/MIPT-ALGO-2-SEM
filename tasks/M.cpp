#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int u;
  int v;
  int weight;
};

struct DSU {
  std::vector<int> parent;
  std::vector<int> rank;

  DSU(int n) {
    parent.resize(n + 1);
    rank.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      parent[i] = i;
    }
  }

  int Find(int a) {
    if (parent[a] != a) {
      parent[a] = Find(parent[a]);
    }
    return parent[a];
  }

  bool Unite(int a, int b) {
    a = Find(a);
    b = Find(b);
    if (a == b) {
      return false;
    }
    if (rank[a] < rank[b]) {
      std::swap(a, b);
    }
    parent[b] = a;
    if (rank[a] == rank[b]) {
      rank[a]++;
    }
    return true;
  }
};

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  std::vector<Edge> edges(m);

  for (int i = 0; i < m; i++) {
    std::cin >> edges[i].u >> edges[i].v >> edges[i].weight;
  }

  sort(edges.begin(), edges.end(),
       [](const Edge& a, const Edge& b) { return a.weight < b.weight; });

  DSU dsu(n);
  long long mst_weight = 0;

  for (const auto& edge : edges) {
    if (dsu.Unite(edge.u, edge.v)) {
      mst_weight += edge.weight;
    }
  }

  std::cout << mst_weight << "\n";
  return 0;
}
