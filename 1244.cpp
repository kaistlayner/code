#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void copy(char *dst, char *src)
{
    int i;
    for (i = 0; src[i]; i++)
    {
        dst[i] = src[i];
    }
    dst[i] = '\0';
}

bool is_string_same(char* a, char* b, int len){
    for (int i = 0; i < len; i++){
        if(a[i] != b[i]){
            return false;
        }
    }

    return true;
}

void get_answer(char* cards, int chance, int len, char* ans, char* ideal, bool* done)
{
    char buffer[7];
    // cout << "check: " << chance << " from " << cards << " current ans " << ans << endl;
    if (chance == 0 || *done){
        return;
    }

    if (is_string_same(cards, ideal, len)){
        if(chance % 2 == 0){
            *done = true;
            copy(ans, ideal);
            return;
        }
        else if(len > 1){
            ans[len - 1] = cards[len - 2];
            ans[len - 2] = cards[len - 1];
        }
        return;
    }

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
                get_answer(buffer, chance - 1, len, ans, ideal, done);
            }
        }
    }
}

int main(int argc, char **argv)
{
    int test_case;
    int T;

    freopen("input.txt", "r", stdin);
    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        char cards[7], ideal[7], ans[7];
        int chance, len = 0;
        bool done = false;
        cin >> cards >> chance;
        copy(ans, cards);

        int arr[7];
        for (; cards[len]; len++){
            arr[len] = cards[len] - '0';
        }
        sort(arr, arr+len);
        for (int i = 0; i < len; i++){
            ideal[i] = (char)arr[i];
        }

        get_answer(cards, chance, len, ans, ideal, &done);
        cout << '#' << test_case << ' ' << ans << endl;
    }
    return 0;
}