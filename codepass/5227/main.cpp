#include <iostream>
#include <vector>

#define DEBUG true
using namespace std;

int max_sum, max_idx, last_max_sum;
string s;
vector<int> sums;
vector<int> lazy_l, lazy_r;

int left_idx(int idx) { return 2 * idx + 1; }
int right_idx(int idx) { return 2 * idx + 2; }

void init() {
  int cnt = 1;
  for (int i = 1; i < s.size(); ++i) {
    if (s[i] == 'R')
      cnt++;
  }
  sums[0] = cnt;
  max_sum = cnt;
  max_idx = 0;

  for (int i = 1; i < s.size(); ++i) {
    if (s[i - 1] == 'R')
      cnt--;
    if (s[i] == 'L')
      cnt++;
    sums[i] = cnt;
    if (cnt > max_sum) {
      max_sum = cnt;
      max_idx = i;
    }
  }
}

void resolve_lazy(int l, int r) {
  for (int i = 0; i <= r; ++i) {
    // resolve lazy_r
    if (lazy_r[i]) {
      // printf("%d rchanged %d -> %d\n", i, sums[i], sums[i] + lazy_r[i]);
      sums[i] += lazy_r[i];
      if (i < s.size() - 1)
        lazy_r[i + 1] += lazy_r[i];
      lazy_r[i] = 0;
    }
  }
  for (int i = s.size() - 1; i >= l; --i) {
    // resolve lazy_l
    if (lazy_l[i]) {
      // printf("%d lchanged %d -> %d\n", i, sums[i], sums[i] + lazy_l[i]);
      sums[i] += lazy_l[i];
      if (i > 0)
        lazy_l[i - 1] += lazy_l[i];
      lazy_l[i] = 0;
    }
  }

  for (int i = l; i <= r; ++i) {
    if (sums[i] > max_sum) {
      // printf("max updated %d(%d) -> %d(%d)\n", max_idx, max_sum, i, sums[i]);
      max_sum = sums[i];
      max_idx = i;
      if (max_sum > last_max_sum)
        break;
    }
  }
}

void update(int idx, char c) {
  if (s[idx] == c)
    return;
  s[idx] = c;

  if (c == 'R') {
    // update sums 0~idx-1 +1
    if (idx > 0)
      lazy_l[idx - 1]++;
    // update sums idx+1 ~ -1
    if (idx < s.size() - 1)
      lazy_r[idx + 1]--;

    last_max_sum = max_sum;
    if (max_idx < idx) {
      max_sum++;
      return;
    } else if (max_idx > idx) {
      max_sum--;
    }

    resolve_lazy(0, idx);
  } else {
    // update sums 0~idx-1 -1
    if (idx > 0)
      lazy_l[idx - 1]--;
    // update sums idx+1 ~ +1
    if (idx < s.size() - 1)
      lazy_r[idx + 1]++;

    last_max_sum = max_sum;
    if (idx < max_idx) {
      max_sum++;
      return;
    } else if (idx > max_idx) {
      max_sum--;
    }

    resolve_lazy(idx, s.size() - 1);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  if (DEBUG) {
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
  }

  cin >> s;
  sums.resize(s.size());
  lazy_l.resize(s.size());
  lazy_r.resize(s.size());
  init();

  int Q;
  cin >> Q;
  // cout << s;
  // printf(", idx: %d -> %d\n", max_idx, max_sum);

  while (Q--) {
    int idx;
    char c;
    cin >> idx >> c;
    update(idx - 1, c);
    // cout << s;
    // printf(", idx: %d -> %d\n", max_idx, max_sum);
    cout << max_sum << '\n';
  }

  return 0;
}