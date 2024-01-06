#include <iostream>
#include <queue>

using namespace std;

queue<pair<int, int> > q;
bool visited[100001] = {0};

void move(int value, int step) {
  if (value < 0 || value > 100000) return;
  if (visited[value]) return;

  q.push(make_pair(value, step));
  visited[value] = true;

  // cout << "\tinsert: " << value << " " << step << endl;
}

int main() {
  int N, K, step;

  cin >> N >> K;
  // freopen("output.txt", "w", stdout);

  q.push(make_pair(N, 0));

  while (1) {
    pair<int, int> elem = q.front();
    int value = elem.first;
    step = elem.second;
    q.pop();

    // cout << "pop: " << value << " " << step << endl;

    if (value == K) break;

    move(value - 1, step + 1);
    move(value + 1, step + 1);
    move(value * 2, step + 1);
  }

  cout << step << endl;

  return 0;
}