#include <iostream>

#define DEBUG true

using namespace std;

int inputs[1000001];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  if (DEBUG) {
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
  }

  int N, M, K;

  cin >> N >> M >> K;

  for (int i = 1; i <= N; ++i) {
    cin >> inputs[i];
  }

  for (int i = 0; i < M + K; ++i) {
    int a, b, c;

    cin >> a >> b >> c;

    if (a == 1) {
      inputs[b] = c;
    } else {
      long long result = 1;

      for (int j = b; j <= c; ++j) {
        result *= inputs[j];
        result %= 1000000007;
      }

      cout << result << '\n';
    }
  }

  return 0;
}