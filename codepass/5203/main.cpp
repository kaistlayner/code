#include <bits/stdc++.h>
#define DEBUG true

using namespace std;
using pii = pair<int, int>;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    if (DEBUG)
    {
        freopen("input.txt", "r", stdin);
        // freopen("output.txt", "w", stdout);
    }

    int N;
    cin >> N;
    set<int> store_type;
    map<int, queue<int>> store_idx; // type -> idxs

    for (int i = 1; i <= N; ++i)
    {
        int type;
        cin >> type;
        store_type.insert(type);
        store_idx[type].push(i);
    }

    // 일단 앞에서 부터
    auto iter = store_type.begin();

    vector<pii> ans;
    while (iter != store_type.end())
    {
        int cur_type = *iter;

        // save answer
        int cur_idx = store_idx[cur_type].front();
        store_idx[cur_type].pop();
        ans.push_back({cur_type, cur_idx});

        // move iterator
        auto next_iter = iter;
        if (iter != store_type.begin())
        {
            --next_iter;
        }
        else
        {
            ++next_iter;
        }

        // erase empty type
        if (store_idx[cur_type].empty())
        {
            store_type.erase(iter);
        }

        iter = next_iter;
    }

    if (ans.size() < N)
    {
        // ans 맨 뒤에서 부터 elem 넣기
        auto target = *(store_type.begin());
        // cout << "target: " << target << '\n';
        stack<pii> ans2;
        priority_queue<int> inserted_target_idx;
        vector<int> visited(N + 1);

        for (auto iter = ans.rbegin(); iter != ans.rend(); iter++)
        {
            ans2.push(*iter);
            if (store_idx[target].empty())
            {
                continue;
            }

            auto [last_type, last_idx] = *iter;
            int front_type;
            if (last_type == target)
            {
                inserted_target_idx.push(-last_idx);
                visited[last_idx] = true;
            }

            if (iter + 1 == ans.rend())
            {
                front_type = -1;
            }
            else
            {
                auto [front_t, front_idx] = *(iter + 1);
                front_type = front_t;
            }

            // cout << "front: " << front_type << " last: " << last_type << '\n';
            if (last_type != target && front_type != target)
            {
                int target_idx = store_idx[target].front();
                store_idx[target].pop();
                ans2.push({target, target_idx});
                inserted_target_idx.push(-target_idx);
                visited[target_idx] = true;
                // cout << "inserted!\n";
            }
        }

        if (ans2.size() < N)
        {
            cout << -1 << '\n';
            return 0;
        }

        while (!ans2.empty())
        {
            auto [t, idx] = ans2.top();
            if (!visited[idx])
            {
                cout << idx << ' ';
            }
            else
            {
                int front_idx = inserted_target_idx.top();
                inserted_target_idx.pop();
                cout << -front_idx << ' ';
            }
            ans2.pop();
        }
        cout << '\n';
        return 0;
    }

    for (auto [t, idx] : ans)
    {
        cout << idx << ' ';
    }
    cout << '\n';

    return 0;
}