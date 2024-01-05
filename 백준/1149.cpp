#include <iostream>

using namespace std;

int main() {
  int N, dp[3] = {0};

  cin >> N;

  for (int i = 1; i <= N; ++i) {
    int R, G, B;
    cin >> R >> G >> B;

    int tmp[3];
    tmp[0] = min(dp[1], dp[2]) + R;
    tmp[1] = min(dp[0], dp[2]) + G;
    tmp[2] = min(dp[0], dp[1]) + B;

    dp[0] = tmp[0];
    dp[1] = tmp[1];
    dp[2] = tmp[2];
  }

  int ans = min(dp[0], min(dp[1], dp[2]));
  cout << ans << endl;

  return 0;
}