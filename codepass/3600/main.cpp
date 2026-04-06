#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

int N;
vector<vector<int>> connected;
vector<int> visited;
vector<int> values;

int idx = 1;
vector<int> indexs, tree;
vector<pii> range;

void index_dfs(int node) {
  indexs[node] = idx++;
  visited[node] = true;
  for (int child : connected[node]) {
    if (!visited[child]) {
      index_dfs(child);
    }
  }
  range[node] = {indexs[node], idx - 1};
}

int left_idx(int i) { return 2 * i + 1; }
int right_idx(int i) { return 2 * i + 2; }

void update_tree(int i, int L, int R, int target, int added) {
  if (target < L || R < target) {
    return;
  }

  tree[i] += added;
  if (L == R) {
    return;
  }

  int mid = (L + R) / 2;
  update_tree(left_idx(i), L, mid, target, added);
  update_tree(right_idx(i), mid + 1, R, target, added);
}

void update(int node, int value) {
  int origin_value = values[node];
  values[node] = value;

  int target = indexs[node];
  update_tree(0, 1, N, target, value - origin_value);
}

int retrieve_tree(int i, int L, int R, int l, int r) {
  if (R < l || r < L) {
    return 0;
  }

  if (l <= L && R <= r) {
    return tree[i];
  }

  int mid = (L + R) / 2;
  return retrieve_tree(left_idx(i), L, mid, l, r) +
         retrieve_tree(right_idx(i), mid + 1, R, l, r);
}

int retrieve(int node) {
  auto [from, to] = range[node];
  return retrieve_tree(0, 1, N, from, to);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("input.txt", "r", stdin);

  cin >> N;
  connected.resize(N + 1);
  visited.resize(N + 1);
  values.resize(N + 1);

  for (int i = 2; i <= N; ++i) {
    int s, e;
    cin >> s >> e;
    connected[s].push_back(e);
    connected[e].push_back(s);
  }

  indexs.resize(N + 1);
  range.resize(N + 1);
  index_dfs(1);

  int Q;
  cin >> Q;
  tree.resize(4 * (N + 1));

  while (Q--) {
    int mode;
    cin >> mode;

    if (mode == 1) {
      int node, value;
      cin >> node >> value;
      update(node, value);
    } else {
      int node;
      cin >> node;
      cout << retrieve(node) << '\n';
    }
  }

  return 0;
}