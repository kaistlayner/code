#include <iostream>
#include <vector>

#define DEBUG true

using namespace std;
using pii = pair<int, int>;

vector<int> origins, sums;
vector<bool> lazy;

int left_idx(int idx) { return 2 * idx + 1; }

int right_idx(int idx) { return 2 * idx + 2; }

void push(int i, int L, int R) {
  if (lazy[i]) {
    lazy[i] = 0;
    sums[i] = (R - L + 1) - sums[i];

    if (L != R) {
      lazy[left_idx(i)] = !lazy[left_idx(i)];
      lazy[right_idx(i)] = !lazy[right_idx(i)];
    }
  }
}

int update(int i, int L, int R, int l, int r) {
  // printf("%d's range %d ~ %d, checking %d ~ %d\n", i, L, R, l, r);
  push(i, L, R);
  if (R < l || r < L) {
    return sums[i];
  }
  if (l <= L && R <= r) {
    lazy[i] = !lazy[i];
    push(i, L, R);
    return sums[i];
  }

  int mid = (L + R) / 2;
  sums[i] = update(left_idx(i), L, mid, l, r) +
            update(right_idx(i), mid + 1, R, l, r);
  return sums[i];
}

int retrieve(int i, int L, int R, int l, int r) {
  push(i, L, R);

  if (R < l || r < L) {
    return 0;
  }
  if (l <= L && R <= r) {
    return sums[i];
  }

  int mid = (L + R) / 2;
  return retrieve(left_idx(i), L, mid, l, r) +
         retrieve(right_idx(i), mid + 1, R, l, r);
}

void print_all(int N) {
  for (int i = 0; i < N; ++i) {
    cout << retrieve(0, 0, N - 1, i, i) << ' ';
  }
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  if (DEBUG) {
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
  }

  int N, M;
  cin >> N >> M;
  origins.resize(N);
  sums.resize(4 * N);
  lazy.resize(4 * N);

  // print_all(N);
  for (int i = 1; i <= M; ++i) {
    int Q, S, E;
    cin >> Q >> S >> E;
    if (Q == 0) {
      update(0, 0, N - 1, S - 1, E - 1);
      // print_all(N);
    } else {
      cout << retrieve(0, 0, N - 1, S - 1, E - 1) << '\n';
    }
  }

  return 0;
}