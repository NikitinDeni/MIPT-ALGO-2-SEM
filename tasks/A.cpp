#include <iostream>
#include <limits>
#include <queue>
#include <vector>

const int cInf = 2009000999;

struct Edge {
  int to;
  int weight;
};

int main() {
  int t;
  std::cin >> t;
  while (t-- != 0) {
    int n;
    int m;
    std::cin >> n >> m;

    std::vector<std::vector<Edge>> graph(n);
    for (int i = 0; i < m; i++) {
      int u;
      int v;
      int c;
      std::cin >> u >> v >> c;
      graph[u].push_back({v, c});
      graph[v].push_back({u, c});
    }

    int s;
    std::cin >> s;

    std::vector<int> dist(n, cInf);
    dist[s] = 0;

    using Pii = std::pair<int, int>;
    std::priority_queue<Pii, std::vector<Pii>, std::greater<Pii>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
      auto [d, u] = pq.top();
      pq.pop();

      if (d != dist[u]) {
        continue;
      }

      for (auto& edge : graph[u]) {
        int v = edge.to;
        int weight = edge.weight;
        if (dist[u] + weight < dist[v]) {
          dist[v] = dist[u] + weight;
          pq.push({dist[v], v});
        }
      }
    }

    for (int i = 0; i < n; i++) {
      std::cout << dist[i] << " ";
    }
    std::cout << "\n";
  }
  return 0;
}
