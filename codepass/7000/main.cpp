#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

int N, ans, min_store, min_idx;
vector<int> costs, visited;
vector<vector<int>> connects, rconnects;
stack<int> st;

void dfs(int n) {
  visited[n] = 1;
  for (int i : connects[n]) {
    if (!visited[i]) {
      dfs(i);
    }
  }
  st.push(n);
}

void rdfs(int n) {
  visited[n] = 1;
  // cout << n << " visited!\n";
  if (costs[n] < min_store) {
    min_store = costs[n];
    min_idx = n;
  }

  for (int i : rconnects[n]) {
    if (!visited[i]) {
      rdfs(i);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("input.txt", "r", stdin);

  cin >> N;
  costs.resize(N + 1);
  connects.resize(N + 1);
  rconnects.resize(N + 1);
  visited.resize(N + 1);

  for (int i = 1; i <= N; ++i) {
    cin >> costs[i];
  }
  for (int i = 1; i <= N; ++i) {
    string s;
    cin >> s;
    for (int j = 1; j <= N; ++j) {
      if (s[j - 1] == '1') {
        connects[i].push_back(j);
        rconnects[j].push_back(i);
      }
    }
  }

  for (int i = 1; i <= N; ++i) {
    if (!visited[i]) {
      dfs(i);
    }
  }
  visited.assign(N + 1, 0);

  ans = 0;
  while (!st.empty()) {
    int top = st.top();
    st.pop();
    if (!visited[top]) {
      min_store = 1110000;
      rdfs(top);
      // cout << min_idx << " " << min_store << '\n';
      ans += min_store;
    }
  }

  cout << ans << '\n';

  return 0;
}