#include <bits/stdc++.h>
#define DEBUG false
#define Y_MAX 100000000
using namespace std;
using pii = pair<int, int>;

int rain, L = Y_MAX, R = -1;
vector<int> cnt, lazy;
set<int> candidates;
vector<bool> visited;

int get_left(int i) { return 2 * i + 1; }
int get_right(int i) { return 2 * i + 2; }

void push(int i, int L, int R) {
  if (lazy[i]) {
    cnt[i] += lazy[i];
    if (L != R) {
      lazy[get_left(i)] += lazy[i];
      lazy[get_right(i)] += lazy[i];
    }
    lazy[i] = 0;
  }
}

void update(int i, int L, int R, int l, int r, pii &x) {
  push(i, L, R);

  if (cnt[i] >= rain) {
    return;
  }

  if (R < l || r < L) {
    return;
  }

  if (l <= L && R <= r) {
    lazy[i]++;
    push(i, L, R);
    if (!visited[x.second] && cnt[i] <= rain) {
      visited[x.second] = 1;
      candidates.erase(x.second);
      //   printf("\t%d(%d~%d) erased!\n", x.second, l, r);
    }
    // printf("\t%d(%d~%d) cnt become %d\n", i, L, R, cnt[i]);
    return;
  }

  int mid = (L + R) / 2;
  update(get_left(i), L, mid, l, r, x);
  update(get_right(i), mid + 1, R, l, r, x);
  cnt[i] = min(cnt[get_left(i)], cnt[get_right(i)]);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("input.txt", "r", stdin);

  int N, n_max = 0;
  cin >> rain >> N;

  priority_queue<pii> pq;
  map<int, pii> info;

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
    if (n > n_max) {
      n_max = x;
    }

    info[n] = {y_min, y_max - 1};
    pq.push({-x, n});
  }

  cnt.resize((R - L + 1) * 4);
  lazy.resize((R - L + 1) * 4);
  visited.resize(n_max + 1);

  while (!pq.empty()) {
    auto [x, n] = pq.top();
    pq.pop();
    auto [y_min, y_max] = info[n];
    pii elem = {-x, n};
    // printf("working on %d(%d~%d)\n", elem.second, y_min, y_max);
    update(0, L, R, y_min, y_max, elem);
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
