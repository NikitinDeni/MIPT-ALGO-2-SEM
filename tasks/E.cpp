#include <iostream>
#include <vector>

void StdSolve(int n, int m, std::vector<int>& w, std::vector<int>& c) {
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      if (w[i - 1] > j) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - w[i - 1]] + c[i - 1]);
      }
    }
  }

  std::vector<int> result;
  int j = m;
  for (int i = n; i > 0; i--) {
    if (dp[i][j] != dp[i - 1][j]) {
      result.push_back(i);
      j -= w[i - 1];
    }
  }

  for (int i = result.size() - 1; i >= 0; i--) {
    std::cout << result[i] << "\n";
  }
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  std::vector<int> w(n);
  std::vector<int> c(n);

  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  for (int i = 0; i < n; i++) {
    std::cin >> c[i];
  }
  StdSolve(n, m, w, c);
  return 0;
}
