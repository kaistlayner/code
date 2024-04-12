#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct knight{
    int r = 0, c = 0;
    int h = 0, w = 0;
    int k = 0;
    int damage = 0;
    bool drop_out = 0;
};

int L = -1, N = -1, Q = -1;
int chess[41][41] = {0,};
int chess_with_players[41][41] = {0,}; //기사만 있는거
knight players[31];
vector<pair<int, int> > orders;
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

void printBoard(int a[][41], bool clean = false){
    cout << '\n';
    for(int r = 1; r<= L; r++){
        for(int c = 1; c <= L; c++){
            if(a[r][c] < 0 || a[r][c] >= 10) cout << a[r][c] << ' ';
            else if(clean && a[r][c] == 1) cout << ' ' << 0 << ' ';
            else cout << ' ' << a[r][c] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void input(){
    cin >> L >> N >> Q;

    for(int i = 1; i <= L; i++){
        for(int j = 1; j <= L; j++){
            int tmp = -1;
            cin >> tmp;
            chess[i][j] = tmp;
            if(tmp == 2){
                chess_with_players[i][j] = -1;
            }
        }
    }

    for(int i = 1; i <= N; i++){
        int r = 0, c = 0, h = 0, w = 0, k = 0;
        cin >> r >> c >> h >> w >> k;
        players[i].r = r;
        players[i].c = c;
        players[i].h = h;
        players[i].w = w;
        players[i].k = k;

        for(int x = r; x < r + h; x++){
            for(int y = c; y < c + w; y++){
                chess_with_players[x][y] = i;
            }
        }
    }

    for(int j = 0; j < Q; j++){
        int i = 0, d = 0;
        cin >> i >> d;
        orders.push_back(make_pair(i,d));
    }
    
}

bool is_valid(int r, int c){
    return 0 < r && r <= L && 0 < c && c <= L && chess[r][c] != 2;
}

void update_chess_with_players(){
    for(int i = 1; i <= L; i++){
        for(int j = 1; j <= L; j++){
            chess_with_players[i][j] = 0;
        }
    }
    for(int i = 1; i <= N; i++){
        if(players[i].drop_out != 1){
            for(int r = players[i].r; r < players[i].r + players[i].h; r++){
                for(int c = players[i].c; c < players[i].c + players[i].w; c++){
                    chess_with_players[r][c] = i;
                }
            }
        }
    }

}

//벽이 있는지
bool can_push(int knight, int dir){
    bool check = true;
    int start_r = players[knight].r;
    int start_c = players[knight].c;

    for(int r = start_r; r < start_r + players[knight].h; r++){
        for(int c = start_c; c < start_c + players[knight].w; c++){
            int next_r = r + dr[dir];
            int next_c = c + dc[dir];
            if(!is_valid(next_r,next_c)) return false;
        }
    }
   return true;
}

//인접해있는 기사 구하기
set<int> get_neighbor(int knight, int dir){
    set<int> neighbor;
    int start_r = players[knight].r;
    int start_c = players[knight].c;

    for(int r = start_r; r < start_r + players[knight].h; r++){
        for(int c = start_c; c < start_c + players[knight].w; c++){
            int next_r = r + dr[dir];
            int next_c = c + dc[dir];
            if(chess_with_players[next_r][next_c] != knight && chess_with_players[next_r][next_c] > 0){
                neighbor.insert(chess_with_players[next_r][next_c]);
            }
        }
    }

    return neighbor;
}
//벽있는지 없는지. true 면 벽 없음.
bool can_push_all(int knight, int dir){
    bool check = true;

    set<int> neighbor = get_neighbor(knight, dir);
    //if(neighbor.empty()) return can_push(knight, dir);

    if(can_push(knight, dir)){
        for(auto i = neighbor.begin(); i != neighbor.end(); i++){
            check = check && can_push_all(*i, dir);
        }   
    }
    else{
        check = false;
    }
    
    return check;
}

void sol();

//데미지 계산 함수
//밀려난 기사만 데미지 입음.
void damaged(int target){
    cout << "target damage: " << target << '\t' << players[target].damage;
    for(int r = players[target].r; r < players[target].r + players[target].h; r++){
        for(int c = players[target].c; c < players[target].c + players[target].w; c++){
            if(chess[r][c] == 1){
                players[target].damage++;
            }
        }
    }
    cout << " -> " << players[target].damage << " / " << players[target].k << " and total damage: ";
    sol();
    cout << '\n';
}

bool move(int target, int d){
    //탈락확인
    if(players[target].drop_out) return 0;
    //벽확인
    if(!can_push_all(target, d)) return 0;

    cout << "searching: " << target << '\n'; 
    
    set<int> neighbor = get_neighbor(target, d);
    if(!neighbor.empty()){
        cout << target << "'s neighbor size: " << neighbor.size() << '\n'; 
        for(auto i = neighbor.begin(); i != neighbor.end(); i++){
            if(!get_neighbor(*i, d).empty()) move(*i, d);
            else{
              players[*i].r = players[*i].r + dr[d];
              players[*i].c = players[*i].c + dc[d];

              cout << "inner move: " << *i << ' ' << d << " by " << target << '\n'; 
              update_chess_with_players();
              printBoard(chess_with_players);
            }
            damaged(*i);
        }
    }

    players[target].r = players[target].r + dr[d];
    players[target].c = players[target].c + dc[d];

    cout << "move: " << target << ' ' << d << '\n';
    update_chess_with_players();
    printBoard(chess_with_players);
    return 1;
}


//탈락자 조사함수
void retire(){
    for(int i = 1; i <= N; i++){
        if(!players[i].drop_out && players[i].k <= players[i].damage){
            players[i].drop_out = 1;
            for(int r = players[i].r; r < players[i].r + players[i].h; r++){
                for(int c = players[i].c; c < players[i].c + players[i].w; c++){
                  if(chess_with_players[r][c] == i){
                    chess_with_players[r][c] = 0;
                  }
                }
            }
        }
    }
}

void sol(){
    int answer = 0;
    for(int i = 1; i <= N; i++){
        if(!players[i].drop_out){
            answer += players[i].damage;
        }
    }
    cout << answer << endl;
}

int main() {
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);

    input();

    printBoard(chess, 0);
    printBoard(chess_with_players);

    for(auto i = orders.begin(); i != orders.end(); i++){
        cout << "order: " << i->first << ' ' << i->second << '\n'; 
        if(move(i->first, i->second)) retire();
    }
    sol();

    return 0;
}