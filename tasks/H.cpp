#include <limits.h>

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

const long long cInf = 1e18;
static const int cMax = 30;

struct Edge {
  int to;
  int rev;
  long long cap;
  long long or_cap;
  int id;
};

struct Dinic {
  int n;
  int s;
  int t;
  std::vector<std::vector<Edge>> adj;
  std::vector<int> lvl;
  std::vector<int> ptr;
  long long lim;

  Dinic(int size, int source, int sink) : n(size), s(source), t(sink) {
    adj.assign(n, std::vector<Edge>());
    lvl.assign(n, 0);
    ptr.assign(n, 0);
  }

  void AddEdge(int u, int v, long long c, int id) {
    Edge a = {v, (int)adj[v].size(), c, c, id};
    Edge b = {u, (int)adj[u].size(), 0, 0, -1};
    adj[u].push_back(a);
    adj[v].push_back(b);
  }

  bool Bfs() {
    std::fill(lvl.begin(), lvl.end(), -1);
    std::queue<int> q;
    lvl[s] = 0;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto& e : adj[u]) {
        if (lvl[e.to] < 0 && e.cap >= lim) {
          lvl[e.to] = lvl[u] + 1;
          q.push(e.to);
        }
      }
    }
    return (lvl[t] >= 0);
  }

  long long Dfs(int u, long long pushed) {
    if (u == t || pushed == 0) {
      return pushed;
    }
    for (int& cid = ptr[u]; cid < (int)adj[u].size(); cid++) {
      Edge& e = adj[u][cid];
      if (lvl[e.to] == lvl[u] + 1 && e.cap >= lim) {
        long long tr = Dfs(e.to, std::min(pushed, e.cap));
        if (tr > 0) {
          e.cap -= tr;
          adj[e.to][e.rev].cap += tr;
          return tr;
        }
      }
    }
    return 0;
  }

  long long MaxFlow() {
    long long flow = 0;
    for (lim = 1LL << cMax; lim > 0; lim >>= 1) {
      while (Bfs()) {
        std::fill(ptr.begin(), ptr.end(), 0);
        while (true) {
          long long pushed = Dfs(s, cInf);
          if (pushed == 0) {
            break;
          }
          flow += pushed;
        }
      }
    }
    return flow;
  }
};

int main() {
  int n;
  int m;
  std::cin >> n >> m;

  int s = 0;
  int t = n - 1;
  Dinic dinic(n, s, t);

  for (int i = 0; i < m; i++) {
    int u;
    int v;
    long long c;
    std::cin >> u >> v >> c;
    u--;
    v--;
    dinic.AddEdge(u, v, c, i);
  }

  long long max_flow = dinic.MaxFlow();
  std::cout << max_flow << "\n";

  std::vector<long long> flow_on_edge(m, 0);
  for (int u = 0; u < n; u++) {
    for (auto& e : dinic.adj[u]) {
      if (e.id >= 0) {
        flow_on_edge[e.id] = e.or_cap - e.cap;
      }
    }
  }

  for (int i = 0; i < m; i++) {
    std::cout << flow_on_edge[i] << "\n";
  }

  return 0;
}
