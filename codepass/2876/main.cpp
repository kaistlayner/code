#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

#define DEBUG true
using namespace std;
using pii = pair<int, int>;

// ith -> group
vector<int> groups;
// group -> pii<start~end>
vector<pii> ranges;
// group -> cnt
vector<int> cnts;

// cnt max tree
vector<int> tree;

int get_left(int i) { return i * 2 + 1; }
int get_right(int i) { return i * 2 + 2; }

void init(int i, int L, int R) {
  if (L == R) {
    tree[i] = cnts[L];
    return;
  }

  int mid = (L + R) / 2;
  init(get_left(i), L, mid);
  init(get_right(i), mid + 1, R);
  tree[i] = max(tree[get_left(i)], tree[get_right(i)]);
}

int retrieve(int i, int L, int R, int s, int e) {
  if (e < L || R < s) {
    return -1;
  }
  if (s <= L && R <= e) {
    return tree[i];
  }

  int mid = (L + R) / 2;
  return max(retrieve(get_left(i), L, mid, s, e),
             retrieve(get_right(i), mid + 1, R, s, e));
}

int get_cnt(int group, int s, int e) {
  auto [S, E] = ranges[group];
  int l = max(S, s), r = min(E, e);
  return r - l + 1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("input.txt", "r", stdin);

  int N, Q;
  cin >> N >> Q;

  groups.clear();
  ranges.clear();
  cnts.clear();

  int last_value, cnt, group_idx = 0;
  for (int i = 0; i < N; ++i) {
    int num;
    cin >> num;

    if (i == 0) {
      last_value = num;
      cnt = 1;
      groups.push_back(group_idx);
      continue;
    }

    if (last_value == num) {
      cnt++;
      groups.push_back(group_idx);
    } else {
      ranges.push_back({i - cnt, i - 1});
      cnts.push_back(cnt);

      last_value = num;
      cnt = 1;
      group_idx++;

      groups.push_back(group_idx);
    }
  }
  ranges.push_back({N - cnt, N - 1});
  cnts.push_back(cnt);

  int G = cnts.size();
  tree.resize(4 * G);
  init(0, 0, G - 1);

  while (Q--) {
    int s, e;
    cin >> s >> e;
    s--, e--;

    int start_group = groups[s], end_group = groups[e];
    int mid = -1;
    if (end_group - start_group > 1) {
      mid = retrieve(0, 0, G - 1, start_group + 1, end_group - 1);
    }
    int start_cnt = get_cnt(start_group, s, e);
    int end_cnt = get_cnt(end_group, s, e);
    int max_cnt = max(start_cnt, end_cnt);

    cout << max(max_cnt, mid) << '\n';
  }

  return 0;
}