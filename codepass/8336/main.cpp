#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
vector<int> pay, converted_pay, converted_idx, lazy;
vector<vector<int>> childs;
vector<pii> tree_range;

int get_left(int i) { return 2 * i + 1; }
int get_right(int i) { return 2 * i + 2; }

void update(int i, int L, int R, int l, int r, int amount) {
  if (R < l || r < L) {
    return;
  }
  if (l <= L && R <= r) {
    lazy[i] += amount;
    return;
  }

  int mid = (L + R) / 2;
  update(get_left(i), L, mid, l, r, amount);
  update(get_right(i), mid + 1, R, l, r, amount);
}

void push(int i, int L, int R) {
  if (lazy[i]) {
    if (L != R) {
      lazy[get_left(i)] += lazy[i];
      lazy[get_right(i)] += lazy[i];
    } else {
      converted_pay[L] += lazy[i];
    }
    lazy[i] = 0;
  }
}

int retrieve(int i, int L, int R, int target) {
  push(i, L, R);
  if (target < L || R < target) {
    return 0;
  }
  if (L == R) {
    return converted_pay[L];
  }

  int mid = (L + R) / 2;
  return retrieve(get_left(i), L, mid, target) +
         retrieve(get_right(i), mid + 1, R, target);
}

int idx = 1;
void init(int node) {
  converted_idx[node] = idx++;
  int in = idx - 1;

  for (int child : childs[node]) {
    init(child);
  }
  int out = idx - 1;

  tree_range[node] = {in + 1, out};
  converted_pay[converted_idx[node]] = pay[node];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("input.txt", "r", stdin);

  int N, Q;
  cin >> N >> Q;
  pay.resize(N + 1);
  converted_pay.resize(N + 1);
  childs.resize(N + 1);
  converted_idx.resize(N + 1);
  tree_range.resize(N + 1);
  lazy.resize(4 * (N + 1));

  cin >> pay[1];
  for (int i = 2; i <= N; ++i) {
    cin >> pay[i];
    int parent;
    cin >> parent;
    childs[parent].push_back(i);
  }

  init(1);

  while (Q--) {
    char mode;
    int i, x;
    cin >> mode >> i;

    if (mode == 'p') {
      cin >> x;
      auto [l, r] = tree_range[i];
      update(0, 1, N, l, r, x);
    } else {
      cout << retrieve(0, 1, N, converted_idx[i]) << '\n';
    }
  }

  return 0;
}