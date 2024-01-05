#include <iostream>

using namespace std;

string maze[100];
int move_cnt[100][100];
int N, M;

void move(int x, int y, int cnt) {
  // invalid
  if (x < 0 || x >= N || y < 0 || y >= M) return;
  if (maze[x][y] != '1') return;

  if (move_cnt[x][y] == 0 || cnt + 1 < move_cnt[x][y]) {
    // save move count
    move_cnt[x][y] = ++cnt;

    if (x == N - 1 && y == M - 1) return;
    // keep moving
    move(x - 1, y, cnt);
    move(x + 1, y, cnt);
    move(x, y - 1, cnt);
    move(x, y + 1, cnt);
  }
}

int main(int argc, char** argv) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> N >> M;

  for (int i = 0; i < N; ++i) {
    string line;
    cin >> line;
    maze[i] = line;
  }

  move(0, 0, 0);
  cout << move_cnt[N - 1][M - 1] << endl;

  return 0;
}