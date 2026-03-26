#include <bits/stdc++.h>

#define DEBUG true

using namespace std;
using pii = pair<int, int>;
using ll = long long;

int N;
vector<int> nums;
vector<ll> range_sum;

int get_left(int idx)
{
    return 2 * idx + 1;
}

int get_right(int idx)
{
    return 2 * idx + 2;
}

void init_range_sum(int idx, int left, int right)
{
    if (left == right)
    {
        range_sum[idx] = nums[left];
        // printf("[init] %d(%d ~ %d)'s sum: %d\n", idx, left, right, range_sum[idx]);
        return;
    }

    int left_idx = get_left(idx);
    int right_idx = get_right(idx);
    int mid = (left + right) / 2;

    init_range_sum(left_idx, left, mid);
    init_range_sum(right_idx, mid + 1, right);

    range_sum[idx] = range_sum[left_idx] + range_sum[right_idx];
    // printf("[init] %d(%d ~ %d)'s sum: %d\n", idx, left, right, range_sum[idx]);
}

void update_range_sum(int idx, int left, int right, int l, int r, int x)
{
    int left_max = max(left, l);
    int right_min = min(right, r);
    int cnt = right_min - left_max + 1;
    if (cnt < 1)
    {
        return;
    }

    range_sum[idx] += x * cnt;
    // printf("[update] %d(%d ~ %d)'s sum: %d / updated %d(%d ~ %d)\n", idx, left, right, range_sum[idx], x, l, r);
    if (left == right)
    {
        return;
    }

    int left_idx = get_left(idx);
    int right_idx = get_right(idx);
    int mid = (left + right) / 2;

    update_range_sum(left_idx, left, mid, l, r, x);
    update_range_sum(right_idx, mid + 1, right, l, r, x);
}

ll retrieve_range_sum(int idx, int left, int right, int l, int r)
{
    // 검색 범위에 벗어남
    if (right < l || r < left)
    {
        return 0;
    }
    // 범위에 속함
    else if (l <= left && right <= r)
    {
        // printf("[retrieve] %d(%d ~ %d)'s sum: %d\n", idx, left, right, range_sum[idx]);
        return range_sum[idx];
    }
    // 애매함
    int left_idx = get_left(idx);
    int right_idx = get_right(idx);
    int mid = (left + right) / 2;

    return retrieve_range_sum(left_idx, left, mid, l, r) + retrieve_range_sum(right_idx, mid + 1, right, l, r);
}

// void print_all()
// {
//     for (int i = 0; i < N; ++i)
//     {
//         cout << retrieve_range_sum(0, 0, N - 1, i, i) << ' ';
//     }
//     cout << '\n';
// }

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

    cin >> ::N;
    nums.resize(4 * N);
    range_sum.resize(4 * N);

    for (int i = 0; i < N; ++i)
    {
        cin >> nums[i];
    }

    init_range_sum(0, 0, N - 1);

    int Q, mode, f, r, x;
    cin >> Q;
    while (Q--)
    {
        cin >> mode;
        if (mode == 1)
        {
            cin >> f >> r >> x;
            update_range_sum(0, 0, N - 1, f - 1, r - 1, x);
        }
        else
        {
            cin >> f >> r;
            cout << retrieve_range_sum(0, 0, N - 1, f - 1, r - 1) << '\n';
        }
    }

    return 0;
}