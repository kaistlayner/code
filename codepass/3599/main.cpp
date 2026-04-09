#include <bits/stdc++.h>
#define NODE_MAX 300005

using namespace std;
using pii = pair<int, int>;

vector<int> parents, levels;
vector<vector<int>> connects;
int sparse[NODE_MAX][20];

void init_sparse(int node, int level) {
  levels[node] = level;
  sparse[node][0] = parents[node];

  for (int i = 1; i < 20; ++i) {
    int value = sparse[sparse[node][i - 1]][i - 1];
    sparse[node][i] = value;
    if (!value) {
      break;
    }
  }

  for (int child : connects[node]) {
    if (child == parents[node]) {
      continue;
    }
    parents[child] = node;
    init_sparse(child, level + 1);
  }
}

int LCA(int a, int b) {
  int parent, child;
  if (levels[a] < levels[b]) {
    parent = a;
    child = b;
  } else {
    parent = b;
    child = a;
  }

  // 같은 level로 이동
  int diff = levels[child] - levels[parent];
  int cnt = 0;
  while (diff) {
    int rest = diff % 2;
    diff = diff / 2;
    if (rest) {
      child = sparse[child][cnt];
    }
    cnt++;
  }

  if (parent == child) {
    return parent;
  }

  // 같은 부모 찾기
  while (1) {
    int j = 0;
    while (1) {
      if (sparse[parent][j] == sparse[child][j]) {
        break;
      }
      j++;
    }

    if (j == 0) {
      return sparse[parent][0];
    }

    parent = sparse[parent][j - 1];
    child = sparse[child][j - 1];
  }

  return 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("input.txt", "r", stdin);

  int N;
  cin >> N;
  levels.resize(N + 1);
  parents.resize(N + 1);
  connects.resize(N + 1);

  for (int i = 1; i <= N - 1; ++i) {
    int a, b;
    cin >> a >> b;
    connects[a].push_back(b);
    connects[b].push_back(a);
  }

  init_sparse(1, 0);

  int Q;
  cin >> Q;

  while (Q--) {
    int a, b;
    cin >> a >> b;
    cout << LCA(a, b) << '\n';
  }

  return 0;
}