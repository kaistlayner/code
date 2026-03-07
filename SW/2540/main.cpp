#include<iostream>
#include<vector>

using namespace std;
#define ALPHA 26

int graph[ALPHA][ALPHA];
vector<int> childs[ALPHA], parents[ALPHA];
int ans, saved_value[ALPHA], visited[ALPHA];

void reset_vars() {
    ans = 0;

    for (int i = 0; i < ALPHA; i++) {
        visited[i] = 0;
        saved_value[i] = 0;
        childs[i].clear();
        parents[i].clear();

        for (int j = 0; j < ALPHA; j++) {
            graph[i][j] = 0;
        }
    }
}

int check_conditions(int n){ 
  if(visited[n] == 1) return -1;
  int length = saved_value[n];

  if(visited[n] == 0){
    visited[n] = 1;
    for(int child : childs[n]){
      int child_length = check_conditions(child);
      if(child_length == -1) return -1;

      length = max(length, child_length + graph[child][n]);
      //cout << '\t' << (char)('A' + n) << " <- " << (char)('A' + child) << '(' << saved_value[child] << ')' << ": " << graph[child][n] << '\n';
    }
    ans += length;
    visited[n] = 2; saved_value[n] = length;
    //cout << (char)('A' + n) << ": " << length << '\n';
  }

  return length;
}

int main(int argc, char** argv)
{
	freopen("input.txt", "r", stdin);
	int T; cin >> T;

	for(int test_case = 1; test_case <= T; ++test_case)
	{
    int equation_cnt; cin >> equation_cnt;
    reset_vars();

    while(equation_cnt--){
      char A, B; string eq, plus, C;
      cin >> A >> eq >> B >> plus >> C;
      C = C.substr(1, C.size() - 2);

      int a = A - 'A', b = B - 'A';
      int cost = C.size();

      graph[a][b] = -cost;
      graph[b][a] = cost;
      childs[a].push_back(b);
      parents[b].push_back(a);
    }

    for(int n = 0; n < ALPHA; ++n){
      if(visited[n]) continue;

      int length = check_conditions(n);
      if(length == -1){
        ans = -1;
        break;
      }
    }

    cout << ans << '\n';
	}

	return 0;
}