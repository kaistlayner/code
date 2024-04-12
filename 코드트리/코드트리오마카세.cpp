#include <iostream>
#include <vector>
#include <deque>

#define DEBUG true

using namespace std;

int L, Q;
deque<deque<string> > belt;
vector<string> customer;
vector<int> customer_cnt;

void check_belt_at(int pos){
  deque<string> belt_tile = belt.at(pos);

  for(auto iter = belt_tile.begin(); iter != belt_tile.end();){
    if((*iter).compare(customer[pos]) == 0){
      customer_cnt[pos]--;
      // never come back same person
      belt_tile.erase(iter);
    }else{
      iter++;
    }
  }

  belt.at(pos) = belt_tile;
};

void check_belt(){
  for(int i = 0; i < L; i++){
    check_belt_at(i);
  }
};

void rotate_belt(){
  deque<string> front = belt.front();
  belt.pop_front();
  belt.push_back(front);
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  if (DEBUG) {
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
  }

  cin >> L >> Q;
  for(int i = 0; i < L; i++){
    deque<string> belt_tile;
    belt.push_back(belt_tile);
  }

  customer.assign(L, "");
  customer_cnt.assign(L, 0);

  int type, t, pos, n, people_cnt = 0, food_cnt = 0, tick = 0;
  string name;

  for (int i = 1; i <= Q; ++i) {
    cin >> type >> t;
    cout << type << ' ' << t << '\n';

    int gap = (t - tick) % L;

    while(gap--){
      rotate_belt();
      check_belt();
    }

    if(type == 100){
      cin >> pos >> name;
      belt.at(pos).push_back(name);
      food_cnt++;
      check_belt_at(pos);
    }else if(type == 200){
      cin >> pos >> name >> n;
      customer[pos] = name;
      customer_cnt[pos] = n;
      people_cnt++;
      check_belt_at(pos);
    }else if(type == 300){
      cout << people_cnt << ' ' << food_cnt << '\n';
    }

    tick = t;
  }

  return 0;
}