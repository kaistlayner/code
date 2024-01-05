#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  int test_case;
  int T;

  // freopen("input.txt", "r", stdin);
  cin >> T;

  int sum = 0, max = 0, curr;

  for (test_case = 1; test_case <= T; ++test_case) {
    cin >> curr;
    sum += curr;
    if (curr > max) max = curr;
  }

  double avg = (double)sum / T;
  double result = avg / max * 100;

  cout << result;

  return 0;
}