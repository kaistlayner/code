#include <iostream>

#define DEBUG true

using namespace std;

int main() {
  if (DEBUG) {
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
  }
  int N, M, K;
  int64_t numbers[1000001];

  cin >> N >> M >> K;

  for (int i = 1; i <= N; ++i) {
    cin >> numbers[i];
  }

  for (int i = 0; i < M + K; ++i) {
    int a, b, c;
    cin >> a >> b >> c;

    int64_t upper_sum = 0, lower_sum = 0;

    if (a == 1) {
      numbers[b] = c;
    } else {
      for (int j = b; j <= c; ++j) {
        bool is_positive = lower_sum >= 0;
        int64_t curr = numbers[j];

        if (!(curr ^ is_positive)) {
          lower_sum += curr;
        } else {
          lower_sum = lower_sum - is_positive * ((int64_t)1 << 62) + curr;
          upper_sum += is_positive;
        }
      }
      cout << lower_sum << endl;
    }
  }

  return 0;
}