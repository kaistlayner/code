#include <iostream>
#include <vector>
#include <deque>

#define DEBUG true

using namespace std;

int L, Q, people_cnt, food_cnt;
deque<deque<string> > belt;
vector<string> customer;
vector<int> customer_cnt;

void print_belt(){
  cout << '\n';
  for(int i = 0; i < L; i++){
    cout << i << ": [" << customer[i] << "] " << customer_cnt[i];
    cout << "\t\t\tfood: ";
    for(auto iter : belt[i]){
      cout << iter << ' ';
    }
    cout << '\n';
  }
  cout << '\n';
}

void check_belt_at(int pos){
  deque<string> belt_tile = belt[pos];

  for(auto iter = belt_tile.begin(); iter != belt_tile.end();){
    if((*iter).compare(customer[pos]) == 0){
      customer_cnt[pos]--;
      food_cnt--;
      iter = belt_tile.erase(iter);
      
      if(!customer_cnt[pos]){
        people_cnt--;
        customer[pos] = "";
      }
    }else{
      iter++;
    }
  }

  belt[pos] = belt_tile;
};

void check_belt(){
  for(int i = 0; i < L; i++){
    check_belt_at(i);
  }
  if(DEBUG){
    cout << "check" << '\n';
    print_belt();
  }
};

void rotate_belt(){
  deque<string> front = belt.back();
  belt.pop_back();
  belt.push_front(front);
  if(DEBUG){
    cout << "rotate" << '\n';
    print_belt();
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

  cin >> L >> Q;
  // for(int i = 0; i < L; i++){
  //   deque<string> belt_tile;
  //   belt.push_back(belt_tile);
  // }

  customer.assign(L, "");
  customer_cnt.assign(L, 0);
  people_cnt = 0;
  food_cnt = 0;

  int type, t, pos, n, tick = 0;
  string name;

  for (int i = 1; i <= Q; ++i) {
    cin >> type >> t;
    if(DEBUG) cout << "input: " << type << ' ' << t << '\n';

    int gap = (t - tick) % L;
    
    while(gap--){
      // rotate_belt();
      // check_belt();
    }

    if(type == 100){
      cin >> pos >> name;
      belt[pos].push_back(name);
      food_cnt++;
      check_belt_at(pos);
      if(DEBUG) print_belt();
    }else if(type == 200){
      cin >> pos >> name >> n;
      customer[pos] = name;
      customer_cnt[pos] = n;
      people_cnt++;
      check_belt_at(pos);
      if(DEBUG) print_belt();
    }else if(type == 300){
      cout << people_cnt << ' ' << food_cnt << '\n';
    }

    tick = t;
  }

  return 0;
}