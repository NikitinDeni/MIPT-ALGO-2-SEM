#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> g;
std::vector<std::vector<int>> gr;
std::vector<bool> used;
std::vector<int> order;
std::vector<int> comp;

void Dfs1(int v) {
  used[v] = true;
  for (int to : g[v]) {
    if (!used[to]) {
      Dfs1(to);
    }
  }
  order.push_back(v);
}

void Dfs2(int v, int cl) {
  comp[v] = cl;
  for (int to : gr[v]) {
    if (comp[to] == 0) {
      Dfs2(to, cl);
    }
  }
}

void Printres(std::vector<int>& res) {
  for (auto x : res) {
    std::cout << x << " ";
  }
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;

  g.resize(n + 1);
  gr.resize(n + 1);
  used.assign(n + 1, false);
  comp.assign(n + 1, 0);

  for (int i = 0; i < m; i++) {
    int u;
    int v;
    std::cin >> u >> v;
    g[u].push_back(v);
    gr[v].push_back(u);
  }

  for (int i = 1; i <= n; i++) {
    if (!used[i]) {
      Dfs1(i);
    }
  }

  reverse(order.begin(), order.end());

  int cmpcount = 0;
  for (int v : order) {
    if (comp[v] == 0) {
      ++cmpcount;
      Dfs2(v, cmpcount);
    }
  }

  std::cout << cmpcount << "\n";
  for (int i = 1; i <= n; i++) {
    std::cout << comp[i] << " ";
  }
  std::cout << "\n";

  return 0;
}
