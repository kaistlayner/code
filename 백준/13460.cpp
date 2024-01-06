#include <iostream>
#include <queue>
#include <vector>

#define DEBUG true

using namespace std;

int N, M;

struct elem {
  int r_x, r_y, b_x, b_y, step;
  bool end;
  string map[10];
};

queue<elem> q;  // map, (pos(x, y), step)
int memo[10][10][10][10];

void print_map(elem from, elem to) {
  if (!DEBUG) return;

  cout << endl;
  cout << "step: " << from.step << " -> " << to.step << endl;

  for (int i = 0; i < N; ++i) {
    cout << from.map[i] << "\t" << to.map[i] << endl;
  }

  cout << endl;
}

void copy_map(string map[10], string new_map[10]) {
  for (int i = 0; i < 10; ++i) {
    new_map[i] = map[i];
  }
}

elem move_map(elem info, int dx, int dy) {
  bool changed = false, blue_done = false, blue_dead = false;
  elem new_elem = {info.r_x, info.r_y, info.b_x, info.b_y, info.step + 1};
  copy_map(info.map, new_elem.map);

  if (info.step >= 10) {
    return new_elem;
  }

  new_elem.map[info.r_x][info.r_y] = '.';

  // move red
  while (new_elem.map[new_elem.r_x + dx][new_elem.r_y + dy] != '#') {
    char next_red = new_elem.map[new_elem.r_x + dx][new_elem.r_y + dy];

    if (next_red == 'O') {
      new_elem.end = true;
      break;
    }

    if (next_red == 'B') {
      if (blue_done) break;
      blue_done = true;

      new_elem.map[info.b_x][info.b_y] = '.';

      // move blue
      while (new_elem.map[new_elem.b_x + dx][new_elem.b_y + dy] != '#') {
        char next_blue = new_elem.map[new_elem.b_x + dx][new_elem.b_y + dy];

        if (next_blue == 'O') {
          blue_dead = true;
          break;
        }

        // next_blue == '.'
        new_elem.b_x += dx;
        new_elem.b_y += dy;
        changed = true;
      }

      if (!blue_dead) new_elem.map[new_elem.b_x][new_elem.b_y] = 'B';
      if (blue_dead) break;
    }

    if (next_red == '.') {
      new_elem.r_x += dx;
      new_elem.r_y += dy;
      changed = true;
    }
  }

  if (!new_elem.end) new_elem.map[new_elem.r_x][new_elem.r_y] = 'R';

  new_elem.map[info.b_x][info.b_y] = '.';

  // move blue
  if (!blue_done) {
    while (new_elem.map[new_elem.b_x + dx][new_elem.b_y + dy] != '#') {
      char next_blue = new_elem.map[new_elem.b_x + dx][new_elem.b_y + dy];

      if (next_blue == 'O') {
        blue_dead = true;
        break;
      }

      if (next_blue == 'R') {
        break;
      }

      // next_blue == '.'
      new_elem.b_x += dx;
      new_elem.b_y += dy;
      changed = true;
    }
  }
  if (!blue_dead) new_elem.map[new_elem.b_x][new_elem.b_y] = 'B';

  if (new_elem.end ||
      changed && !blue_dead &&
          !memo[new_elem.r_x][new_elem.r_y][new_elem.b_x][new_elem.b_y]) {
    q.push(new_elem);
    memo[new_elem.r_x][new_elem.r_y][new_elem.b_x][new_elem.b_y] = 1;
    print_map(info, new_elem);
  }
  if (blue_dead) new_elem.end = false;
  return new_elem;
}

int main() {
  if (DEBUG) {
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
  }
  int r_x, r_y, b_x, b_y;
  string map[10];

  cin >> N >> M;

  for (int i = 0; i < N; ++i) {
    string line;
    cin >> line;
    map[i] = line;

    int idx = line.find('R');
    if (idx != string::npos) {
      r_x = i;
      r_y = idx;
    }

    idx = line.find('B');
    if (idx != string::npos) {
      b_x = i;
      b_y = idx;
    }
  }

  elem tmp = {r_x, r_y, b_x, b_y, 0};
  copy_map(map, tmp.map);
  q.push(tmp);
  memo[r_x][r_y][b_x][b_y] = 1;

  int dx[] = {0, 0, 1, -1};
  int dy[] = {1, -1, 0, 0};

  while (!q.empty()) {
    elem info = q.front();

    for (int i = 0; i < 4; ++i) {
      elem out = move_map(info, dx[i], dy[i]);
      if (out.end) {
        cout << out.step << endl;
        return 0;
      }
    }

    q.pop();
  }

  cout << -1 << endl;
  return 0;
}