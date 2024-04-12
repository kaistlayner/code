#include <iostream>
#include <vector>
#include <map>

#define DEBUG true

using namespace std;

struct info{
  int pos, time, needs;
  vector<int> foods;
};

map<string, info> people;

int L, Q, people_cnt, food_cnt;

bool check_range(int pos, int time, int target){
  if(target > pos) target -= L;

  if(DEBUG) cout << pos << ' ' << time << ' ' << target << ": " << (target >= pos - time) << '\n';

  // pos ~ pos - time
  return target >= pos - time;
}

void eat_food(int cur_time){
  for(auto iter = people.begin(); iter != people.end();){
    info infomation = iter->second;

    if(infomation.pos != -1){
      vector<int> foods = infomation.foods;
      if(DEBUG) cout << iter->first << '\n';

      for(auto iter2 = foods.begin(); iter2 != foods.end();){
        if(DEBUG) cout << "Food: " <<*iter2 << '\n';
        if(check_range(infomation.pos, cur_time - infomation.time, *iter2) == true){
          iter2 = foods.erase(iter2);
          food_cnt--;
          infomation.needs--;
        }else{
          iter2++;
        }
        if(DEBUG) cout << '\n';
      }

      if(!infomation.needs){
        people_cnt--;
        iter = people.erase(iter);
      }else{
        infomation.foods = foods;
        int tmp = (infomation.pos - (cur_time - infomation.time)) % L;
        if(tmp < 0) tmp += L;
        infomation.pos = tmp;
        infomation.time = cur_time;
        if(DEBUG) cout << "pos: " << tmp << " time: " << cur_time << '\n';
        iter->second = infomation;
        iter++;
      }
    }else{
      iter++;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  if (DEBUG) {
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
  }

  people_cnt = 0, food_cnt = 0;
  cin >> L >> Q;

  int type, t, x, n, pos;
  string name;

  for (int i = 1; i <= Q; ++i) {
    cin >> type >> t;
    if(DEBUG) cout << "input: " << type << ' ' << t << '\n';

    if(type == 100){
      cin >> x >> name;
      pos = (x - t) % L;
      while(pos < 0) pos += L;
      food_cnt++;
      
      if(people.find(name) == people.end()){
        info sth;
        sth.pos = -1;
        people.insert({name, sth});
      }

      (people.find(name)->second).foods.push_back(pos);
      if(DEBUG) cout << "inserted: " << pos << '\n';
    }else if(type == 200){
      cin >> x >> name >> n;
      pos = (x - t) % L;
      if(pos < 0) pos += L;
      people_cnt++;

      if(people.find(name) == people.end()){
        info sth;
        people.insert({name, sth});
      }

      (people.find(name)->second).pos = pos;
      (people.find(name)->second).time = t;
      (people.find(name)->second).needs = n;
    }
    else if(type == 300){
      eat_food(t);
      cout << people_cnt << ' ' << food_cnt << '\n';
    }
  }

  return 0;
}