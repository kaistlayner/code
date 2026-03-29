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
      // printf("\t%d(%d~%d) erased!\n", x.second, l, r);
    }
    // printf("\t%d(%d~%d) cnt become %d\n", i, L, R, cnt[i]);
    return;
  }

  int mid = (L + R) / 2;
  update(get_left(i), L, mid, l, r, x);
  update(get_right(i), mid + 1, R, l, r, x);
  cnt[i] = min(cnt[get_left(i)], cnt[get_right(i)]);
}

struct Plate {
  int n, x, y_min, y_max;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("input.txt", "r", stdin);

  int N, n_max = 0;
  cin >> rain >> N;

  vector<Plate> plates;
  vector<int> ys;

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
      n_max = n;
    }

    plates.push_back({n, x, y_min, y_max});

    ys.push_back(y_min);
    ys.push_back(y_max);
  }

  sort(ys.begin(), ys.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());

  int segN = (int)ys.size();

  auto get_y = [&](int y) {
    return (int)(lower_bound(ys.begin(), ys.end(), y) - ys.begin());
  };

  sort(plates.begin(), plates.end(), [](const Plate &a, const Plate &b) {
    if (a.x != b.x)
      return a.x < b.x;
    return a.n < b.n;
  });

  cnt.resize(segN * 4);
  lazy.resize(segN * 4);
  visited.resize(n_max + 1);

  for (auto &plate : plates) {
    int l = get_y(plate.y_min);
    int r = get_y(plate.y_max) - 1;
    pii elem = {plate.x, plate.n};

    // printf("working on %d(%d~%d) -> compressed (%d~%d)\n",
    //        plate.n, plate.y_min, plate.y_max, l, r);

    update(0, 0, segN - 1, l, r, elem);
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