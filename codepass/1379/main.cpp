#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

vector<vector<int>> connects;
vector<int> visited, levels, low;
set<int> ans;

void dfs(int node, int parent, bool isRoot, int level) {
  visited[node] = true;
  levels[node] = low[node] = level;
  int cnt = 0;

  for (int child : connects[node]) {
    if (child == parent) {
      continue;
    }
    if (!visited[child]) {
      cnt++;
      dfs(child, node, false, level + 1);
      if (!isRoot && low[child] >= level) {
        ans.insert(node);
      }
    }
    low[node] = min(low[node], low[child]);
  }

  if (isRoot && cnt > 1) {
    ans.insert(node);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("input.txt", "r", stdin);

  int n, m;
  cin >> n >> m;
  connects.resize(n + 1);
  visited.resize(n + 1);
  levels.resize(n + 1);
  low.resize(n + 1);

  while (m--) {
    int a, b;
    cin >> a >> b;
    connects[a].push_back(b);
    connects[b].push_back(a);
  }

  dfs(1, 0, true, 0);
  for (int node : ans) {
    cout << node << ' ';
  }
  if (!ans.size()) {
    cout << -1;
  }

  return 0;
}