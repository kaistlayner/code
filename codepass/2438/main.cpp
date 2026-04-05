#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
struct Elem {
  int max;
  int L, R;
};
vector<int> origin;
vector<Elem> tree;

int left_idx(int idx) { return 2 * idx + 1; }
int right_idx(int idx) { return 2 * idx + 2; }

void init(int i, int L, int R) {
  if (L == R) {
    tree[i] = {1, L, R};
    return;
  }

  int mid = (L + R) / 2;
  init(left_idx(i), L, mid);
  init(right_idx(i), mid + 1, R);
}

void update(int i, int L, int R, int idx) {
  if (idx < L || R < idx) {
    return;
  }

  if (L == R) {
    return;
  }

  int mid = (L + R) / 2;
  update(left_idx(i), L, mid, idx);
  update(right_idx(i), mid + 1, R, idx);

  if (tree[left_idx(i)].max < tree[right_idx(i)].max) {
    tree[i] = tree[right_idx(i)];
  } else {
    tree[i] = tree[left_idx(i)];
  }

  if (origin[mid] != origin[mid + 1]) {
    int cnt = 2, range_L, range_R;

    if (tree[left_idx(i)].R == mid) {
      range_L = tree[left_idx(i)].L;
      cnt += tree[left_idx(i)].max - 1;
    } else {
      range_L = mid - 1;
      while (L <= range_L) {
        if (origin[range_L] == origin[range_L + 1]) {
          break;
        }
        cnt++;
        range_L--;
      }
      range_L++;
    }

    if (tree[right_idx(i)].L == mid + 1) {
      range_R = tree[right_idx(i)].R;
      cnt += tree[right_idx(i)].max - 1;
    } else {
      range_R = mid + 2;
      while (range_R <= R) {
        if (origin[range_R] == origin[range_R - 1]) {
          break;
        }
        cnt++;
        range_R++;
      }
      range_R--;
    }

    if (cnt > tree[i].max) {
      tree[i] = {cnt, range_L, range_R};
    }
  }

  //   printf("[DEBUG] %d(%d~%d) become %d\n", i, L + 1, R + 1, tree[i]);
  //   printf("[DEBUG] \tcompare %dth(%d) and %dth(%d)\n", mid + 1, origin[mid],
  //          mid + 2, origin[mid + 1]);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("input.txt", "r", stdin);

  int N, Q;
  cin >> N >> Q;
  origin.resize(N, 0);
  tree.resize(4 * N);
  init(0, 0, N - 1);

  while (Q--) {
    int idx;
    cin >> idx;
    origin[idx - 1] = !origin[idx - 1];
    update(0, 0, N - 1, idx - 1);
    cout << tree[0].max << '\n';
  }

  return 0;
}