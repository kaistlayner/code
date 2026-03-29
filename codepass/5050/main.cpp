#include <bits/stdc++.h>
#define DEBUG false
#define Y_MAX 100000000
using namespace std;
using pii = pair<int, int>;

int rain, L = Y_MAX, R = -1;
vector<int> tree, lazy;
set<int> candidates;

int get_left(int i) { return 2 * i + 1; }
int get_right(int i) { return 2 * i + 2; }

void update(int i, int L, int R, int l, int r, pii x) {}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("input.txt", "r", stdin);

  int N, rain;
  cin >> rain >> N;

  struct Input {
    int x, y_min, y_max, n;
  };
  priority_queue<Input> pq;

  for (int i = 0; i < N; ++i) {
    int n, x, y_min, y_max;
    cin >> n >> x >> y_min >> y_max;
    candidates.insert(n);

    if (y_min < L) {
      L = y_min;
    }
    if (R < y_max) {
      R = y_max;
    }
    Input input = {-x, y_min, y_max - 1, n};
    pq.push(input);
  }

  while (!pq.empty()) {
    auto [x, y_min, y_max, n] = pq.top();
    pq.pop();
    update(0, L, R, y_min, y_max, {-x, n});
  }

  for (int i : candidates) {
    cout << i << ' ';
  }
  if (candidates.empty()) {
    cout << 0;
  }
  cout << '\n';

  return 0;
}
