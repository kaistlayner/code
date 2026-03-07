#include <iostream>
#include <vector>
#include <unordered_set>

#define DEBUG true
#define uset unordered_set
constexpr int MAX_NODE = 1000005;

using namespace std;
using pii = pair<int,int>;

int cnt[MAX_NODE];
uset<int> connected[MAX_NODE];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  
  if (DEBUG) {
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
  }
  
  int N, ans = 0;

  cin >> N;
  uset<int> left;
  
  for (int i = 1; i < N; ++i) {
    int u, v;
    cin >> u >> v;

    cnt[u]++;
    cnt[v]++;

    connected[u].insert(v);
    connected[v].insert(u);

    left.insert(u);
    left.insert(v);
  }

  bool coloring = false; // leaves 색칠할 차례인지 아닌지

  vector<int> leaves;
  for(int elem : left){
      if(cnt[elem] == 1){
        leaves.push_back(elem);
      }
    }
    
  while(!left.empty()){
    if(left.size() <= 2){
      ans++;
      break;
    }

    vector<int> next_leaves;

    for(int elem : leaves){
      left.erase(elem);
      for(int conn_elem : connected[elem]){
        cnt[conn_elem]--;
        connected[conn_elem].erase(elem);
        if(cnt[conn_elem] == 1) next_leaves.push_back(conn_elem);
      }
    }

    if(coloring) ans += leaves.size();
    leaves = next_leaves;
    // cout << "ans: " << ans << ", erased total: " << erased.size() << '\n';
    coloring = !coloring;
  }

  cout << ans;
  return 0;
}