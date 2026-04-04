#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

#define DEBUG true
using namespace std;
using pii = pair<int, int>;

vector<int> cola, pizza, tree_cola, tree_pizza;

int get_left(int i) { return i * 2 + 1; }
int get_right(int i) { return i * 2 + 2; }
int get_parent(int i) { return (i - 1) / 2; }

void init(int i, int L, int R) {
  if (L == R) {
    tree_cola[i] = cola[L];
    tree_pizza[i] = pizza[L];
    return;
  }

  int mid = (L + R) / 2;
  init(get_left(i), L, mid);
  init(get_right(i), mid + 1, R);
  tree_cola[i] = max(tree_cola[get_left(i)], tree_cola[get_right(i)]);
  tree_pizza[i] = max(tree_pizza[get_left(i)], tree_pizza[get_right(i)]);
}

int target;
int target_idx;
void find_target_idx(int i, int L, int R) {
  if (L <= target && target <= R) {
    if (L == R) {
      target_idx = i;
    } else {
      int mid = (L + R) / 2;
      find_target_idx(get_left(i), L, mid);
      find_target_idx(get_right(i), mid + 1, R);
    }
  }
}

void update(int i, int mode) {
  // 본인이 max인 경우, 아닌 경우까지 올라가서 다시 init
  // 아닌 경우, 본인이 max보다 커지면, max일떄까지 부모로 가서 업데이트
}

void retrieve(int i, int L, int R, int l, int r) {
  // retrieve 왼쪽 구역 or retrieve 오른쪽 구역 => retrieve 재귀
  // 아니면 왼쪽에서 콜라, 오른쪽에서 피자 => 계산
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("input.txt", "r", stdin);

  int N;
  cin >> N;
  cola.resize(N);
  pizza.resize(N);
  tree_cola.resize(4 * N);
  tree_pizza.resize(4 * N);

  for (int i = 0; i < N; ++i) {
    cin >> cola[i];
  }
  for (int i = 0; i < N; ++i) {
    cin >> pizza[i];
  }

  int Q;
  cin >> Q;
  while (Q--) {
    int mode, from, to;
    cin >> mode >> from >> to;
  }

  return 0;
}