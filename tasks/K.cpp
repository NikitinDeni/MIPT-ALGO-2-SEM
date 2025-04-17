#include <limits.h>

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

const long long cInf = (long long)1e18;

struct Edge {
  int to;
  int rev;
  long long cap;
  long long cost;
};

struct MinCostMaxFlow {
  int n;
  std::vector<std::vector<Edge>> adj;
  std::vector<long long> h;
  std::vector<long long> dist;
  std::vector<int> prevv;
  std::vector<int> preve;

  MinCostMaxFlow(int size)
      : n(size), adj(size), h(size), dist(size), prevv(size), preve(size) {}

  void AddEdge(int from, int to, long long cap, long long cost) {
    adj[from].push_back(Edge{to, (int)adj[to].size(), cap, cost});
    adj[to].push_back(Edge{from, (int)adj[from].size() - 1, 0, -cost});
  }

  std::pair<long long, long long> MinCostMaxFlowCalc(int s, int t) {
    long long flow = 0;
    long long cost = 0;
    std::fill(h.begin(), h.end(), 0);

    while (true) {
      std::priority_queue<std::pair<long long, int>,
                          std::vector<std::pair<long long, int>>,
                          std::greater<std::pair<long long, int>>>
          pq;
      std::fill(dist.begin(), dist.end(), cInf);
      dist[s] = 0;
      pq.push({0, s});

      while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        long long d = cur.first;
        int v = cur.second;
        if (dist[v] < d) {
          continue;
        }
        for (int i = 0; i < (int)adj[v].size(); i++) {
          Edge& e = adj[v][i];
          if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
            dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
            prevv[e.to] = v;
            preve[e.to] = i;
            pq.push({dist[e.to], e.to});
          }
        }
      }
      if (dist[t] == cInf) {
        break;
      }
      for (int v = 0; v < n; v++) {
        if (dist[v] < cInf) {
          h[v] += dist[v];
        }
      }
      long long d = cInf;
      for (int v = t; v != s; v = prevv[v]) {
        d = std::min(d, adj[prevv[v]][preve[v]].cap);
      }
      flow += d;
      cost += d * h[t];
      for (int v = t; v != s; v = prevv[v]) {
        Edge& e = adj[prevv[v]][preve[v]];
        e.cap -= d;
        adj[v][e.rev].cap += d;
      }
    }

    return {flow, cost};
  }
};

int main() {
  int n;
  int m;
  std::cin >> n >> m;

  MinCostMaxFlow mcmf(n + 1);

  for (int i = 0; i < m; i++) {
    int u;
    int v;
    long long c;
    long long w;
    std::cin >> u >> v >> c >> w;
    mcmf.AddEdge(u, v, c, w);
  }

  auto result = mcmf.MinCostMaxFlowCalc(1, n);
  std::cout << result.second << "\n";

  return 0;
}
