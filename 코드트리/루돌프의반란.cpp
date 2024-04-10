#include <iostream>
#include <vector>
#include <math.h>

#define DEBUG false

using namespace std;

struct santa{
  int point;
  int pos[2];
  bool dead;
  int idx;
  int stun;
};

struct tile{
  santa *person;
  bool is_rudolph;
};

int N, M, P, C, D;
int k, survive_cnt;

tile map[51][51];
int rudolph[2];
santa people[31];

void print_map(){
  for(int i = 1; i <= N; i++){
    for(int j = 1; j <= N; j++){
      if(map[i][j].person){
        cout << "[" << map[i][j].person->idx << "]";
        cout << string(map[i][j].person->stun, '*');
        cout << " ";
      }
      else if(map[i][j].is_rudolph) cout << "[R] ";
      else cout << "[ ] ";
    }
    cout << '\n';
  }
  cout << '\n';
}

bool is_in_map(int x, int y){
  return 1 <= x && x <= N && 1 <= y && y <= N;
}

int unify(int n){
  if(n > 0) return 1;
  if(n < 0) return -1;
  return 0;
}

void collide_santa(santa *person, int dx, int dy, bool flag = false){
  int x = person->pos[0], y = person->pos[1];
  if(flag) map[x][y].person = NULL;

  int x2 = x + dx, y2 = y + dy;

  if(DEBUG) cout << "collide: " << x << y << ' ' << dx << dy << ' ' << x2 << y2 << '\n';
  
  if(!is_in_map(x2, y2)){
    person->dead = true;
    survive_cnt--;
    return;
  };

  santa *tmp2 = map[x2][y2].person;
  map[x2][y2].person = person;
  person->pos[0] = x2;
  person->pos[1] = y2;

  if(DEBUG) print_map();

  if(tmp2){
    collide_santa(tmp2, unify(dx), unify(dy));
  }
}

void move_rudolph(){
  int min = 987654321;
  int direction[2];
  int prev[2];

  for(int i = 1; i <= P; i++){
    santa tmp = people[i];
    if(people[i].dead) continue;

    int dx = tmp.pos[0] - rudolph[0];
    int dy = tmp.pos[1] - rudolph[1];

    int distance = dx * dx + dy * dy;

    if(distance <= min){
      if(distance == min){
        if(prev[0] > tmp.pos[0] || (prev[0] == tmp.pos[0] && prev[1] > tmp.pos[1])){
          continue;
        }
      }

      min = distance;
      direction[0] = unify(dx);
      direction[1] = unify(dy);
      prev[0] = tmp.pos[0];
      prev[1] = tmp.pos[1];
    }
  }

  int x = rudolph[0], y = rudolph[1];
  int x2 = x + direction[0], y2 = y + direction[1];
  rudolph[0] = x2;
  rudolph[1] = y2;

  map[x][y].is_rudolph = false;
  map[x2][y2].is_rudolph = true;

  if(map[x2][y2].person){
    santa *tmp = map[x2][y2].person;
    tmp->point += C;
    tmp->stun = 2;

    collide_santa(tmp, C * direction[0], C * direction[1], true);
  }

  if(DEBUG) print_map();
};

void move_santa_check(int x, int y, int dx, int dy){
  santa *tmp = map[x][y].person;
  int x2 = x + dx, y2 = y + dy;

  if(!map[x2][y2].is_rudolph){
    map[x][y].person = NULL;
    map[x2][y2].person = tmp;
    tmp->pos[0] = x2;
    tmp->pos[1] = y2;
  }else{
    tmp->point += D;
    tmp->stun = 1;

    collide_santa(tmp, (1-D) * dx, (1-D) * dy, true);
  }
}

void move_santa(){
  for(int i = 1; i <= P; i++){
    santa tmp = people[i];
    if(tmp.dead) continue;
    else if(tmp.stun){
      people[i].stun--;
      continue;
    }

    int x = tmp.pos[0], y = tmp.pos[1];

    vector<pair<int, int> > directions;
    directions.push_back(make_pair(-1, 0));
    directions.push_back(make_pair(0, 1));
    directions.push_back(make_pair(1, 0));
    directions.push_back(make_pair(0, -1));

    int dx = rudolph[0] - x, dy = rudolph[1] - y;
    int min = dx * dx + dy * dy;
    pair<int, int> ans(0, 0);

    for(auto &elem : directions){
      int x2 = x + elem.first, y2 = y + elem.second;

      if(!map[x2][y2].person){
        dx = rudolph[0] - x2, dy = rudolph[1] - y2;
        int distance = dx * dx + dy * dy;

        if(distance < min){
          ans = elem;
          min = distance;
        }
      }
    }

    if(!ans.first || !ans.second) move_santa_check(x, y, ans.first, ans.second);

    if(DEBUG) print_map();
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  if (DEBUG) {
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
  }

  cin >> N >> M >> P >> C >> D;

  int x, y;
  cin >> x >> y;

  map[x][y].is_rudolph = true;
  rudolph[0] = x;
  rudolph[1] = y;

  for (int i = 1; i <= P; ++i) {
    int idx;
    cin >> idx >> x >> y;

    people[idx].pos[0] = x;
    people[idx].pos[1] = y;
    people[idx].idx = idx;

    map[x][y].person = &people[idx];
  }

  k = 1;
  survive_cnt = P;

  if(DEBUG) print_map();

  while(k++ <= M && survive_cnt){
    move_rudolph();
    move_santa();

    for(int i=1; i<=P; i++){
      if(!people[i].dead) people[i].point++;
    }

    if(DEBUG) {
      for(int i=1; i<=P; i++){
        cout << people[i].point;
        if(i != P) cout << ' ';
      }
      cout << '\n' << '\n';
    }
  }

  for(int i=1; i<=P; i++){
    cout << people[i].point;
    if(i != P) cout << ' ';
  }
  cout << '\n';

  return 0;
}