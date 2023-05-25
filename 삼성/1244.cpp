#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
#include <map>

using namespace std;

map<string, bool[11]> visited;
int ans;

void get_answer(string cards, int chance, string ideal)
{
    visited[cards][chance] = true;

    if (chance < 1){
        if (ans < stoi(cards)){
            ans = stoi(cards);
        }
        return;
    }

    int len = cards.size();

    if (cards.compare(ideal) == 0){
        if(chance % 2 == 0){
            ans = stoi(ideal);
        }
        else if(len > 1){
            cards = ideal;
            cards[len - 1] = ideal[len - 2];
            cards[len - 2] = ideal[len - 1];
            ans = stoi(cards);
        }
        return;
    }

    for (int i = 0; i < len - 1; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            string buffer = cards;
            buffer[i] = cards[j];
            buffer[j] = cards[i];

            if(!visited[buffer][chance - 1])
            {
                get_answer(buffer, chance - 1, ideal);
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
        string cards, ideal;
        int chance;
        cin >> cards >> chance;

        int len = cards.size();
        ans = 0;
        visited.clear();

        int arr[7];
        for (int i = 0; i < len; i++){
            arr[i] = cards[i] - '0';
        }
        sort(arr, arr+len, greater<int>());
        for (int i = 0; i < len; i++){
            ideal[i] = (char)('0' + arr[i]);
        }

        get_answer(cards, chance, ideal);
        cout << '#' << test_case << ' ' << ans << endl;
    }
    return 0;
}