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

    int N;
    cin >> N;

    for (int i = 0; i < N; ++i)
    {
        int R;
        string S;
        cin >> R >> S;

        string P = "";
        for (int j = 0; j < S.length(); ++j)
        {
            // for (int k = 0; k < R; ++k)
            // {
            //     P += S[j];
            // }
            P.append(R, S[j]);
        }

        cout << P << '\n';
    }

    return 0;
}