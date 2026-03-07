#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

#define ALPHA 26

vector<int> childs[ALPHA];
vector<string> edge_str[ALPHA];

int ans;
int saved_value[ALPHA];
int visited[ALPHA];

void reset_vars() {
    ans = 0;

    for (int i = 0; i < ALPHA; i++) {
        visited[i] = 0;
        saved_value[i] = 0;
        childs[i].clear();
        edge_str[i].clear();
    }
}

bool suffix_ok(string a, string b){
    if(a.size() < b.size()) swap(a,b);
    return a.substr(a.size()-b.size()) == b;
}

int check_conditions(int n){
    if(visited[n] == 1) return -1;

    if(visited[n] == 2) return saved_value[n];

    visited[n] = 1;

    int length = 0;
    string base = "";

    for(int i=0;i<childs[n].size();i++){
        int child = childs[n][i];
        string s = edge_str[n][i];

        int child_len = check_conditions(child);
        if(child_len == -1) return -1;

        if(base == "") base = s;
        else if(!suffix_ok(base, s)) return -1;

        length = max(length, child_len + (int)s.size());

        if(s.size() > base.size()) base = s;
    }

    visited[n] = 2;
    saved_value[n] = length;
    ans += length;

    return length;
}

int main()
{
    freopen("input.txt", "r", stdin);

    int T; 
    cin >> T;

    while(T--){
        reset_vars();

        int equation_cnt;
        cin >> equation_cnt;

        while(equation_cnt--){
            char A, B;
            string eq, plus, C;

            cin >> A >> eq >> B >> plus >> C;

            C = C.substr(1, C.size()-2);

            int a = A-'A';
            int b = B-'A';

            childs[a].push_back(b);
            edge_str[a].push_back(C);
        }

        for(int i=0;i<ALPHA;i++){
            if(visited[i]) continue;

            if(check_conditions(i) == -1){
                ans = -1;
                break;
            }
        }

        cout << ans << '\n';
    }
}