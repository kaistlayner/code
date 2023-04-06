#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
#include <map>

using namespace std;


void get_answer(char* cards, int chance, int len, char* ans, char* ideal, bool* done, map<string, bool[11]> *visited)
{
    char buffer[7];
    
    if (chance == 0 || *done){
        return;
    }

    if((*visited)[cards][chance]){
        return;
    }
    (*visited)[cards][chance] = true;

    if (strcmp(cards, ideal) == 0){
        if(chance % 2 == 0){
            *done = true;
            strcpy(ans, ideal);
            return;
        }
        else if(len > 1){
            strcpy(ans, ideal);
            ans[len - 1] = ideal[len - 2];
            ans[len - 2] = ideal[len - 1];
        }
        return;
    }

    for (int i = 0; i < len - 1; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            strcpy(buffer, cards);
            buffer[i] = cards[j];
            buffer[j] = cards[i];

            if (chance == 1)
            {
                if (stoi(buffer) > stoi(ans))
                    strcpy(ans, buffer);
            }
            else
            {
                get_answer(buffer, chance - 1, len, ans, ideal, done, visited);
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
        char cards[7], ideal[7] = {0}, ans[7];
        int chance, len = 0;
        bool done = false;
        cin >> cards >> chance;
        strcpy(ans, cards);


        int arr[7];
        for (; cards[len]; len++){
            arr[len] = cards[len] - '0';
        }
        sort(arr, arr+len, greater<int>());
        for (int i = 0; i < len; i++){
            ideal[i] = (char)('0' + arr[i]);
        }

        map<string,bool[11]> visited;
        get_answer(cards, chance, len, ans, ideal, &done, &visited);
        cout << '#' << test_case << ' ' << ans << endl;
    }
    return 0;
}