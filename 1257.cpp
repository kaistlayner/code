#include<iostream>
#include<algorithm>
#include<set>

using namespace std;

string words[80000];
set<string> dic;

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
		int index, cnt = 0;
		string str;
		cin >> index >> str;

		for(int i=0; str[i]; i++){
			for(int j=i; str[j]; j++){
				string tmp = str.substr(i, j+1-i);
				if(dic.find(tmp) == dic.end()){
					dic.insert(tmp);
					words[cnt++] = tmp;
				}
			}
		}

		if(cnt < index){
			cout << "#" << test_case << " " << "none" << endl;
		}
		else{
			sort(words, words+cnt, cmp);
			cout << "#" << test_case << " " << words[index-1] << endl;
		}

		for(int i=0; i<cnt; i++)
			words[i].clear();
		dic.clear();
	}
	return 0;
}