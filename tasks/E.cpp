#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

struct Edge {
  int u;
  int v;
};

const int cThir = 32;

struct Pairhash {
  size_t operator()(const std::pair<int, int>& p) const {
    return ((size_t)p.first << cThir) | (unsigned int)p.second;
  }
};

int timer = 0;
std::vector<int> tin, low;
std::vector<bool> used;
std::vector<std::vector<std::pair<int, int>>> adj;
std::vector<int> bridges;
std::vector<Edge> edges;

std::unordered_map<std::pair<int, int>, int, Pairhash> freq;

void Dfs(int v, int paredge) {
  used[v] = true;
  tin[v] = low[v] = timer++;

  for (auto& p : adj[v]) {
    int to = p.first;
    int id = p.second;

    if (id == paredge) {
      continue;
    }

    if (used[to]) {
      low[v] = std::min(low[v], tin[to]);
    } else {
      Dfs(to, id);
      low[v] = std::min(low[v], low[to]);
      if (low[to] > tin[v]) {
        int a = std::min(v, to);
        int b = std::max(v, to);
        if (freq[{a, b}] == 1) {
          bridges.push_back(id);
        }
      }
    }
  }
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;

  edges.resize(m + 1);
  adj.assign(n + 1, std::vector<std::pair<int, int>>());
  used.assign(n + 1, false);
  tin.assign(n + 1, -1);
  low.assign(n + 1, -1);

  for (int i = 1; i <= m; i++) {
    int u;
    int v;
    std::cin >> u >> v;
    edges[i] = {u, v};

    if (u == v) {
      continue;
    }

    adj[u].push_back({v, i});
    adj[v].push_back({u, i});

    int a = std::min(u, v);
    int b = std::max(u, v);
    freq[{a, b}]++;
  }

  for (int i = 1; i <= n; i++) {
    if (!used[i]) {
      Dfs(i, -1);
    }
  }

  std::sort(bridges.begin(), bridges.end());

  std::cout << bridges.size() << "\n";
  for (int id : bridges) {
    std::cout << id << " ";
  }
  std::cout << "\n";

  return 0;
}
