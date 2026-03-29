#include <bits/stdc++.h>
#define DEBUG false
#define Y_MAX 100000000
using namespace std;
using pii = pair<int, int>;

int rain, N, L = Y_MAX, R = -1;
map<int, set<pii>> targets, lazy; // idx->vector<x>

// 전체 범위에 있는 철판 vector 저장
// -> 점점 범위 줄이며 갯수 체크
// -> 갯수 rain 이하면 그 range vector에 있는거 후보에서 다 제거
// -> 갯수 넘쳐도 후보에 남은 애가 없다면 skip

int get_left(int i) { return 2 * i + 1; }
int get_right(int i) { return 2 * i + 2; }

void append(set<pii> &a, set<pii> &b) { a.insert(b.begin(), b.end()); }
void remove(set<int> &a, set<pii> &b) {
  for (auto &[x, i] : b) {
    if (DEBUG) {
      if (a.find(i) != a.end()) {
        printf("\t%d erased! \n", i);
      }
    }
    a.erase(i);
  }
}

void remove_some(set<int> &a, set<pii> &b, int n) {
  int last_x = -1;
  for (auto &[x, i] : b) {
    if (DEBUG) {
      printf("\t%d trying.. \n", i);
      if (a.find(i) != a.end()) {
        printf("\t!!%d erased!! \n", i);
      }
    }
    a.erase(i);
    if (last_x != x) {
      n--;
      if (!n) {
        break;
      }
    }
    last_x = x;
  }
}

void push(int i, int L, int R) {
  if (lazy[i].size()) {
    append(targets[i], lazy[i]);
    if (L != R) {
      append(lazy[get_left(i)], lazy[i]);
      append(lazy[get_right(i)], lazy[i]);
    }
    lazy[i].clear();
  }
}

void update(int i, int L, int R, int l, int r, pii x) {
  if (R < l || r < L) {
    return;
  }
  if (l <= L && R <= r) {
    if (DEBUG) {
      printf("[lazy]\t%d(%d~%d) inserted into %d(%d~%d)\n", x.second, l, r, i,
             L, R);
    }
    lazy[i].insert(x);
    return;
  }
  targets[i].insert(x);
  if (DEBUG) {
    printf("\t%d(%d~%d) inserted into %d(%d~%d)\n", x.second, l, r, i, L, R);
  }

  int mid = (L + R) / 2;
  update(get_left(i), L, mid, l, r, x);
  update(get_right(i), mid + 1, R, l, r, x);
}

set<int> candidates;
void resolve(int i, int L, int R) {
  push(i, L, R);
  if (targets[i].empty()) {
    return;
  }
  if (DEBUG) {
    printf("range %d ~ %d\n", L, R);
    cout << "\ttargets: ";
    for (auto [xx, ii] : targets[i]) {
      printf("(%d, %d), ", xx, ii);
    }
    cout << '\n';
  }

  if (targets[i].size() <= rain) {
    remove(candidates, targets[i]);
    return;
  }
  if (L == R) {
    remove_some(candidates, targets[i], rain);
    return;
  }

  int mid = (L + R) / 2;
  resolve(get_left(i), L, mid);
  resolve(get_right(i), mid + 1, R);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  //   freopen("input.txt", "r", stdin);

  cin >> rain >> N;

  struct Input {
    int n, x, y_min, y_max;
  };
  queue<Input> q;

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
    Input input = {n, x, y_min, y_max - 1};
    q.push(input);
  }
  while (!q.empty()) {
    Input input = q.front();
    q.pop();
    update(0, L, R, input.y_min, input.y_max, {input.x, input.n});
  }
  resolve(0, L, R);

  for (int i : candidates) {
    cout << i << ' ';
  }
  if (candidates.empty()) {
    cout << 0;
  }
  cout << '\n';

  return 0;
}
