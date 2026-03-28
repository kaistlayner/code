#include <bits/stdc++.h>

#define DEBUG true

using namespace std;
using pii = pair<int, int>;
using ll = long long;

int N;
vector<int> nums;
vector<ll> range_sum;
vector<ll> lazy;

int get_left(int idx)
{
    return 2 * idx + 1;
}

int get_right(int idx)
{
    return 2 * idx + 2;
}

void push(int idx, int left, int right)
{
    if (lazy[idx] != 0)
    {
        range_sum[idx] += (right - left + 1) * lazy[idx];

        if (left != right)
        {
            lazy[get_left(idx)] += lazy[idx];
            lazy[get_right(idx)] += lazy[idx];
        }

        lazy[idx] = 0;
    }
}

void init_range_sum(int idx, int left, int right)
{
    if (left == right)
    {
        range_sum[idx] = nums[left];
        return;
    }

    int left_idx = get_left(idx);
    int right_idx = get_right(idx);
    int mid = (left + right) / 2;

    init_range_sum(left_idx, left, mid);
    init_range_sum(right_idx, mid + 1, right);

    range_sum[idx] = range_sum[left_idx] + range_sum[right_idx];
}

void update_range_sum(int idx, int left, int right, int l, int r, int x)
{
    push(idx, left, right);

    if (right < l || r < left)
    {
        return;
    }

    if (l <= left && right <= r)
    {
        lazy[idx] += x;
        push(idx, left, right);
        return;
    }

    int left_idx = get_left(idx);
    int right_idx = get_right(idx);
    int mid = (left + right) / 2;

    update_range_sum(left_idx, left, mid, l, r, x);
    update_range_sum(right_idx, mid + 1, right, l, r, x);

    range_sum[idx] = range_sum[left_idx] + range_sum[right_idx];
}

ll retrieve_range_sum(int idx, int left, int right, int l, int r)
{
    push(idx, left, right);

    if (right < l || r < left)
    {
        return 0;
    }

    if (l <= left && right <= r)
    {
        return range_sum[idx];
    }

    int left_idx = get_left(idx);
    int right_idx = get_right(idx);
    int mid = (left + right) / 2;

    return retrieve_range_sum(left_idx, left, mid, l, r) +
           retrieve_range_sum(right_idx, mid + 1, right, l, r);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> ::N;
    nums.resize(N);
    range_sum.resize(4 * N);
    lazy.resize(4 * N);

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