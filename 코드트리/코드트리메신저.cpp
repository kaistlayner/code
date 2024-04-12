#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 100001
#define MAX_D 22

int n, q;
int a[MAX_N], p[MAX_N], val[MAX_N];
bool notice[MAX_N];
int nx[MAX_N][MAX_D];

// 초기 설정 값을 받아옵니다.
void init() {
    // 부모 채팅과 채팅의 권한 정보를 입력받습니다.
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        // 채팅의 권한이 20을 초과하는 경우 20으로 제한합니다.
        if(a[i] > 20) a[i] = 20;
    }
    
    // TODO
}

// 채팅의 알림 상태를 토글합니다.
void toggle_notice(int chat) {
    // TODO
}

// 채팅의 권한의 크기를 변경합니다.
void change_power(int chat, int power) {
    // TODO
}

// 두 채팅의 부모를 교체합니다.
void change_parent(int chat1, int chat2) {
    // TODO
}

// 해당 채팅의 val 값을 출력합니다.
void print_count(int chat) {
    // TODO
}

int main() {
    cin >> n >> q;
    while(q--) {
        int query;
        cin >> query;
        if(query == 100) {
            init();
        }
        else if(query == 200) {
            int chat;
            cin >> chat;
            toggle_notice(chat);
        }
        else if(query == 300) {
            int chat, power;
            cin >> chat >> power;
            change_power(chat, power);
        }
        else if(query == 400) {
            int chat1, chat2;
            cin >> chat1 >> chat2;
            change_parent(chat1, chat2);
        }
        else if(query == 500) {
            int chat;
            cin >> chat;
            print_count(chat);
        }
    }
    return 0;
}