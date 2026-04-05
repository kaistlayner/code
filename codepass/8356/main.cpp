#include <bits/stdc++.h>
#include <climits>
#define DEBUG true
using namespace std;
using pii = pair<int, int>;

vector<int> cola, pizza, tree_cola, tree_pizza, tree_answer;

int get_left(int i) { return i * 2 + 1; }
int get_right(int i) { return i * 2 + 2; }

void init(int i, int L, int R) {
  if (L == R) {
    tree_cola[i] = cola[L];
    tree_pizza[i] = pizza[L];
    tree_answer[i] = -INT_MAX;
    return;
  }

  int mid = (L + R) / 2;
  init(get_left(i), L, mid);
  init(get_right(i), mid + 1, R);
  tree_cola[i] = max(tree_cola[get_left(i)], tree_cola[get_right(i)]);
  tree_pizza[i] = max(tree_pizza[get_left(i)], tree_pizza[get_right(i)]);
  tree_answer[i] = max(max(tree_answer[get_left(i)], tree_answer[get_right(i)]),
                       tree_cola[get_left(i)] + tree_pizza[get_right(i)]);
}

void update(int i, int L, int R, int mode, int idx, int value) {
  if (idx < L || R < idx) {
    return;
  }

  if (L == R) {
    if (mode == 1) {
      cola[L] = value;
      tree_cola[i] = cola[L];
    } else if (mode == 2) {
      pizza[L] = value;
      tree_pizza[i] = pizza[L];
    }
    return;
  }

  int mid = (L + R) / 2;
  update(get_left(i), L, mid, mode, idx, value);
  update(get_right(i), mid + 1, R, mode, idx, value);
  tree_cola[i] = max(tree_cola[get_left(i)], tree_cola[get_right(i)]);
  tree_pizza[i] = max(tree_pizza[get_left(i)], tree_pizza[get_right(i)]);
  tree_answer[i] = max(max(tree_answer[get_left(i)], tree_answer[get_right(i)]),
                       tree_cola[get_left(i)] + tree_pizza[get_right(i)]);
}

int retrieve_food(int i, int L, int R, int l, int r, int mode) {
  if (R < l || r < L) {
    return -INT_MAX;
  }
  if (l <= L && R <= r) {
    return mode == 1 ? tree_cola[i] : tree_pizza[i];
  }

  int mid = (L + R) / 2;
  return max(retrieve_food(get_left(i), L, mid, l, r, mode),
             retrieve_food(get_right(i), mid + 1, R, l, r, mode));
}

int retrieve(int i, int L, int R, int l, int r) {
  if (R < l || r < L) {
    return -INT_MAX;
  }
  if (l <= L && R <= r) {
    return tree_answer[i];
  }

  int mid = (L + R) / 2;
  int maxChild = max(retrieve(get_left(i), L, mid, l, r),
                     retrieve(get_right(i), mid + 1, R, l, r));
  int leftCola = retrieve_food(get_left(i), L, mid, l, r, 1);
  int rightPizza = retrieve_food(get_right(i), mid + 1, R, l, r, 2);
  return max(maxChild, leftCola + rightPizza);
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
  tree_answer.resize(4 * N);

  for (int i = 0; i < N; ++i) {
    cin >> cola[i];
  }
  for (int i = 0; i < N; ++i) {
    cin >> pizza[i];
  }
  init(0, 0, N - 1);

  int Q;
  cin >> Q;
  while (Q--) {
    int mode, from, to;
    cin >> mode >> from >> to;
    if (mode != 3) {
      update(0, 0, N - 1, mode, from - 1, to);
    } else {
      cout << retrieve(0, 0, N - 1, from - 1, to - 1) << '\n';
    }
  }

  return 0;
}