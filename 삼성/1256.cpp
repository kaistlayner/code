#include<iostream>
#include<algorithm>

using namespace std;

string words[400];

bool cmp(string a, string b){
	return a < b;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
		int index;
		string str;
		cin >> index >> str;

		for(int i=0; str[i]; i++){
			words[i] = &str[i];
		}

		sort(words, words+str.length(), cmp);

		cout << "#" << test_case << " " << words[index-1] << endl;
	}
	return 0;
}