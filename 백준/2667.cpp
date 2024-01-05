#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

string map[25];
bool visited[25][25];
int N;

void conquer(int x, int y, int* ans) {
  if (x < 0 || x >= N || y < 0 || y >= N) return;
  if (visited[x][y]) return;
  if (map[x][y] != '1') return;

  visited[x][y] = true;
  *ans += 1;

  conquer(x - 1, y, ans);
  conquer(x + 1, y, ans);
  conquer(x, y - 1, ans);
  conquer(x, y + 1, ans);
}

int main() {
  vector<int> house_size;
  cin >> N;

  for (int i = 0; i < N; ++i) {
    string line;
    cin >> line;
    map[i] = line;
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (map[i][j] == '1' && !visited[i][j]) {
        int cnt = 0;
        conquer(i, j, &cnt);

        house_size.push_back(cnt);
      }
    }
  }

  int house_cnt = house_size.size();

  cout << house_cnt << endl;
  sort(house_size.begin(), house_size.end());
  for (int i = 0; i < house_cnt; ++i) {
    cout << house_size[i] << endl;
  }

  return 0;
}