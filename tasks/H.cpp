#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

typedef long long Ll;
bool possible = true;

const Ll cInf = 1000000000000000000LL;

struct Edge {
  int to;
  int s;
};

bool Check(int n, const std::vector<int>& p, const std::vector<Ll>& d, Ll x) {
  std::vector<int> sol(n + 1, 0);
  std::vector<bool> used_val(n + 1, false);
  for (int i = 1; i <= n; i++) {
    Ll val = (Ll)p[i] * x + d[i];
    if (val < 1 || val > n) {
      return false;
    }
    sol[i] = (int)val;
  }
  for (int i = 1; i <= n; i++) {
    if (used_val[sol[i]]) {
      return false;
    }
    used_val[sol[i]] = true;
  }
  for (int i = 1; i <= n; i++) {
    std::cout << sol[i] << " ";
  }
  std::cout << "\n";
  return true;
}

void ProcessBfs(const std::vector<std::vector<Edge>>& graph,
                std::vector<int>& p, std::vector<Ll>& d,
                std::vector<bool>& used, bool& x_fixed, Ll& x_value) {
  std::queue<int> q;
  q.push(1);
  used[1] = true;
  p[1] = 1;
  d[1] = 0;
  while (!q.empty() && possible) {
    int u = q.front();
    q.pop();
    for (const auto& edge : graph[u]) {
      int v = edge.to;
      int s = edge.s;
      int new_p = -p[u];
      Ll new_d = s - d[u];
      if (!used[v]) {
        used[v] = true;
        p[v] = new_p;
        d[v] = new_d;
        q.push(v);
      } else {
        int coef = p[v] - new_p;
        Ll rhs = new_d - d[v];
        if (coef == 0) {
          if (rhs != 0) {
            possible = false;
            break;
          }
        } else {
          if (rhs % coef != 0) {
            possible = false;
            break;
          }
          Ll cand = rhs / coef;
          if (!x_fixed) {
            x_fixed = true;
            x_value = cand;
          } else {
            if (x_value != cand) {
              possible = false;
              break;
            }
          }
        }
      }
    }
  }
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;

  std::vector<std::tuple<int, int, int>> edges;
  std::vector<std::vector<Edge>> graph(n + 1);
  for (int i = 0; i < m; i++) {
    int u;
    int v;
    int s;
    std::cin >> u >> v >> s;
    graph[u].push_back({v, s});
    graph[v].push_back({u, s});
    edges.push_back({u, v, s});
  }

  std::vector<int> p(n + 1, 0);
  std::vector<Ll> d(n + 1, 0);
  std::vector<bool> used(n + 1, false);

  bool x_fixed = false;
  Ll x_value = 0;

  ProcessBfs(graph, p, d, used, x_fixed, x_value);

  if (!possible) {
    std::cout << -1 << "\n";
    return 0;
  }

  if (x_fixed) {
    if (!Check(n, p, d, x_value)) {
      std::cout << -1 << "\n";
    }
    return 0;
  }

  Ll l = -cInf;
  Ll r = cInf;
  for (int v = 1; v <= n; v++) {
    if (p[v] == 1) {
      l = std::max(l, (Ll)1 - d[v]);
      r = std::min(r, (Ll)n - d[v]);
    } else {
      l = std::max(l, (Ll)d[v] - n);
      r = std::min(r, (Ll)d[v] - 1);
    }
  }

  bool found = false;
  for (Ll cand = l; cand <= r; cand++) {
    if (Check(n, p, d, cand)) {
      found = true;
      break;
    }
  }
  if (!found) {
    std::cout << -1 << "\n";
  }
  return 0;
}
