#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using Ll = long long;
const Ll cInf = 1e18;

struct Edge {
  int to;
  int rev;
  Ll cap;
};

bool Bfs(int source, int sink, std::vector<std::vector<Edge>>& graph,
         std::vector<int>& parent, std::vector<Ll>& min_cap) {
  int n = graph.size() - 1;
  std::vector<bool> visited(n + 1, false);
  std::queue<int> q;
  q.push(source);
  visited[source] = true;
  parent[source] = -1;
  min_cap[source] = cInf;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (const Edge& e : graph[u]) {
      if (!visited[e.to] && e.cap > 0) {
        parent[e.to] = u;
        min_cap[e.to] = std::min(min_cap[u], e.cap);
        q.push(e.to);
        visited[e.to] = true;
        if (e.to == sink) {
          return true;
        }
      }
    }
  }
  return false;
}

std::vector<bool> Find(const std::vector<std::vector<Edge>>& graph,
                       int source) {
  int n = graph.size() - 1;
  std::vector<bool> visited(n + 1, false);
  std::queue<int> q;
  q.push(source);
  visited[source] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (const Edge& e : graph[u]) {
      if (e.cap > 0 && !visited[e.to]) {
        visited[e.to] = true;
        q.push(e.to);
      }
    }
  }
  return visited;
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  std::vector<std::tuple<int, int, int>> original_edges;
  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    int c;
    std::cin >> u >> v >> c;
    original_edges.push_back({u, v, c});
  }

  std::vector<std::vector<Edge>> graph(n + 1);
  for (const auto& edge : original_edges) {
    int u;
    int v;
    int c;
    std::tie(u, v, c) = edge;
    graph[u].push_back({v, (int)graph[v].size(), c});
    graph[v].push_back({u, (int)graph[u].size() - 1, c});
  }

  std::vector<int> parent(n + 1);
  std::vector<Ll> min_cap(n + 1);
  while (Bfs(1, n, graph, parent, min_cap)) {
    Ll f = min_cap[n];
    int v = n;
    while (v != 1) {
      int u = parent[v];
      for (Edge& e : graph[u]) {
        if (e.to == v) {
          e.cap -= f;
          graph[v][e.rev].cap += f;
          break;
        }
      }
      v = u;
    }
  }

  std::vector<bool> s = Find(graph, 1);

  std::vector<int> cut_edges;
  for (int i = 0; i < m; ++i) {
    auto [u, v, c] = original_edges[i];
    if (s[u] != s[v]) {
      cut_edges.push_back(i + 1);
    }
  }
  sort(cut_edges.begin(), cut_edges.end());

  Ll sum = 0;
  for (int idx : cut_edges) {
    sum += std::get<2>(original_edges[idx - 1]);
  }

  std::cout << cut_edges.size() << " " << sum << '\n';
  for (int idx : cut_edges) {
    std::cout << idx << " ";
  }
  std::cout << '\n';

  return 0;
}
