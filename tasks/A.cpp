#include <cstring>
#include <iostream>
#include <vector>

const int cMax = 251;

std::vector<int> graph[cMax];
int mathcr[cMax];
bool used[cMax];

bool Kuch(int v) {
  if (used[v]) {
    return false;
  }
  used[v] = true;
  for (int u : graph[v]) {
    if (mathcr[u] == 0 || Kuch(mathcr[u])) {
      mathcr[u] = v;
      return true;
    }
  }
  return false;
}

int main() {
  int n;
  int k;
  std::cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    int x;
    while (std::cin >> x && x != 0) {
      graph[i].push_back(x);
    }
  }

  int matchcnt = 0;
  for (int v = 1; v <= n; ++v) {
    memset(used, 0, sizeof(used));
    if (Kuch(v)) {
      ++matchcnt;
    }
  }

  std::cout << matchcnt << '\n';
  for (int j = 1; j <= k; ++j) {
    if (mathcr[j] != 0) {
      std::cout << mathcr[j] << " " << j << '\n';
    }
  }

  return 0;
}
