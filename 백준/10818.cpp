#include <iostream>

#define DEBUG true

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    if (DEBUG)
    {
        freopen("output.txt", "w", stdout);
        freopen("input.txt", "r", stdin);
    }

    int N, min = 1000001, max = -1000001;

    cin >> N;

    for (int i = 1; i <= N; ++i)
    {
        int x;
        cin >> x;

        if (x < min)
            min = x;
        if (x > max)
            max = x;
    }

    cout << min << ' ' << max << '\n';

    return 0;
}