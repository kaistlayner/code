#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;
vector<vector<pii>> connects;
vector<int> visited;
int R;

int dp(int node, int parent) {
  if (node != R && connects[node].size() == 1) {
    return connects[node][0].second;
  }

  int total = 0;
  for (auto [child, cost] : connects[node]) {
    if (child == parent) {
      continue;
    }
    total += min(cost, dp(child, node));
  }
  return total;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("input.txt", "r", stdin);

  while (1) {
    int N;
    cin >> N >> R;
    if (!N && !R) {
      break;
    }
    connects.clear();
    connects.resize(N + 1);

    for (int i = 1; i <= N - 1; ++i) {
      int u, v, w;
      cin >> u >> v >> w;
      connects[u].push_back({v, w});
      connects[v].push_back({u, w});
    }

    cout << dp(R, 0) << '\n';
  }

  return 0;
}