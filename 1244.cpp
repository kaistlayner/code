#include <iostream>
#include <string>

using namespace std;

void copy(char *dst, char *src)
{
    // cout << "copy " << dst << ' ' << src << endl;
    int i;
    for (i = 0; src[i]; i++)
    {
        dst[i] = src[i];
    }
    dst[i] = '\0';
    // cout << "result " << dst << endl;
}

void get_answer(char *cards, int chance, int len, char *ans)
{
    char buffer[7];
    // cout << "check: " << chance << " from " << cards << " current ans " << ans << endl;
    if (chance == 0)
        return;

    for (int i = 0; i < len - 1; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            copy(buffer, cards);
            buffer[i] = cards[j];
            buffer[j] = cards[i];

            if (chance == 1)
            {
                if (stoi(buffer) > stoi(ans))
                    copy(ans, buffer);
            }
            else
            {
                get_answer(buffer, chance - 1, len, ans);
            }
        }
    }
}

int main(int argc, char **argv)
{
    int test_case;
    int T;

    // freopen("input.txt", "r", stdin);
    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        char cards[7], ans[7];
        int chance, len = 0;
        cin >> cards >> chance;
        copy(ans, cards);

        for (; cards[len]; len++)
            ;
        get_answer(cards, chance, len, ans);
        cout << '#' << test_case << ' ' << ans << endl;
    }
    return 0;
}