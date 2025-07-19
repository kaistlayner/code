#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
using namespace std;

#define DEBUG true

using lli = long long int;

unordered_map<string, lli> nmap;
map<lli, string> vmap;

void init();
void insert(string name, lli value);
void delete_elem(string name);
void rank_elem(lli value);
void sum(lli value);

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  if (DEBUG) {
    // freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
  }

  lli Q;
  cin >> Q;

  for (lli i = 1; i <= Q; ++i){
      string order;
      cin >> order;

      if(order == "init"){
          init();
      }
      else if(order == "insert"){
          string name; lli value;
          cin >> name >> value;
          insert(name, value);
      }
      else if(order == "delete"){
          string name;
          cin >> name;
          delete_elem(name);
      }
      else if(order == "rank"){
          lli value;
          cin >> value;
          rank_elem(value);
      }else if(order == "sum"){
          lli value;
          cin >> value;
          sum(value);
      }
  }

  return 0;
}

///////////////////////////////////////////////////////////////

void init(){
    nmap.clear();
    vmap.clear();
}

void insert(string name, lli value){
    if(nmap[name] != 0 || vmap[value] != ""){
        cout << 0 << '\n';
        return;
    }

    nmap[name] = value;
    vmap[value] = name;
    cout << 1 << '\n';
}

void delete_elem(string name){
    lli value = nmap[name];
    cout << value << '\n';

    if(value == 0) return;
    vmap.erase(value);
    nmap.erase(name);
}

void rank_elem(lli k){
    if (vmap.size() < k){
        cout << "None" << '\n';
        return;
    }

    auto iter = vmap.begin();
    advance(iter, k-1);
    
    cout << iter->second << '\n';
}

void sum(lli value){
    auto iter = vmap.upper_bound(value);
    lli sum = 0;

    while(1){
        if(iter == vmap.begin()) break;
        iter--;
        sum += iter->first;
    }

    cout << sum << '\n';
}