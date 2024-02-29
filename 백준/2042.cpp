#include <iostream>

#define DEBUG false

using namespace std;

long long numbers[1000001];
long long tree[4000004];

void make_tree(int node, int start, int end) {
  if (start == end) {
    tree[node] = numbers[start];
  } else {
    make_tree(node * 2, start, (start + end) / 2);
    make_tree(node * 2 + 1, (start + end) / 2 + 1, end);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
  }
}

void update_tree(int node, int start, int end, int index, long long diff) {
  if (index < start || index > end) {
    return;
  }

  tree[node] += diff;

  if (start != end) {
    update_tree(node * 2, start, (start + end) / 2, index, diff);
    update_tree(node * 2 + 1, (start + end) / 2 + 1, end, index, diff);
  }
}

long long get_tree(int node, int start, int end, int from, int to) {
  if (from > end || to < start) {
    return 0;
  }

  if (from <= start && end <= to) {
    return tree[node];
  }

  return get_tree(node * 2, start, (start + end) / 2, from, to) +
         get_tree(node * 2 + 1, (start + end) / 2 + 1, end, from, to);
}

int main() {
  if (DEBUG) {
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
  }
  int N, M, K;

  cin >> N >> M >> K;

  for (int i = 1; i <= N; ++i) {
    cin >> numbers[i];
  }

  make_tree(1, 1, N);

  for (int i = 0; i < M + K; ++i) {
    int a, b;
    long long c;
    cin >> a >> b >> c;

    if (a == 1) {
      long long diff = c - numbers[b];
      numbers[b] = c;

      update_tree(1, 1, N, b, diff);
    } else if (a == 2) {
      long long sum = get_tree(1, 1, N, b, c);
      cout << sum << endl;
    }
  }

  return 0;
}