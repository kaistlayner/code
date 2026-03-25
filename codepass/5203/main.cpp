#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

// 사전순 최소를 만들기 위해 "인덱스 기준 정렬"
// idx가 작은 후보부터 먼저 시도
struct CmpIdx
{
    bool operator()(const pii &a, const pii &b) const
    {
        return a.first < b.first;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);

    int N;
    cin >> N;

    // num -> 해당 숫자가 등장한 인덱스들
    map<int, vector<int>> pos;

    // num -> 남은 개수
    map<int, int> cnt;

    // num -> 현재까지 몇 개 사용했는지 (pos에서 포인터 역할)
    map<int, int> used;

    // 입력 처리
    for (int i = 1; i <= N; ++i)
    {
        int x;
        cin >> x;
        pos[x].push_back(i);
        cnt[x]++;
    }

    // 사전순 최소 후보 선택용
    // 각 숫자별 "현재 사용 가능한 가장 앞 인덱스"를 저장
    set<pii, CmpIdx> byIdx;

    // 최대 빈도 추적용
    // (-cnt, num) 형태로 넣어서 begin()이 최대 cnt
    set<pii> byCnt;

    // 초기 상태 세팅
    for (auto &[num, v] : pos)
    {
        byIdx.insert({v[0], num});
        byCnt.insert({-cnt[num], num});
        used[num] = 0;
    }

    // 현재 num의 "다음에 사용할 인덱스"
    auto cur_idx = [&](int num)
    {
        return pos[num][used[num]];
    };

    vector<int> ans;
    int last = -1;  // 직전에 사용한 숫자
    int remain = N; // 남은 총 개수

    for (int step = 0; step < N; ++step)
    {
        bool picked = false;

        // 현재 최대 빈도
        int mx = -byCnt.begin()->first;

        // 두 번째 최대 빈도
        int second_mx = 0;
        if (byCnt.size() >= 2)
        {
            auto it = byCnt.begin();
            ++it;
            second_mx = -it->first;
        }

        // 사전순 최소를 위해 idx 작은 순으로 후보 탐색
        for (auto it = byIdx.begin(); it != byIdx.end(); ++it)
        {
            int idx = it->first;
            int num = it->second;

            // 인접 중복 방지
            if (num == last)
                continue;

            // === feasibility check (미리 판단) ===
            // num을 하나 썼을 때 새로운 최대 빈도 계산

            int new_mx;

            if (cnt[num] == mx)
            {
                // 최대 빈도 원소를 줄이는 경우
                new_mx = max(cnt[num] - 1, second_mx);
            }
            else
            {
                // 최대 빈도 건드리지 않음
                new_mx = mx;
            }

            // 인접 중복 없이 끝까지 배치 가능한 조건
            // mx <= (remain - mx) + 1
            if (new_mx > (remain - 1 - new_mx) + 1)
            {
                continue;
            }

            // === 실제 반영 ===

            // 현재 상태 제거
            byIdx.erase(it);
            byCnt.erase({-cnt[num], num});

            // 사용 처리
            cnt[num]--;
            used[num]++;
            remain--;

            // 아직 남아있으면 다시 삽입
            if (cnt[num] > 0)
            {
                byIdx.insert({cur_idx(num), num});
                byCnt.insert({-cnt[num], num});
            }

            // 결과 기록
            ans.push_back(idx);
            last = num;
            picked = true;
            break;
        }

        // 어떤 후보도 못 고르면 불가능
        if (!picked)
        {
            cout << "-1\n";
            return 0;
        }
    }

    // 최종 인덱스 출력
    for (int x : ans)
        cout << x << ' ';
    cout << '\n';
}